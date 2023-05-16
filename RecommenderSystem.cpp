#include "RecommenderSystem.h"

// See full documentation in header file
RecommenderSystem::RecommenderSystem ()
:_rs_movies(movie_compare ) //giving the map the compare func
{
}

// See full documentation in header file
sp_movie RecommenderSystem::add_movie
    (const std::string &name, int year, const std::vector<double> &features)
{
  sp_movie new_movie = make_shared<Movie> (name, year); //create new shared ptr
  _rs_movies[new_movie] = features; //adding the feature vec as value
  return new_movie; //return the movie
}

/*************** helpers functions for recommend functions ***************/

// See full documentation in header file
rank_map RecommenderSystem::find_average (const RSUser &user) const
{
  rank_map normalized_vec = user.get_ranks (); //save rank map as var
  double sum = FIRST;
  int num = FIRST;
  for (const auto &movie_ptr: normalized_vec)
  {
      sum += movie_ptr.second; //sum the ranks
      num++; //sum amount of movies that the user rank them
  }
  if(num == FIRST)
  {
    throw (std::logic_error(RANK_ERROR));
  }
  double avg = sum / num;
  for (auto &movie_ptr: normalized_vec)
  {
      movie_ptr.second -= avg; //normalized the rank
  }
  return normalized_vec;
}

// See full documentation in header file
vector<double> RecommenderSystem::mult
    (vector<double> &cur, double scalar) const
{
  vector<double> result; //create result vec
  result.reserve (cur.size ()); //determinate his size to feature vec size
  for (const auto &ptr: cur)
  {
    result.push_back (ptr * scalar); //push the result of the multiply
  }
  return result; //return result
}

// See full documentation in header file
vector<double> RecommenderSystem::find_preferences_vector
    (const rank_map &normalized_vec)
{
  bool first = true; //check if we in the first vector to add
  vector<double> pref;
  for (const auto &cur: normalized_vec)
  {
    //create mult vec of the feature vec and the rank of the user
    vector<double> new_vec = mult (_rs_movies[cur.first], cur.second);
    if (first) //if we in the first time
    {
        pref = new_vec;
        first = false;
    }
    else
    { //if we not in the first time
      int vec_size = pref.size();
      for (int i = 0; i < vec_size; i++)
      {
        pref[i] += new_vec[i]; //add the result from the mult
      }
    }
    }
  return pref; //return the preference vec
}

// See full documentation in header file
double RecommenderSystem::norm_func (const vector<double> &vec) const
{
  double norm_sum = FIRST;
  for (const auto &cur: vec)
  {
    norm_sum += pow (cur, POW_BY); //sum the value**2
  }
  return sqrt (norm_sum); //return the sqrt of the sum
}

// See full documentation in header file
double RecommenderSystem::find_similarity
    (const vector<double> &first_vec, const vector<double> &sec_vec) const
{
  double cord_mult = FIRST; //represent the coordinate mult
  int vec_size = first_vec.size();
  for (int i = 0; i < vec_size; i++)
  {
    cord_mult += first_vec[i] * sec_vec[i];
  }
  //find the mult of two norms of two vectors
  double norm_mult = norm_func (first_vec) * norm_func (sec_vec);
  if(norm_mult == FIRST)
  {
    throw (std::logic_error(NORM_ERROR));
  }
  return cord_mult / norm_mult; //return the similarity by the equation
}

// See full documentation in header file
sp_movie RecommenderSystem::
select_movie (const RSUser &user, const vector<double> &pref_vec) const
{
 sp_movie max_recommend = nullptr; //save the shared_ptr to recommend movie
  double max_predict = FIRST;//save the max predict_rank
  for (const auto &cur: _rs_movies)
  {
      if(user.get_ranks().count (cur.first) == NOT_FOUND)
        //if the movie isn't in the user movies
      {
        double cur_predict = find_similarity(pref_vec, cur.second);
        //if the cur predict is bigger then max or we didn't get movie yet
        if (cur_predict > max_predict || max_recommend == nullptr)
        {
          max_predict = cur_predict;
          max_recommend = cur.first;
        }
      }
    }
  return max_recommend; //return shared_ptr for the recommended movie
}



/*************************** until here ******************************/

// See full documentation in header file
sp_movie RecommenderSystem::recommend_by_content (const RSUser &user)
{
  //find the norm movies deg
  rank_map normalized_vec = find_average (user);
  // find the preference vec
  vector<double> pref_vec = find_preferences_vector (normalized_vec);
  //find recommend movie
  sp_movie selected_movie = select_movie (user, pref_vec);
  return selected_movie;
}
/********************** predict by filtering ***************************/

/**
 * compare bettween two pairs so the vec will bo sort
 * from the bigger to the smallest
 * @param lhs - pair 1
 * @param rhs - pair 2
 * @return true if pair 1 bigger then pair two else false
 */
bool compare(t_pair& lhs,t_pair& rhs)
{
  return lhs.second > rhs.second;
}

// See full documentation in header file
double RecommenderSystem::predict_movie_score
    (const RSUser &user, const sp_movie &movie, int k)
{ //get vector of pairs sp_movie and double
  vector<t_pair> similar_movie;
  for (const auto &cur_movie: _rs_movies)
  {
    if(user.get_ranks().count (cur_movie.first) != NOT_FOUND)
      //if it is movie that the user rank
    {
      double movie_deg = find_similarity
          (_rs_movies[cur_movie.first], _rs_movies[movie]);
      similar_movie.push_back({cur_movie.first,movie_deg}); //insert vec
    }
  } //sort to get k movies
  sort(similar_movie.begin(),similar_movie.end(), compare);
  double sum_predict_deg = FIRST;
  double sum_predict = FIRST;
  for(int i = 0;i < k;i++)
  { //calculate movie predict
    sum_predict += similar_movie[i].second;
    sum_predict_deg +=
        (similar_movie[i].second * user.get_ranks ()[similar_movie[i].first]);
  }
  if(sum_predict == FIRST)
  {
    throw (std::logic_error(SIMILAR_ERROR));
  }
  return sum_predict_deg / sum_predict;
}

// See full documentation in header file
sp_movie RecommenderSystem::recommend_by_cf (const RSUser &user, int k)
{
  sp_movie predict_movie = nullptr; //save the recommended movie
  double max_predict = FIRST; //save the max predict
  for(const auto& cur_movie : _rs_movies)
  {//if it is movie that the user didn't watch
    if(user.get_ranks().count (cur_movie.first) == NOT_FOUND)
    {//predict his score
      double cur_predict = predict_movie_score
          (user, cur_movie.first, k);
      if (cur_predict > max_predict || predict_movie == nullptr)
      {//check if cur score is bigger then max
        max_predict = cur_predict;
        predict_movie = cur_movie.first;
      }
    }
  }
  return predict_movie; //return the recommended movie
}

/*************************** until here ******************************/

// See full documentation in header file
sp_movie RecommenderSystem::get_movie
    (const std::string &name, int year) const
{ //create shared ptr to find the movie
  sp_movie cur = make_shared<Movie>(name,year);
  auto find_one = _rs_movies.find(cur);
  if (find_one == _rs_movies.end())
  {
    return sp_movie(nullptr); //todo - check
  }
  return ((find_one)->first); //return shared ptr to the movie
}

// See full documentation in header file
ostream& operator<<(ostream& is,RecommenderSystem rs)
{
  for(const auto& movie : rs._rs_movies)
  {
    is << *(movie.first); //print all of them
  }
  return is;
}




