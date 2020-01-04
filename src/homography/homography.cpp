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
    matcher.knnMatch(desc[i], desc[i+1], nn_matches, 2);

    int n_match = 0;
    for (vector<DMatch>& vm : nn_matches) {
      if (vm[0].distance < vm[1].distance * 0.8 and vm[0].distance < 16)
        vm.pop_back(), n_match++;
      else
        vm.clear();
    }

    for (auto v : nn_matches) {
      for (auto mt : v) {
        p.emplace_back(m[i][mt.queryIdx].pt, m[i+1][mt.trainIdx].pt);
      }
    }

    if(p.size() < 4) continue;

    H.emplace_back(ransac<HomographyModel, HomographyMeasurement, ComputeHomographyModel, ComputeHomographyError, 4>(p));
  }

  return H;
}
// #include <opencv2/stitching/detail/autocalib.hpp>
// int main(int argc, char **argv) {

//   vector<Mat> I(n);
//   vector<Mat> H(n);
//   vector<Mat> R(n);

//   for(int i = 0; i < n; i++) {
//     char str[255];
//     sprintf(str, "%s/%d.JPG", path.c_str(), i+1);
//   }

//   double focal = 0;
//   int n_focal = 0;

//   for(int i = 0; i < n-1; i++) {
//     Mat &I1 = I[i], &I2 = I[i+1];

//     Ptr<AKAZE> D = AKAZE::create();
//     vector<KeyPoint> m1, m2;
//     Mat desc1, desc2;
//     D->detectAndCompute(I1, noArray(), m1, desc1);
//     D->detectAndCompute(I2, noArray(), m2, desc2);

//     Mat J1, J2;

//     BFMatcher matcher(NORM_HAMMING);
//     vector<vector<DMatch>> nn_matches;
//     matcher.knnMatch(desc1, desc2, nn_matches, 2);

//     int n_match = 0;
//     for (vector<DMatch> &vm : nn_matches) {
//       if (vm[0].distance < vm[1].distance * 0.8)
//         vm.pop_back(), n_match++;
//       else
//         vm.clear();
//     }

//     vector<Point2f> p1, p2;

//     for (auto v : nn_matches) {
//       for (auto m : v) {
//         p1.push_back(m1[m.queryIdx].pt);
//         p2.push_back(m2[m.trainIdx].pt);
//       }
//     }

//     H[i+1] = findHomography(p2, p1, RANSAC);

//     // double f0, f1;
//     // bool f0_ok, f1_ok;
//     // detail::focalsFromHomography(H[i+1], f0, f1, f0_ok, f1_ok);
//     // if(f0_ok and f1_ok) focal += sqrt(f0*f1), n_focal++;
//   }

//   // focal /= n_focal;
//   // printf("f: %f\n", focal);

//   // Mat K = Mat::eye(3,3, CV_64F);
//   // K.at<double>(0,0) = K.at<double>(1,1) = focal;
  

//   Mat K = Mat::zeros(5* I[0].rows, 25 * I[0].cols, CV_8U);
//   Mat H_cur = Mat::eye(3,3, CV_64F);
//   H[3] = H_cur;
//   for (int i = 3; i < n; i++) {
//     H_cur = H[i]*H_cur;
//     warpPerspective(I[i], K, H_cur, K.size(), INTER_LINEAR, BORDER_TRANSPARENT);
//     // R[i] = (K.inv()*H[i]*K).inv();
//   }

//   imwrite("panorama.jpg", K);


//   return 0;
// }