#ifndef POINTSDISTANCE_INCLUDE_DISTANCEFUNCTIONS_HPP
#define POINTSDISTANCE_INCLUDE_DISTANCEFUNCTIONS_HPP

#include <cmath>
#include <vector>

bool comparator_x(const std::pair<double, double> &lhs, const std::pair<double, double> &rhs);

bool comparator_y(const std::pair<double, double> &lhs, const std::pair<double, double> &rhs);

inline double CountFlatDistance(const std::pair<std::pair<double, double>, std::pair<double, double> > &points) {
  return pow(pow(points.first.first - points.second.first, 2)
                 + pow(points.first.second - points.second.second, 2), 0.5f);
}

inline double FindMedianForAbscissa(const std::vector<std::pair<double,
                                                         double> > &Px) {
  int bound = Px.size() / 2;
  double sum = 0;
  for (int i = 0; i < bound; ++i) {
    sum += Px.at(i).first;
  }
  return sum / bound;
}

std::vector<std::pair<double, double> > SelectPointsWithDelta();

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
                                                                                                             double> > &rhs);

std::pair<std::pair<double, double>, std::pair<double, double> > ClosestPair(const std::vector<std::pair<double,
                                                                                                         double> > &Px,
                                                                             const std::vector<std::pair<double,
                                                                                                         double >> &Py);

std::pair<std::pair<double, double>, std::pair<double, double> > ClosestSplitPair(const std::vector<std::pair<double,
                                                                                                              double> > &Px,
                                                                                  const std::vector<std::pair<double,
                                                                                                              double >> &Py,
                                                                                  const double &delta);

inline void PushFirstHalf(std::vector<std::pair<double, double> > &dest,
                          const std::vector<std::pair<double, double> > &src) {
  int bound = src.size() / 2;
  int counter = 0;
  while (counter != bound) {
    dest.emplace_back(src.at(counter));
    ++counter;
  }
}

inline void PushSecondHalf(std::vector<std::pair<double, double> > &dest,
                           const std::vector<std::pair<double, double> > &src) {
  int bound = src.size();
  int counter = src.size() / 2;
  while (counter != bound) {
    dest.emplace_back(src.at(counter));
    ++counter;
  }
}

#endif //POINTSDISTANCE_INCLUDE_DISTANCEFUNCTIONS_HPP