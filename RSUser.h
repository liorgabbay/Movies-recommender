#ifndef GIT_USER_H
#define GIT_USER_H
/***************************/
/*         include         */
/***************************/
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "Movie.h"
/***************************/

/***************************/
/*         declares        */
/***************************/
class RecommenderSystem;
/***************************/

/***************************/
/*         typedef         */
/***************************/
typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;
typedef shared_ptr<RecommenderSystem> rs_ptr;
/***************************/

/***************************/
/*         defines         */
/***************************/
#define PRINT_USER "name: "<<user._name<<"\n"
/***************************/
class RSUser
{
 private:
  /************* private members *************/
  string _name; //user name
  rank_map _user_movies; //user rank map
  rs_ptr _rs_ptr; //user recommender system

 public:
  /*************** constructor ***************/
  /**
	 * Constructor for the class
	 */
  RSUser (string &name, rank_map &user_movies, rs_ptr &rs_ptr);

  /**************** getters ******************/

  /**
   * a getter for the user's name
   * @return the username
   */
  string get_name () const { return _name;}
  /**
   * a getter for the ranks map
   * @return
   */
  rank_map get_ranks () const { return _user_movies;}

  /**************** functions ******************/

  /**
   * function for adding a movie to the DB
   * @param name name of movie
   * @param year year it was made
   * @param features a vector of the movie's features
   * @param rate the user rate for this movie
   */
  void add_movie_to_rs (const std::string &name, int year,
                        const std::vector<double> &features,
                        double rate);

  /**
   * returns a recommendation according to the movie's content
   * @return recommendation
   */
  sp_movie get_recommendation_by_content () const;

  /**
   * returns a recommendation according to the similarity recommendation method
   * @param k the number of the most similar movies to calculate by
   * @return recommendation
   */
  sp_movie get_recommendation_by_cf (int k) const;

  /**
   * predicts the score for a given movie
   * @param name the name of the movie
   * @param year the year the movie was created
   * @param k the parameter which represents
   * the number of the most similar movies to predict the score by
   * @return predicted score for the given movie
   */
  double
  get_prediction_score_for_movie
  (const std::string &name, int year, int k) const;

  /**************** operators ******************/

  /**
   * output stream operator
   * @param os the output stream
   * @param user the user
   * @return output stream
   */
  friend ostream &operator<< (ostream &is, const RSUser &user);
};

#endif //GIT_USER_H
