#include "cylindrical/warper.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

void cylindrical_warp(Mat I, Mat O, double f, double s) {
  double xc = I.cols/2.;
  double yc = I.rows/2.;
  for(int y = 0; y < I.rows; y++) {
    for(int x = 0; x < I.cols; x++) {
      double xi = x-xc, yi = y-yc;
      double tgo = xi/f;
      double theta = atan(tgo);
      double h = yi/f;
      O.at<double>(s*h, s*theta) = I.at<double>(y,x);
    }
  }
}