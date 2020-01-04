#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>
#include <opencv2/stitching/detail/warpers.hpp>

#include "homography/homography.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
  // read images
  vector<Mat> I(3);
  I[0] = imread("../data/pano1/1.jpg", IMREAD_GRAYSCALE);
  I[1] = imread("../data/pano1/2.jpg", IMREAD_GRAYSCALE);
  I[2] = imread("../data/pano1/3.jpg", IMREAD_GRAYSCALE);

  vector<HomographyModel> H = computeHomographies(I);

  Mat O = Mat::zeros(2*I[0].rows, 2*I[0].cols, CV_8U);
  Mat H_cur = Mat::eye(3,3, CV_64F);
  Mat T = Mat::eye(3,3, CV_64F);
  T.at<double>(1,2) = I[0].cols/2.;

  for(size_t i = 0; i < I.size(); i++) {
    warpPerspective(I[i], O, T*H_cur, O.size(), INTER_LINEAR, BORDER_TRANSPARENT);
    H_cur = H[i].toMat()*H_cur;
  }
  imshow("panorama.jpg", O);

  waitKey(0);

  return EXIT_SUCCESS;
}