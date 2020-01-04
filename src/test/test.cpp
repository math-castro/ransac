#include <vector>
#include <chrono>
#include <Eigen/Dense>

#include "homography/compute_homography_model.hpp"
#include "homography/compute_homography_error.hpp"
#include "ransac.hpp"

using namespace std;
using namespace Eigen;

void random_measurements(Matrix3d& H, vector<Point2f>& src, vector<Point2f>& dst, int n) {
  src.clear();
  dst.clear();
  H = Matrix3d::Random();
  H /= H(2,2);
  VectorXd x = 1000*VectorXd::Random(n);
  VectorXd y = 1000*VectorXd::Random(n);
  for(int i = 0; i < n; i++) {
    Vector3d p(x(i), y(i), 1);
    Vector3d pp = H*p+Vector3d(1.*rand()/RAND_MAX, 1.*rand()/RAND_MAX, 0);
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
  double opencv = 0, our = 0;
  for(int i = 0; i < 1000; i++) {
    random_measurements(real_H, src, dst, 10000);
    start = chrono::high_resolution_clock::now();
    H = findHomography(src, dst, CV_RANSAC);
    finish = chrono::high_resolution_clock::now();
    opencv += chrono::duration<double>(finish-start).count();
    // cout << "Real H:\n" << real_H << endl;
    // cout << "OpenCV's H: " << chrono::duration<double>(finish - start).count()
        //  << " s" << endl;
    // cout << H << endl;

    measurements.clear();
    for (size_t i = 0; i < src.size(); i++) {
      measurements.emplace_back(src[i], dst[i]);
    }

    start = chrono::high_resolution_clock::now();
    auto my_H =
        ransac<HomographyModel, HomographyMeasurement, ComputeHomographyModel,
               ComputeHomographyError, 4>(measurements);
    finish = chrono::high_resolution_clock::now();
    our += chrono::duration<double>(finish-start).count();

    // cout << "Our H: " << chrono::duration<double>(finish - start).count()
        //  << " s" << endl;
    // my_H.print();
  }
  cout << "OpenCV's: " << opencv << " s" << endl;
  cout << "Ours: " << our << " s" << endl;

  return EXIT_SUCCESS;
}