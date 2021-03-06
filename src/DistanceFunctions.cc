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

void SelectPointsWithDelta(std::vector<std::pair<double, double> > &Sy,
                           const std::vector<std::pair<double,
                                                       double >> &Py,
                           const double &median,
                           const double &delta) {

  auto positive_segment = median + delta;
  auto negative_segment = median - delta;

  for (auto &pair_points : Py) {
    if (pair_points.first <= positive_segment && pair_points.second >= negative_segment)
      Sy.emplace_back(pair_points);
  }
}

std::pair<std::pair<double, double>, std::pair<double, double> > ClosestSplitPair(const std::vector<std::pair<double,
                                                                                                              double> > &Px,
                                                                                  const std::vector<std::pair<double,
                                                                                                              double >> &Py,
                                                                                  const double &delta) {
  double median = FindMedianForAbscissa(Px);

  std::vector<std::pair<double, double> > Sy;

  SelectPointsWithDelta(Sy, Px, median, delta);

  double best = delta;

  std::pair<std::pair<double, double>, std::pair<double, double> > best_pair;

  for (int i = 0; i < Sy.size() - 1; ++i) {
    unsigned int diff = Sy.size() - i;
    for (unsigned int j = 0; j < std::min(static_cast<unsigned int>(7), diff); ++j) {
      if (CountFlatDistance(std::make_pair(Sy.at(i), Sy.at(i + j))) < best) {
        best = CountFlatDistance(std::make_pair(Sy.at(i), Sy.at(i + j)));
        best_pair = std::make_pair(Sy.at(i), Sy.at(i + j));
      }
    }
  }

  return best_pair;
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
    return std::pair<std::pair<double, double>, std::pair<double, double>>();
  }
}

std::pair<std::pair<double, double>, std::pair<double, double> > ClosestPair(const std::vector<std::pair<double,
                                                                                                         double> > &Px,
                                                                             const std::vector<std::pair<double,
                                                                                                         double >> &Py) {
  if (Px.size() <= 3 || Py.size() <= 3) {
    if (Px.size() == 3 || Py.size() == 3) {
      std::pair<std::pair<double, double>, std::pair<double, double> > x_f_s = std::make_pair(Px.at(0), Px.at(1));
      std::pair<std::pair<double, double>, std::pair<double, double> > x_f_t = std::make_pair(Px.at(0), Px.at(2));
      std::pair<std::pair<double, double>, std::pair<double, double> > x_s_t = std::make_pair(Px.at(1), Px.at(2));

      std::pair<std::pair<double, double>, std::pair<double, double> > y_f_s = std::make_pair(Py.at(0), Py.at(1));
      std::pair<std::pair<double, double>, std::pair<double, double> > y_f_t = std::make_pair(Py.at(0), Py.at(2));
      std::pair<std::pair<double, double>, std::pair<double, double> > y_s_t = std::make_pair(Py.at(1), Py.at(2));

      std::pair<std::pair<double, double>, std::pair<double, double> > best_x = ChooseBestOfThree(x_f_s, x_f_t, x_s_t);
      std::pair<std::pair<double, double>, std::pair<double, double> > best_y = ChooseBestOfThree(y_f_s, y_f_t, y_s_t);

      if (CountFlatDistance(best_x) < CountFlatDistance(best_y))
        return best_x;
      else
        return best_y;
    } else if (Px.size() <= 2 || Py.size() <= 2) {
      std::pair<std::pair<double, double>, std::pair<double, double> > x_f_s = std::make_pair(Px.at(0), Px.at(1));

      std::pair<std::pair<double, double>, std::pair<double, double> > y_f_s = std::make_pair(Py.at(0), Py.at(1));

      if (CountFlatDistance(x_f_s) < CountFlatDistance(y_f_s))
        return x_f_s;
      else
        return y_f_s;
    }
  } else {
    std::vector<std::pair<double, double> > Lx;
    std::vector<std::pair<double, double> > Ly;
    std::vector<std::pair<double, double> > Rx;
    std::vector<std::pair<double, double> > Ry;

    PushFirstHalf(Lx, Px);
    PushFirstHalf(Ly, Py);

    PushSecondHalf(Rx, Px);
    PushSecondHalf(Ry, Py);

    std::pair<std::pair<double, double>, std::pair<double, double> > best_left_pair = ClosestPair(Lx, Ly);
    std::pair<std::pair<double, double>, std::pair<double, double> > best_right_pair = ClosestPair(Rx, Ry);

    double delta = std::min(CountFlatDistance(best_left_pair), CountFlatDistance(best_right_pair));

    std::pair<std::pair<double, double>, std::pair<double, double> > best_split_pair = ClosestSplitPair(Px, Py, delta);

    return ChooseBestOfThree(best_left_pair, best_split_pair, best_right_pair);
  }
}