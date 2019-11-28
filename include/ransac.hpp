#pragma once

#include<vector>

/*
*ComputeModel: should derive from BaseComputeModel with the same Model and Measurement
*ComputeError: should derive from BaseComputeError with the same Model and Measurement
*n: number of measurements to estimate model
*k: maximum number of iterations
*t: threshold for inliers
*/
template <class Model, class Measurement, class ComputeModel,
          class ComputeError>
Model ransac(const std::vector<Measurement>& measurements, int n, int k, double t) {
  // TODO: implement RANSAC
  ComputeModel compute_model;
  ComputeError compute_error;

  Model model = compute_model(measurements);
  Measurement measurement;

  compute_error(model, measurement);
  return model;
}