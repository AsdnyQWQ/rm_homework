#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <filesystem>

namespace fs = std::filesystem;

void pnp_solver(cv::Mat img,std::vector<std::vector<cv::Point2f>> imagePoints);