#include "files.hpp"

#include <filesystem>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Mat> readImagesInFolder(const string& path) {
    const vector<string> file_paths = getFilePathsInFolder(path);
    vector<Mat> I(file_paths.size());
    for(int i = 0; i < file_paths.size(); i++) {
        I[i] = imread(file_paths[i], IMREAD_GRAYSCALE);
    }
    return I;
}

vector<string> getFilePathsInFolder(const string& path) {
  vector<string> r;
  for (const auto& entry : filesystem::directory_iterator(path))
    if (entry.is_regular_file()) r.push_back(entry.path());
  return r;
}