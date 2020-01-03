#include <vector>
#include <chrono>

#include "test/test_ransac.hpp"
#include "ransac.hpp"
#include "homography/compute_homography_model.hpp"

using namespace std;

int main() {
  ComputeHomographyModel chm;
  vector<HomographyMeasurement> measurements;

  measurements.emplace_back(Point2f(0,0), Point2f(1,1));
  measurements.emplace_back(Point2f(1,1), Point2f(2,2));
  measurements.emplace_back(Point2f(2,1), Point2f(3,4));
  measurements.emplace_back(Point2f(4,3), Point2f(1,5));

  auto start = chrono::high_resolution_clock::now();
  HomographyModel hm = chm(measurements);
  auto finish = chrono::high_resolution_clock::now();

  cout << "Simple homography calculation\n";
  cout << "Both matrices should be equal\n";
  cout << "Ours: " << chrono::duration<double>(finish-start).count() << " s" << endl;
  hm.print();

  vector<Point2f> src, dst;
  src.emplace_back(0,0);
  src.emplace_back(1,1);
  src.emplace_back(2,1);
  src.emplace_back(4,3);
  dst.emplace_back(1,1);
  dst.emplace_back(2,2);
  dst.emplace_back(3,4);
  dst.emplace_back(1,5);

  start = chrono::high_resolution_clock::now();
  Mat H = findHomography(src, dst);
  finish = chrono::high_resolution_clock::now();
  cout << "OpenCV's: " << chrono::duration<double>(finish-start).count() << " s" << endl;
  cout << H << endl;

  return EXIT_SUCCESS;
}