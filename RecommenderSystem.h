#ifndef SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#define SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
/***************************/
/*         includes        */
/***************************/
#include "Movie.h"
#include "RSUser.h"
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
/***************************/
/***************************/
/*           using         */
/***************************/
using std::map;
using std::vector;
using std::find;
using std::pow;
using std::sqrt;
using std::array;
using std::sort;
/***************************/

/***************************/
/*         typedef         */
/***************************/
typedef map<sp_movie ,vector<double>,equal_func> movies_map;
typedef std::pair<sp_movie,double> t_pair;
/***************************/

/***************************/
/*         defines         */
/***************************/
#define FIRST 0
#define POW_BY 2
#define NOT_FOUND 0
#define RANK_ERROR "division by zero, number of rank movies is 0\n"
#define NORM_ERROR "division by zero, the multiply of the norms is 0\n"
#define SIMILAR_ERROR "division by 0, the sum of similar movies deg is 0\n"
/***************************/

/***************************/
/*       declaritions      */
/***************************/
bool compare(t_pair& lhs,t_pair& rhs);
/***************************/
class RecommenderSystem
{
 private:
  /********* private members *********/
  movies_map _rs_movies;

  /****************** private functions ****************/

  /**
   * normalized movie ranks
   * @param user
   * @return rank map with the normalized movie rank
   */
  rank_map find_average(const RSUser& user) const;

  /**
   * find user preferences vector
   * @param normalized_vec  - rank map with a normalized ranks
   * @return preferences vector for the user
   */
  vector<double> find_preferences_vector(const rank_map& normalized_vec);

  /**
   * return the recommended movie for the user
   * @param user
   * @param pref_vec - preferences vector of the user
   * @return shared_ptr to the recommended movie
   */
  sp_movie select_movie
  (const RSUser& user,const vector<double>& pref_vec) const;
  /**
   * return result vec of multiply vector with double number
   * @param cur - current vector
   * @param scalar - double number
   * @return result vector
   */
  vector<double> mult(vector<double>& cur,double scalar) const;
  /**
   * find similarity between two vector by equation
   * @param first_vec
   * @param sec_vec
   * @return double that represent similarity between two vectors
   */
  double find_similarity
  (const vector<double>& first_vec,const vector<double>& sec_vec) const;
  /**
   * find the norm of vector
   * @param vec
   * @return double - norm of the vector
   */
  double norm_func (const vector<double>& vec) const;
 public:
  /*****************  constructors ***************/

  /**
   * construct an object;
   */
  explicit RecommenderSystem();

  /******************  functions ******************/

  /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
	sp_movie add_movie
    (const std::string& name,int year,const std::vector<double>& features);


    /**
     * a function that calculates the movie with highest
     * score based on movie features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_content(const RSUser& user);

    /**
     * a function that calculates the movie with highest
     * predicted score based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_cf(const RSUser& user, int k);


    /**
     * Predict a user rating for a movie given argument
     * using item cf procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
	double predict_movie_score(const RSUser &user, const sp_movie &movie,
												  int k);

	/**
	 * gets a shared pointer to movie in system
	 * @param name name of movie
	 * @param year year movie was made
	 * @return shared pointer to movie in system
	 */
	sp_movie get_movie(const std::string &name, int year) const;
  /***************  operators ******************/

    /**
     * print all the movies to the stream
     * @param is - stream for output
     * @param rs - RecommenderSystem
     * @return output stream
     */
    friend ostream& operator<<(ostream& is,RecommenderSystem rs);

};


#endif //SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
