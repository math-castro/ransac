#include "homography/homography_model.hpp"

using namespace cv;
using namespace Eigen;

HomographyModel::HomographyModel(const Eigen::Matrix3d& matrix) : _matrix(matrix) {}

Point2f HomographyModel::operator()(Point2f p) const {
  Vector3d v(p.x, p.y, 1);
  v = _matrix*v;
  return Point2f(v.x/v.z,v.y/v.z);
}