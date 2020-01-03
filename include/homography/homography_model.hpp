#pragma once

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

class HomographyModel {
 public:
  HomographyModel(const Eigen::Matrix3d& matrix);
  cv::Point2f operator()(cv::Point2f p) const;
 private:
  const Eigen::Matrix3d _matrix;
};