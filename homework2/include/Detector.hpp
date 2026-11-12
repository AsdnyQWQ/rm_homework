#include <iostream>
#include <string>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/aruco.hpp>

class Detector
{   
    public:

    struct HSVrange
    {
        std::string color;
        cv::Scalar lower;
        cv::Scalar upper;
    };

    void detect(std::string path);
    void detect();

    cv::Mat tuneHSV(cv::Mat imgHSV);//调参
    void drawResult(cv::Mat mask,cv::Mat img,std::string color);//绘制结果图
};