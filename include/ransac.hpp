#pragma once

#include<vector>
#include<random>
#include<algorithm>
#include<exception>

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
  using namespace std;

  if(n > (int)measurements.size()) {
    throw invalid_argument("The number of measurements cannot be smaller than n");
  }

  ComputeModel compute_model;
  ComputeError compute_error;
  mt19937 rng(random_device{}());

  Model best_model;
  int n_inliers=0;

  for(int i = 0; i < k; i++) {
    // create a sampling
    vector<Measurement> sampling;
    // sample(measurements.begin(), measurements.end(), back_inserter(sampling), n, rng);
	int n0 = n;
	int k0 = k;
	while (n0 > 0) {
		//#include <stdlib.h>
		float p = rand() / (float) RAND_MAX; // float in [0,1[
		if (p < n0/ (float) k0) {
			sampling.push_back(measurements[k0]);
			n0--;
		}
		k0--;
	}
    // compute model
    Model model = compute_model(sampling);
    // compute number of inliers
    int cur_inliers = 0;
    for(const Measurement &measurement : measurements)
      if(compute_error(model, measurement) < t)
        cur_inliers++;
    // if has more inliers, set as best model
    if(cur_inliers > n_inliers) {
      best_model = model;
      n_inliers = cur_inliers;
    }
  }

  return best_model;
}