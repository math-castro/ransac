#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>

#include "utils/files.hpp"
#include "ransac.hpp"

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
  
  waitKey(0);
  return EXIT_SUCCESS;
}