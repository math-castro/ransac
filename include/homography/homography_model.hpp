#pragma once

#include <opencv2/opencv.hpp>

class HomographyModel {
 public:
  HomographyModel(const cv::Matx33f& matrix);
  cv::Point2f operator()(cv::Point2f p) const;
 private:
  const cv::Matx33f _matrix;
};