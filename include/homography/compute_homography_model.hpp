#pragma once

#include "base/base_compute_model.hpp"
#include "homography.hpp"

using namespace std;

struct ComputeHomographyModel : public BaseComputeModel<HomographyModel, HomographyMeasurement>{
  HomographyModel operator()(const vector<HomographyMeasurement>& m);
};