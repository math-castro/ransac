#pragma once

#include <opencv2/opencv.hpp>

class HomographyMeasurement {
 public:
  HomographyMeasurement(cv::Point2f src, cv::Point2f dst);
  const cv::Point2f src, dst;
};