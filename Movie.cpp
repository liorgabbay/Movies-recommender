
#include "Movie.h"


//***********************************************************dont move//
/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash(const sp_movie& movie){
    std::size_t res = HASH_START;
    res = res * RES_MULT + std::hash<std::string>()(movie->get_name());
    res = res * RES_MULT + std::hash<int>()(movie->get_year());
    return res;
}

/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2){
    return !(*m1 < *m2) && !(*m2 < *m1);
}
//***********************************************************dont move//

/**
 * compare between two movies
 * @param m1  - first movie
 * @param m2 - second movie
 * @return the result of the compare between both of them
 */
bool movie_compare(const sp_movie& m1,const sp_movie& m2)
{
  return *m1 < *m2;
}

// See full documentation in header file
Movie::Movie(const std::string& name, int year)
:_name(name),_year(year)
{
}

// See full documentation in header file
bool Movie::operator< (const Movie &rhs) const
{
  if(_year == rhs._year) // if the published year are the same
  {
    return _name<rhs._name; //compare names
  }
  return _year<rhs._year; //else compare by year
}

// See full documentation in header file
ostream& operator<<(ostream& is,const Movie& movie)
{
  is<<PRINT_MOVIE;
  return is;
}

