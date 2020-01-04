#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>

#include "utils/files.hpp"
#include "homography/homography.hpp"

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

  vector<HomographyModel> H = computeHomographies(I);

  Mat K = Mat::zeros(2* I[0].rows, 3 * I[0].cols, CV_8U);
  Mat H_cur = Mat::eye(3,3, CV_64F);
  for (int i = 0; i < 5; i++) {
    warpPerspective(I[i], K, H_cur, K.size(), INTER_LINEAR | WARP_INVERSE_MAP, BORDER_TRANSPARENT);
    H_cur = H[i].toMat()*H_cur;
  }

  imshow("panorama.jpg", K);

  waitKey(0);

  return EXIT_SUCCESS;
}