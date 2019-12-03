#pragma once

#include <opencv2/opencv.hpp>

#include "base/base_compute_error.hpp"
#include "homography.hpp"

using namespace cv;

struct ComputeHomographyError : public BaseComputeError<HomographyModel, HomographyMeasurement> {
  double operator()(const HomographyModel& model, const HomographyMeasurement& measurement);
};