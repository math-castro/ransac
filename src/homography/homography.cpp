#include "homography/homography.hpp"

#include <queue>

#include "homography/homography_model.hpp"
#include "homography/homography_measurement.hpp"
#include "homography/compute_homography_model.hpp"
#include "homography/compute_homography_error.hpp"
#include "ransac.hpp"

using namespace std;
using namespace cv;

vector<HomographyModel> computeHomographies(vector<Mat>& I) {
  // compute features
  Ptr<AKAZE> D = AKAZE::create();
  vector<vector<KeyPoint>> m(I.size());
  vector<Mat> desc(I.size());
  for(size_t i = 0; i < I.size(); i++)
    D->detectAndCompute(I[i], noArray(), m[i], desc[i]);
  
  // build matches and Homographies
  BFMatcher matcher(NORM_HAMMING);
  vector<HomographyModel> H;
  vector<HomographyMeasurement> p;

  for (size_t i = 0; i < I.size()-1; i++) {
    vector<vector<DMatch>> nn_matches;
    matcher.knnMatch(desc[i+1], desc[i], nn_matches, 2);

    int n_match = 0;
    for (vector<DMatch>& vm : nn_matches) {
      if (vm[0].distance < vm[1].distance * 0.8 and vm[0].distance < 16)
        vm.pop_back(), n_match++;
      else
        vm.clear();
    }

    for (auto v : nn_matches) {
      for (auto mt : v) {
        p.emplace_back(m[i+1][mt.queryIdx].pt, m[i][mt.trainIdx].pt);
      }
    }

    if(p.size() < 4) continue;

    H.emplace_back(ransac<HomographyModel, HomographyMeasurement, ComputeHomographyModel, ComputeHomographyError, 4>(p));
  }

  return H;
}