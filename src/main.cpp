#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>

#include "utils/files.hpp"
#include "ransac.hpp"
#include "homography/homography_measurement.hpp"
#include "homography/homography_model.hpp"
#include "homography/compute_homography_model.hpp"
#include "homography/compute_homography_error.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
  
  // Usage message
  if(argc != 2) {
    printf("Usage: %s [path to data]\n", argv[0]);
    printf("Example: %s data/pano1\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // get arguments
  string path = argv[1];
  
  // read images
  vector<Mat> I = readImagesInFolder(path);

  // compute features
  Ptr<AKAZE> D = AKAZE::create();
  vector<vector<KeyPoint>> m(I.size());
  vector<Mat> desc(I.size());
  for(size_t i = 0; i < I.size(); i++)
    D->detectAndCompute(I[i], noArray(), m[i], desc[i]);
  
  // build matches and Homographies
  BFMatcher matcher(NORM_HAMMING);
  vector<vector<vector<HomographyMeasurement>>> p(I.size(), vector<vector<HomographyMeasurement>>(I.size()));
  vector<vector<HomographyModel>> H(I.size(), vector<HomographyModel>(I.size()));
  // vector<vector<vector<Point2f>>> pi(I.size(), vector<vector<Point2f>>(I.size()));
  // vector<vector<vector<Point2f>>> pj(I.size(), vector<vector<Point2f>>(I.size()));

  for (size_t i = 0; i < I.size(); i++) {
    for (size_t j = i + 1; j < I.size(); j++) {
      vector<vector<DMatch>> nn_matches;
      matcher.knnMatch(desc[i], desc[j], nn_matches, 2);

      int n_match = 0;
      for (vector<DMatch>& vm : nn_matches) {
        if (vm[0].distance < vm[1].distance * 0.8 and vm[0].distance < 32)
          vm.pop_back(), n_match++;
        else
          vm.clear();
      }

      for (auto v : nn_matches) {
        for (auto mt : v) {
          // pi[i][j].push_back(m[i][mt.queryIdx].pt);
          // pj[i][j].push_back(m[j][mt.trainIdx].pt);
          p[i][j].emplace_back(m[i][mt.queryIdx].pt, m[j][mt.trainIdx].pt);
        }
      }

      H[i][j] = ransac<HomographyModel, HomographyMeasurement, ComputeHomographyModel, ComputeHomographyError, 4>
      (p[i][j]);
    }
  }



  return EXIT_SUCCESS;
}