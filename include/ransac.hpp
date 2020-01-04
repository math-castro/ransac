#pragma once

#include<vector>
#include<random>
#include<algorithm>
#include<exception>
#include<iostream>

#include "utils/fast_sample.hpp"

int compute_iterations(double p, double r, int s) {
  const int INF = 0x3f3f3f3f;
  if(fabs(r) < 1e-9) return INF;
  return log(1-p)/log(1-pow(r,s));
}

/*
*ComputeModel: should derive from BaseComputeModel with the same Model and Measurement
*ComputeError: should derive from BaseComputeError with the same Model and Measurement
*n: number of measurements to estimate model
*k: maximum number of iterations
*t: threshold for inliers
*/
template <class Model, class Measurement, class ComputeModel,
          class ComputeError>
Model ransac(std::vector<Measurement>& measurements, int n, int k, double t) {
  using namespace std;

  if(n > (int)measurements.size()) {
    throw invalid_argument("The number of measurements cannot be smaller than n");
  }

  ComputeModel compute_model;
  ComputeError compute_error;
  mt19937 rng(random_device{}());

  Model best_model;
  int n_inliers=0;
  int n_iterations = min(compute_iterations(.99, 0, n), k);

  for(int i = 0; i < n_iterations; i++) {
    // create a sampling
    vector<Measurement> sampling = fast_sample<Measurement>(measurements, n);
    // compute model
    Model model = compute_model(sampling);
    // compute number of inliers
    int cur_inliers = 0;
    for(const Measurement &measurement : measurements)
      if(compute_error(model, measurement) < t) {
        cur_inliers++;
      }
    // if has more inliers, set as best model
    if(cur_inliers > n_inliers) {
      best_model = model;
      n_inliers = cur_inliers;
    }
    n_iterations = min(compute_iterations(.99, 1.*n_inliers/measurements.size(), n), k);
    cout << n_iterations << endl;
  }

  return best_model;
}