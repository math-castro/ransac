#pragma once

#include <opencv2/opencv.hpp>

class HomographyMeasurement {
 public:
  HomographyMeasurement(cv::Point2f src, cv::Point2f dst);
  void operator=(const HomographyMeasurement& o);
  cv::Point2f src, dst;
};