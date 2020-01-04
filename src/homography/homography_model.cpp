#include "homography/homography_model.hpp"

#include <iostream>

using namespace cv;
using namespace Eigen;
using namespace std;

HomographyModel::HomographyModel(const Eigen::Matrix3d& matrix) : _matrix(matrix) {}
HomographyModel::HomographyModel() {}

void HomographyModel::operator=(const HomographyModel& o) {
  _matrix = o._matrix;
}

Point2f HomographyModel::operator()(const Point2f& p) const {
  Vector3d v(p.x, p.y, 1);
  v = _matrix*v;
  return Point2f(v.x()/v.z(),v.y()/v.z());
}

void HomographyModel::print() const {
  cout << _matrix << endl;
}

HomographyModel HomographyModel::inverse() {
  return HomographyModel(_matrix.inverse());
}

Mat HomographyModel::toMat() {
  Mat H(3,3,CV_64F);
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      H.at<double>(i,j) = _matrix(i,j);
  return H;
}