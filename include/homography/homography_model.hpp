#pragma once

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

class HomographyModel {
 public:
  HomographyModel(const Eigen::Matrix3d& matrix);
  HomographyModel();
  cv::Point2f operator()(const cv::Point2f& p) const;
  void print() const;
  void operator=(const HomographyModel& o);
  HomographyModel inverse();
  cv::Mat toMat();
 private:
  Eigen::Matrix3d _matrix;
};