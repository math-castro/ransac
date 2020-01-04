#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

#include "homography/homography_model.hpp"

std::vector<HomographyModel> computeHomographies(std::vector<cv::Mat>& I);