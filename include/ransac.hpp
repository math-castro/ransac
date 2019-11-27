#pragma once

#include<vector>

template<class Model, class Measurement, class ComputeModel>
Model ransac(const std::vector<Measurement>& measurements) {
  ComputeModel compute_model;
  return compute_model(measurements);
}