//
// Created on 2/21/2022.
//
#ifndef SCHOOL_SOLUTION_USERFACTORY_H
#define SCHOOL_SOLUTION_USERFACTORY_H

/***************************/
/*         includes        */
/***************************/
#include "RSUser.h"
#include "RecommenderSystemLoader.h"
#include <fstream>
#include <sstream>
/***************************/
/***************************/
/*          define         */
/***************************/
#define NO_RANK "NA"
/***************************/

class RSUsersLoader
{
private:
  /**
   * read the first line and create movies vector
   * @param rec - shared_ptr of recommended system
   * @param line - line to read from
   * @param movies_vec - movies vector
   */
  static void read_movie_line(const shared_ptr<RecommenderSystem>& rec,
                              string& line,vector<sp_movie>& movies_vec);
  /**
   * read the line into and create user
   * @param user_vec - vector of users
   * @param rec - shared_ptr of recommended system
   * @param line - line to read from
   * @param movies_vec - movies vector
   * @return true for success, else false
   */
  static bool read_user_line( vector<RSUser>& user_vec,
                              shared_ptr<RecommenderSystem>& rec,
                              string& line,const vector<sp_movie>& movies_vec);
public:
    RSUsersLoader() = delete;
    RSUsersLoader(const RSUsersLoader& other) = delete;
    RSUsersLoader& operator=
      (const RSUsersLoader& other) = delete;
    /**
     *
     * loads users by the given format with their movie's ranks
     * @param users_file_path a path to the file of the users and
     * their movie ranks
     * @param rs RecommendingSystem for the Users
     * @return vector of the users created according to the file
     */
    static std::vector<RSUser> create_users_from_file
    (const std::string& users_file_path, unique_rec recommender_system)
    noexcept(false);

};


#endif //SCHOOL_SOLUTION_USERFACTORY_H
