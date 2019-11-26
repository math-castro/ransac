#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <opencv2/opencv.hpp>

// #include <opencv2/calib3d/calib3d.hpp>
// #include <opencv2/features2d/features2d.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
  // Usage message
  if(argc != 3) {
    printf("Usage: %s [path to data] [number of images]\n", argv[0]);
    printf("For example: %s data/pano1 3\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // get arguments
  string path = argv[1];
  const int n = atoi(argv[2]);
  if(n == 0) {
    printf("Invalid value for the number of images\n");
    exit(EXIT_FAILURE);
  }

  vector<Mat> I(n);
  vector<Mat> H(n);

  for(int i = 0; i < n; i++) {
    char str[255];
    sprintf(str, "%s/%d.JPG", path.c_str(), i+1);
    I[i] = imread(str, IMREAD_GRAYSCALE);
  }

  for(int i = 3; i < n-1; i++) {
    Mat &I1 = I[i], &I2 = I[i+1];

    Ptr<AKAZE> D = AKAZE::create();
    vector<KeyPoint> m1, m2;
    Mat desc1, desc2;
    D->detectAndCompute(I1, noArray(), m1, desc1);
    D->detectAndCompute(I2, noArray(), m2, desc2);

    Mat J1, J2;

    BFMatcher matcher(NORM_HAMMING);
    vector<vector<DMatch>> nn_matches;
    matcher.knnMatch(desc1, desc2, nn_matches, 2);

    int n_match = 0;
    for (vector<DMatch> &vm : nn_matches) {
      if (vm[0].distance <= 32 and vm[0].distance < vm[1].distance * 0.8)
        vm.pop_back(), n_match++;
      else
        vm.clear();
    }

    vector<Point2f> p1, p2;

    for (auto v : nn_matches) {
      for (auto m : v) {
        p1.push_back(m1[m.queryIdx].pt);
        p2.push_back(m2[m.trainIdx].pt);
      }
    }

    H[i+1] = findHomography(p2, p1, RANSAC);

    // imshow("I1", I1);
    // imshow("I2", I2);
    // imshow("Panorama", K);
  }

  H[3] = Mat::eye(3, 3, CV_64F);
  for(int i = 4; i < n; i++) {
    printf("%d %d\n", H[i].rows, H[i].cols);
    H[i] = H[i-1]*H[i];
  }

  Mat K = Mat::zeros(5* I[0].rows, 25 * I[0].cols, CV_8U);
  for(int i = 3; i < n; i++) {
    warpPerspective(I[i], K, H[i], K.size(), INTER_LINEAR, BORDER_TRANSPARENT);
  }
  imwrite("panorama.jpg", K);

  return 0;
}