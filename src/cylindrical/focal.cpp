#include "cylindrical/focal.hpp"

#include <opencv2/stitching/detail/autocalib.hpp>
#include <iostream>

using namespace cv;
using namespace std;

double computeFocal(std::vector<HomographyModel>& H) {
  double f0, f1;
  bool f0_ok, f1_ok;
  int n_focal = 0;
  double focal = 0;
  for(size_t i = 0; i < H.size(); i++) {
    detail::focalsFromHomography(H[i].toMat(), f0, f1, f0_ok, f1_ok);
    if (f0_ok and f1_ok) focal += sqrt(f0 * f1), n_focal++, cout << sqrt(f0*f1) << endl;
  }
  return focal/n_focal;
}