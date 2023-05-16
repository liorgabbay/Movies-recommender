#include "RSUsersLoader.h"

 void RSUsersLoader :: read_movie_line
 (const shared_ptr<RecommenderSystem>& rec,
  string& line,vector<sp_movie>& movies_vec)
{
  string movie_name; //movie name
  string s_year; //movie year
  //replace '-' with ' '
  std::replace(line.begin(),line.end(),DASH,SPACE);
  std::istringstream line_s (line);
  while(line_s >> movie_name >> s_year)
  {
    int year = std::stoi (s_year, nullptr, BASE); //convert to int
    //get movie ptr and push to vec movies
    movies_vec.push_back (rec->get_movie (movie_name,year));
  }
}

bool RSUsersLoader :: read_user_line(vector<RSUser>& user_vec,
                                     shared_ptr<RecommenderSystem>& rec,
                                     string& line,
                                     const vector<sp_movie>& movies_vec)
{
  string word;
  std::istringstream line_s (line); //convert to stream
  //create rank map
  rank_map user_movies (movies_vec.size(),sp_movie_hash,sp_movie_equal);
  line_s>>word; //read user's name
  string user_name = word;
  int rank_count = FIRST;//count for know which movie we at
  while(line_s>>word) //read from the line
  {
    if(word != NO_RANK) //if the user rank the movie
    {
      auto rank = (double)std::stold (word);
      if(rank < LOWER_RANK || rank > MAX_RANK) //check if rank is valid
      {
        return false;
      }
      sp_movie cur_movie = movies_vec[rank_count]; //getting movie ptr
      user_movies[cur_movie] = rank; //insert to user vector
    }
    rank_count++;
  }//insert to users vec
  user_vec.push_back (RSUser(user_name,user_movies,rec));
  return true;
}


std::vector<RSUser> RSUsersLoader::create_users_from_file
    (const std::string &users_file_path, unique_rec recommender_system)
noexcept (false)
{
  vector<RSUser> user_vec; //create users vector
  vector<sp_movie> movies_vec; //create movies vector
  std::ifstream input (users_file_path); //open file
  if (!input.is_open ())
  {
    throw (std::runtime_error (ERROR_FILE));
  }
  //transfer the unique ptr to shared dor the users
  shared_ptr<RecommenderSystem> rec = std::move(recommender_system);
  bool first_line = true; //check if we in the first line
  string line;
  while (std::getline (input, line)) //insert to line
  {
    if (first_line) //if we in the first line
    {
      read_movie_line (rec,line,movies_vec); //read first line into movies vec
      first_line = false;
    }
    else
    {//read vars for user and insert it to users vec
      if(!read_user_line (user_vec,rec,line,movies_vec))
      {
        input.close();
        throw (std::runtime_error (ERROR_WRONG_RANK));
      }
    }
  }
  input.close();
  return user_vec; //return users vec
}

