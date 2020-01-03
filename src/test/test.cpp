#include <vector>
#include <chrono>
#include <Eigen/Dense>

#include "ransac.hpp"
#include "homography/compute_homography_model.hpp"
#include "homography/compute_homography_error.hpp"

using namespace std;
using namespace Eigen;

void random_measurements(Matrix3d& H, vector<Point2f>& src, vector<Point2f>& dst) {
  const int n = 1000;
  src.clear();
  dst.clear();
  H = Matrix3d::Random();
  VectorXd x = VectorXd::Random(n);
  VectorXd y = VectorXd::Random(n);
  for(int i = 0; i < n; i++) {
    Vector3d p(x(i), y(i), 1);
    Vector3d pp = H*(p + Vector3d::Random()*0.01);
    src.emplace_back(p.x()/p.z(), p.y()/p.z());
    dst.emplace_back(pp.x()/pp.z(), pp.y()/pp.z());
  }
}

int main() {
  ComputeHomographyModel chm;
  ComputeHomographyError che;
  vector<HomographyMeasurement> measurements;

  measurements.emplace_back(Point2f(0,0), Point2f(1,1));
  measurements.emplace_back(Point2f(1,1), Point2f(2,2));
  measurements.emplace_back(Point2f(2,1), Point2f(3,4));
  measurements.emplace_back(Point2f(4,3), Point2f(1,5));

  auto start = chrono::high_resolution_clock::now();
  HomographyModel hm = chm(measurements);
  auto finish = chrono::high_resolution_clock::now();

  // cout << che(hm, measurements[0]) << endl;

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

  Matrix3d real_H;

  random_measurements(real_H, src, dst);
  start = chrono::high_resolution_clock::now();
  H = findHomography(src, dst, CV_RANSAC);
  finish = chrono::high_resolution_clock::now();
  cout << "Real H:\n" << real_H/real_H(2,2) << endl;
  cout << "OpenCV's H: " << chrono::duration<double>(finish-start).count() << " s" << endl;
  cout << H << endl;

  measurements.clear();
  for(int i = 0; i < src.size(); i++) {
    measurements.emplace_back(src[i], dst[i]);
  }


  start = chrono::high_resolution_clock::now();
  auto my_H = ransac<HomographyModel, HomographyMeasurement, ComputeHomographyModel, ComputeHomographyError>
  (measurements, 4, 10, .1);
  finish = chrono::high_resolution_clock::now();

  cout << "Our H: " << chrono::duration<double>(finish-start).count() << " s" << endl;
  my_H.print();

  return EXIT_SUCCESS;
}