//
// Created on 2/20/2022.
//

#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H
#include <map>
#include "User.h"
#include <cmath>
typedef bool (*cmp_func) (const sp_movie &a, const sp_movie &b);
typedef std::map<sp_movie, std::vector<double>, cmp_func> map_movies;

class RecommendationSystem
{
 public:

  explicit RecommendationSystem ()
  {
    cmp_func func = [] (const sp_movie &a,
                        const sp_movie &b)
    {
        return ((*a) < (*b));
    };
    _movies = map_movies (func);
  }

  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie
  add_movie (const std::string &name, int year, const std::vector<double>
  &features);

  /**
   * a function that calculates the movie with highest score bas ed on movie
   * features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const User &user);

  /**
   * a function that calculates the movie with highes t predicted score
   * based on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const User &user, int k);

  /**
   * Predict a user rating for a movie given argument us ing item cf
   * procedure with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const User &user, const sp_movie &movie,
                              int k);

  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie (const std::string &name, int year) const;

  /**
   * output stream operator
   * @param os the output stream
   * @param rs the recommendation system
   * @return output stream
   */
  friend std::ostream &operator<< (std::ostream &os, const
  RecommendationSystem &rs);

 private:
  map_movies _movies;

  /**
 * Calculate the similarity between two vectors using the  formula:
 * (u * v) / (||u|| * ||v||).
 * The vectors v1 and v2 should have the same length.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The similarity value between the two vectors.
 */
  double calculate_similarity (const std::vector<double> &v1,
                               const std::vector<double> &v2);

  /**
 * Create a preferences vector based on the given ranks_map.
 * The preferences vector is a vector of doubles representing  the
 * preferences of a user.
 *
 * @param ranks_map The rank_map containing movie ranks.
 * @return The preferences vector calculated from the ranks_map.
 */
  std::vector<double> create_preferences_vector (const rank_map &ranks_map);

  /**
 * Suggest a movie based on the given preferences vector and user_movies.
 * The suggested movie is selected based on similarity between preferences
 * and user_movies.
 *
 * @param preferences_vec The preferences vector of a user.
 * @param user_movies The rank_map representing the movies already watched
 * by the user.
 * @return A shared pointer to the suggested movie.
 */
  sp_movie suggested_movie (const std::vector<double> &preferences_vec,
                            const rank_map &user_movies);

  /**
 * Normalize the ranks_map by dividing all the rank values by the maximum
 * rank value.
 *
 * @param ranks_map The rank_map to be normalized.
 */
  void normalize (rank_map &ranks_map);

};

#endif //RECOMMENDATIONSYSTEM_H
