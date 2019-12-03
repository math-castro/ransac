#include "homography/compute_homography_model.hpp"

HomographyModel ComputeHomographyModel::operator()(const vector<HomographyMeasurement>& m) {
  // TODO: implement this function
  m.size();
  return HomographyModel(cv::Matx33f::eye());
};