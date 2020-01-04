#pragma once

#include "base/base_compute_model.hpp"
#include "homography/homography_model.hpp"
#include "homography/homography_measurement.hpp"

using namespace std;

struct ComputeHomographyModel : public BaseComputeModel<HomographyModel, HomographyMeasurement>{
  HomographyModel operator()(vector<HomographyMeasurement> m);
};