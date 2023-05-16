#include "RecommenderSystemLoader.h"

bool RecommenderSystemLoader::read_line (string &line, unique_rec& rs)
{
  vector<double> feature; //create feature vec
  string word; //word to read into
  std::istringstream line_s (line);
  line_s >> word;//read movie name
  string movie_name = word.substr (FIRST,word.find (DASH)); //cut '-'
  string year = word.substr (word.find(DASH)+1);
  int movie_year = std::stoi (year, nullptr, BASE);
  while (line_s >> word) //read until the end of the line
  {
    auto rank = (double) std::stold (word, nullptr);//convert to double
    if (rank < LOWER_RANK || rank > MAX_RANK)
    {
      return false; //if the rank is invalid
    }
    feature.push_back (rank);
  }
  rs->add_movie (movie_name, movie_year, feature); //add
  return true;
}


unique_rec RecommenderSystemLoader::
create_rs_from_movies_file
    (const std::string &movies_file_path) noexcept (false)
{
  unique_rec rs = make_unique<RecommenderSystem> (); //create unique ptr
  std::ifstream input (movies_file_path); //open file
  if (!input.is_open ()) //check if open
  {
    throw (std::runtime_error (ERROR_FILE));
  }
  string line; //line to read into
  while (std::getline (input, line)) //read line
  {
    if(!read_line (line, rs)) //insert to recommender system
    {
      input.close ();
      throw (std::runtime_error (ERROR_WRONG_RANK));
    }
  }
  input.close ();
  return rs; //return recommender system
}





