#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
inline T CountLinearDistance(const pair<T, T> &points) {
  return abs(static_cast<double>(points.first - points.second));
}

template<typename T>
inline double CountFlatDistance(const pair<T, T> &f_points, const pair<T, T> &s_points) {
  return pow(pow(static_cast<double>(f_points.first - s_points.first), 2) + pow(static_cast<double>(f_points.second - s_points.second), 2), 0.5f);
}

template<typename T>
pair<double, double> ClosestPair(pair<vector<T>, vector<T>> &cord_points);

template<typename T>
pair<T, T> ClosestSplitPair(const pair<vector<T>, vector<T>> &cord_points, const double &parameter);

template<typename T>
inline void PushFirstHalf(vector<T> &dest, const vector<T> &points) {
  int bound = points.size() / 2;
  int counter = 0;
  while (counter != bound) {
    dest.emplace_back(points.at(counter));
    ++counter;
  }
}

template<typename T>
inline void PushSecondHalf(vector<T> &dest, const vector<T> &points) {
  int bound = points.size();
  int counter = points.size() / 2;
  while (counter != bound) {
    dest.emplace_back(points.at(counter));
    ++counter;
  }
}

int main() {
  pair<vector<int>, vector<int>> points({5, 2, 1, -5, 2, 6, 25, -49, -7, -13}, {-4, 0, 21, 3, -9, 2, 1, 6, 17, 4});

  pair<double, double> closest_points = ClosestPair(points);

  return 0;
}

template<typename T>
pair<T, T> ClosestSplitPair(const pair<vector<T>, vector<T>> &cord_points, const double &parameter) {

}

template<typename T>
pair<double, double> ClosestPair(pair<vector<T>, vector<T>> &cord_points) {

  vector<T> Lx;
  vector<T> Ly;
  vector<T> Rx;
  vector<T> Ry;

  stable_sort(cord_points.first.begin(), cord_points.first.end());
  stable_sort(cord_points.second.begin(), cord_points.second.end());

  PushFirstHalf(Lx, cord_points.first);
  PushFirstHalf(Ly, cord_points.second);

  PushSecondHalf(Rx, cord_points.first);
  PushSecondHalf(Ry, cord_points.second);

  pair<T, T> best_left_pair = ClosestPair(make_pair(Lx, Ly));
  pair<T, T> best_right_pair = ClosestPair(make_pair(Rx, Ry));

  double delta = min(CountLinearDistance(best_left_pair), CountLinearDistance(best_right_pair));

  pair<T, T> best_split_pair = ClosestSplitPair(cord_points, delta);

  return min(min(CountFlatDistance(best_left_pair, best_right_pair), CountFlatDistance(best_split_pair, best_right_pair)),
             CountFlatDistance(best_split_pair, best_left_pair));
}