#pragma once

#include<string>
#include<vector>

#include<opencv2/core.hpp>

std::vector<cv::Mat> readImagesInFolder(const std::string& path); 
std::vector<std::string> getFilePathsInFolder(const std::string& path);