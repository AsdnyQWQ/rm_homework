#pragma once
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

void pnp_solver(cv::Mat img,std::vector<std::vector<cv::Point2f>> imagePoints,cv::Mat cameraMatrix,cv::Mat distCoeffs);