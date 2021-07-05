#include <fstream>

#include "../include/DistanceFunctions.hpp"

using namespace std;

int main() {
  ifstream is("../kek_vector");
  ofstream os("../output");

  vector<pair<double,
              double> > Px, Py;

  double x, y;

  while (!is.eof()) {
    is >> x >> y;
    Px.emplace_back(x, y);
    Py.emplace_back(x, y);
  }

  stable_sort(Px.begin(), Px.end(), comparator_x);
  stable_sort(Py.begin(), Py.end(), comparator_y);

  pair<pair<double, double>, pair<double, double> > closest_points = ClosestPair(Px, Py);

  os << closest_points.first.first << ' ' << closest_points.first.second << "---" << closest_points.second.first << ' ' << closest_points.second.second;

  is.close();
  os.close();

  return 0;
}