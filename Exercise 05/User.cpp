// don't change those includes
#include "User.h"
#include "RecommendationSystem.h"

void User::add_movie_to_rs (const std::string &name, int year,
                            const std::vector<double> &features, double rate)
{
  sp_movie movie = _ranking_sys->add_movie (name, year, features);
  _ranks[movie] = rate;
}

sp_movie User::get_recommendation_by_content () const
{
  return _ranking_sys->recommend_by_content (*this);
}

sp_movie User::get_recommendation_by_cf (int k) const
{
  return _ranking_sys->recommend_by_cf (*this, k);
}

double User::get_prediction_score_for_movie (const std::string &name,
                                             int year, int k) const
{
  std::shared_ptr<Movie> movie = _ranking_sys->get_movie (name, year);
  double prediction = _ranking_sys->predict_movie_score (*this, movie, k);
  return prediction;
}

std::ostream &operator<< (std::ostream &os, const User &user)
{
  if(!os)
  {
    throw std::runtime_error("Output Stream Corrupted");
  }
  os << "name: " << user._name << std::endl;
  os << (*user._ranking_sys) << std::endl;
  return os;
}
