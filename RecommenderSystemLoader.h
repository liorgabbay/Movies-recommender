
#ifndef RECOMMENDERSYSTEMLOADER_H
#define RECOMMENDERSYSTEMLOADER_H
/***************************/
/*         includes        */
/***************************/
#include "RecommenderSystem.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
/***************************/

/***************************/
/*         using           */
/***************************/
using std::unique_ptr;
using std::make_unique;
/***************************/

/***************************/
/*         typedef         */
/***************************/
typedef unique_ptr<RecommenderSystem> unique_rec;
/***************************/

/***************************/
/*         defines         */
/***************************/
#define ERROR_FILE "error: the file is wrong"
#define ERROR_WRONG_RANK "error: there is wrong rank input"
#define LOWER_RANK 1
#define MAX_RANK 10
#define BASE 10
#define DASH '-'
#define SPACE ' '
/***************************/
class RecommenderSystemLoader {
 private:
  static bool read_line(string& line,unique_rec& rs);
 public:
  RecommenderSystemLoader () = delete;
  RecommenderSystemLoader(const RecommenderSystemLoader& other) = delete;
  RecommenderSystemLoader& operator=
      (const RecommenderSystemLoader& other) = delete;
  /**
   * loads movies by the given format for movies with their feature's score
   * @param movies_file_path a path to the file of the movies
   * @return smart pointer to a RecommenderSystem which was created with
   * those movies
   */
  static unique_rec create_rs_from_movies_file
	  (const std::string &movies_file_path) noexcept (false);
};

#endif //RECOMMENDERSYSTEMLOADER_H
