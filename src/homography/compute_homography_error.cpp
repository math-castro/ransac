#include "homography/compute_homography_error.hpp"

double ComputeHomographyError::operator()(const HomographyModel& model, const HomographyMeasurement& measurement) {
  return norm(model(measurement.src) - measurement.dst);
}