#pragma once

#include<vector>

/*ComputeModel should derive from BaseComputeModel with the same Model and Measurement*/
template<class Model, class Measurement, class ComputeModel>
Model ransac(const std::vector<Measurement>& measurements) {
  //TODO: implement RANSAC
  ComputeModel compute_model;
  return compute_model(measurements);
}