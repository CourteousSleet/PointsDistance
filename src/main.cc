#include <fstream>

#include "../include/DistanceFunctions.hpp"

using namespace std;

int main() {
  ifstream is("../kek_vector");

  vector<pair<double,
              double> > Px, Py;

  stable_sort(Px.begin(), Px.end(), comparator_x);
  stable_sort(Py.begin(), Py.end(), comparator_y);

  pair<pair<double, double>, pair<double, double> > closest_points = ClosestPair(Px, Py);



  return 0;
}