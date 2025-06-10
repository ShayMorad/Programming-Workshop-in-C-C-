//
// Created by shaym on 6/24/2023.
//
#include <algorithm>
#include "RecommendationSystem.h"

sp_movie RecommendationSystem::add_movie (const std::string &name, int
year, const std::vector<double> &features)
{
  sp_movie mov = std::make_shared<Movie> (name, year);
  _movies[mov] = features;
  return mov;
}

sp_movie RecommendationSystem::get_movie (const std::string &name, int
year) const
{
  sp_movie mov = std::make_shared<Movie> (name, year);
  auto res = _movies.find (mov);

  if (res != _movies.end ())
  {
    return res->first;
  }

  return {nullptr};
}

double RecommendationSystem::predict_movie_score (const User &user, const
sp_movie &movie, int k)
{
  rank_map copied_ranks_map = user.get_ranks ();
  std::vector<std::pair<sp_movie, double>> calculated_scores;
  std::vector<double> features = _movies[movie];

  for (const auto &pair: copied_ranks_map)
  {
    std::vector<double> pair_features = _movies[pair.first];
    calculated_scores.emplace_back (pair.first, calculate_similarity (
        features, pair_features));
  }

  std::sort (
      calculated_scores.begin (), calculated_scores.end (),
      [] (std::pair<sp_movie, double> &a, std::pair<sp_movie, double> &b)
      { return a.second > b.second; });

  double similarity_and_rank = 0;
  double similarity = 0;
  for (int i = 0; i < k; i++)
  {
    similarity_and_rank += copied_ranks_map[calculated_scores[i].first]
                           * calculated_scores[i].second;
    similarity += calculated_scores[i].second;
  }

  return (similarity_and_rank / similarity);
}

void RecommendationSystem::normalize (rank_map &copied_ranks_map)
{
  double sum = 0;
  int movies_count = 0;
  for (auto &rank: copied_ranks_map)
  {
    movies_count++;
    sum += rank.second;
  }
  double average = sum / movies_count;
  for (auto &rank: copied_ranks_map)
  {
    copied_ranks_map[rank.first] = rank.second - average;
  }
}

std::vector<double> RecommendationSystem::create_preferences_vector (const
rank_map &ranks_map)
{
  std::vector<double> preferences;
  unsigned long features_amount = (_movies.begin ())->second.size ();
  for (unsigned long i = 0; i < features_amount; i++)
  {
    preferences.push_back (0);
  }

  for (const auto &pair: ranks_map)
  {
    std::vector<double> features = _movies[pair.first];
    for (unsigned long i = 0; i < features.size (); i++)
    {
      preferences[i] += pair.second * features[i];
    }
  }
  return preferences;
}

sp_movie RecommendationSystem::suggested_movie (const std::vector<double>
&preferences_vec, const rank_map &user_movies)
{
  double highest_rank = 0;
  std::shared_ptr<Movie> suggested_movie = nullptr;
  for (auto &pair: _movies)
  {
    if (user_movies.find (pair.first) != user_movies.end ())
    {
      continue;
    }
    std::vector<double> movie_features = _movies[pair.first];
    double movie_rank
        = calculate_similarity (preferences_vec, movie_features);

    if (suggested_movie == nullptr || movie_rank > highest_rank)
    {
      suggested_movie = pair.first;
      highest_rank = movie_rank;
    }
  }
  return suggested_movie;
}

double RecommendationSystem::calculate_similarity (const
std::vector<double> &v1, const std::vector<double> &v2)
{
  double dot = 0.0;
  double norm1squared = 0.0;
  double norm2squared = 0.0;

  for (unsigned long i = 0; i < v1.size (); ++i)
  {
    dot += v1[i] * v2[i];
    norm1squared += v1[i] * v1[i];
    norm2squared += v2[i] * v2[i];
  }
  double normproduct = std::sqrt (norm1squared) * std::sqrt (norm2squared);
  double similarity = dot / normproduct;
  return similarity;
}

sp_movie RecommendationSystem::recommend_by_content (const User &user)
{
  rank_map copied_ranks_map = user.get_ranks ();
  normalize (copied_ranks_map);
  std::vector<double> preferences = create_preferences_vector
      (copied_ranks_map);
  return suggested_movie (preferences, copied_ranks_map);
}

sp_movie RecommendationSystem::recommend_by_cf (const User &user, int k)
{
  rank_map copied_ranks_map = user.get_ranks ();
  std::shared_ptr<Movie> suggested_movie = nullptr;
  double highest_rank = 0;

  for (auto &pair: _movies)
  {
    if (copied_ranks_map.find (pair.first) != copied_ranks_map.end ())
    {
      continue;
    }
    double movie_rank
        = predict_movie_score (user, pair.first, k);

    if (suggested_movie == nullptr || movie_rank > highest_rank)
    {
      suggested_movie = pair.first;
      highest_rank = movie_rank;
    }
  }
  return suggested_movie;
}

std::ostream &operator<< (std::ostream &os, const RecommendationSystem &rs)
{
  for (const auto &movie : rs._movies)
  {
    os << (*movie.first);
  }
  return os;
}