#include "homography/homography_model.hpp"

using namespace cv;

HomographyModel::HomographyModel(const Eigen::Matrix3d& matrix) : _matrix(matrix) {}

Point2f HomographyModel::operator()(Point2f p) const {
  // TODO: implement function
  return Point2f(0,0);
}