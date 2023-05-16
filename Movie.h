#ifndef INC_22B_C_C__EX5_MOVIE_H
#define INC_22B_C_C__EX5_MOVIE_H
/***************************/
/*         includes        */
/***************************/
#include <iostream>
#include <vector>
#include <memory>
/***************************/

/***************************/
/*         using           */
/***************************/
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::ostream;
/***************************/

/***************************/
/*         defines         */
/***************************/
#define HASH_START 17
#define RES_MULT 31
#define PRINT_MOVIE movie._name<<" ("<<movie._year<<")\n"
/***************************/

/***************************/
/*      class declare      */
/***************************/
class Movie;
/***************************/

/***************************/
/*         typedef         */
/***************************/
typedef shared_ptr<Movie> sp_movie; // smart pointer to movie
typedef std::size_t (*hash_func)(const sp_movie& movie);
typedef bool (*equal_func)(const sp_movie& m1,const sp_movie& m2);
/***************************/

/***************************/
/*   function declaration  */
/***************************/
std::size_t sp_movie_hash(const sp_movie& movie);
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2);
bool movie_compare(const sp_movie& m1,const sp_movie& m2);
/***************************/

class Movie
{
 private:
  /************* private members *************/
  string _name; //movie name
  int _year; //movie published year

 public:
  /*************** constructor ***************/

  /**
     * constructor
     * @param name: name of movie
     * @param year: year it was made
     */
    Movie(const std::string& name, int year);
  /**************** getters ******************/

    /**
     * returns the name of the movie
     * @return const ref to name of movie
     */
    string get_name() const {return _name;}
    /**
     * returns the year the movie was made
     * @return year movie was made
     */
    int get_year() const {return _year;}

  /**************** operators ******************/

  /**
     * operator< for two movies
     * @param rhs: right hand side
     * @param lhs: left hand side
     * @return returns true if (lhs.year) < rhs.year or
     * (rhs.year == lhs.year & lhs.name < rhs.name) else return false
     */
    bool operator<(const Movie& rhs) const;

    /**
     * operator<< for movie
     * @param os ostream to output info with
     * @param movie movie to output
     */
    friend ostream& operator<<(ostream& is,const Movie& movie);
};



#endif //INC_22B_C_C__EX5_MOVIE_H
