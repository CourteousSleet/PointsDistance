#include <iostream>

#include "../include/DistanceFunctions.hpp"

bool comparator_x(const std::pair<double, double> &lhs, const std::pair<double, double> &rhs) {
  if (lhs.first < rhs.first)
    return true;
  return false;
}

bool comparator_y(const std::pair<double, double> &lhs, const std::pair<double, double> &rhs) {
  if (lhs.second < rhs.second)
    return true;
  return false;
}

std::pair<std::pair<double, double>, std::pair<double, double> > ChooseBestOfThree(const std::pair<std::pair<double,
                                                                                                             double>,
                                                                                                   std::pair<double,
                                                                                                             double> > &lhs,
                                                                                   const std::pair<std::pair<double,
                                                                                                             double>,
                                                                                                   std::pair<double,
                                                                                                             double> > &mhs,
                                                                                   const std::pair<std::pair<double,
                                                                                                             double>,
                                                                                                   std::pair<double,
                                                                                                             double> > &rhs) {
  double dist_lhs = CountFlatDistance(lhs);
  double dist_rhs = CountFlatDistance(rhs);
  double dist_mhs = CountFlatDistance(mhs);

  double minimal_dist = std::min(std::min(dist_lhs, dist_rhs), dist_mhs);

  if (minimal_dist == dist_lhs)
    return lhs;
  else if (minimal_dist == dist_rhs)
    return rhs;
  else if (minimal_dist == dist_mhs)
    return mhs;
  else {
    std::cout << "Shit what happened\n";
  }
  return std::pair<std::pair<double, double>, std::pair<double, double>>();
}

std::pair<std::pair<double, double>, std::pair<double, double> > ClosestPair(std::vector<std::pair<double,
                                                                                                   double> > &Px,
                                                                             std::vector<std::pair<double,
                                                                                                   double >> &Py) {

  std::vector<std::pair<double, double> > Lx;
  std::vector<std::pair<double, double> > Ly;
  std::vector<std::pair<double, double> > Rx;
  std::vector<std::pair<double, double> > Ry;

  std::vector<std::pair<double, double> > Px_copy = Px;
  std::vector<std::pair<double, double> > Py_copy = Py;

  stable_sort(Px_copy.begin(), Px_copy.end(), comparator_x);
  stable_sort(Py_copy.begin(), Py_copy.end(), comparator_y);

  PushFirstHalf(Lx, Px_copy);
  PushFirstHalf(Ly, Py_copy);

  PushSecondHalf(Rx, Px_copy);
  PushSecondHalf(Ry, Py_copy);

  std::pair<std::pair<double, double>, std::pair<double, double> > best_left_pair = ClosestPair(Lx, Ly);
  std::pair<std::pair<double, double>, std::pair<double, double> > best_right_pair = ClosestPair(Rx, Ry);

  double delta = std::min(CountFlatDistance(best_left_pair), CountFlatDistance(best_right_pair));

  std::pair<std::pair<double, double>, std::pair<double, double> > best_split_pair = ClosestSplitPair(Px, Py, delta);

  return ChooseBestOfThree(best_left_pair, best_split_pair, best_right_pair);
}