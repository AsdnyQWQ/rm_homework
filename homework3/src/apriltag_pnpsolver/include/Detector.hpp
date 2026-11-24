#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/aruco.hpp>


class Detector
{   
    public:

    std::vector<std::vector<cv::Point2f>> detect(cv::Mat img);

};