#include "RSUser.h"
#include "RecommenderSystem.h"

// See full documentation in header file
RSUser::RSUser
    (string &name, rank_map &user_movies, rs_ptr &rs_ptr)
    : _name (name), _user_movies (user_movies), _rs_ptr (rs_ptr)
{
}

// See full documentation in header file
void RSUser::add_movie_to_rs
    (const std::string &name,
     int year, const std::vector<double> &features, double rate)
{
  _rs_ptr->add_movie (name, year, features); //add to the recommender system
  sp_movie movie = _rs_ptr->get_movie (name, year); //get his shared_ptr
  _user_movies[movie] = rate; //add to the user rank map
}

// See full documentation in header file
sp_movie RSUser::get_recommendation_by_content () const
{ //use recommender system to find the movie
  return _rs_ptr->recommend_by_content (*this);
}

// See full documentation in header file
sp_movie RSUser::get_recommendation_by_cf (int k) const
{ //use recommender system to find the movie
  return _rs_ptr->recommend_by_cf (*this, k);
}

// See full documentation in header file
double RSUser::get_prediction_score_for_movie
    (const std::string &name, int year, int k) const
{  //use recommender system to find the movie score
  sp_movie movie = _rs_ptr->get_movie (name, year);
  return _rs_ptr->predict_movie_score (*this, movie, k);
}

// See full documentation in header file
ostream &operator<< (ostream &is, const RSUser &user)
{ //print the user and the movies
  is << PRINT_USER;
  is << *(user._rs_ptr);
  is << std::endl;
  return is;
}


