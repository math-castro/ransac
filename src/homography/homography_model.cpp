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
  cout << _matrix/_matrix(2,2) << endl;
}