#pragma once

#include<string>
#include<vector>

#include<opencv2/core.hpp>

/*Reads all images in folder {path} into a Mat and returns them in a vector*/
std::vector<cv::Mat> readImagesInFolder(const std::string &path); 

/*Returns vector of all file paths in folder <path>*/
std::vector<std::string> getFilePathsInFolder(const std::string &path);