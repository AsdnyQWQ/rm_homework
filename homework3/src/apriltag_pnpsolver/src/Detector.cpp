#include "Detector.hpp"
#include "pnp_solver.hpp"


std::vector<std::vector<cv::Point2f>> Detector::detect(cv::Mat img)
{
    //选择Aprilag的字典家族36h11
    cv::Ptr <cv::aruco::Dictionary> dictionary =
    cv::aruco::getPredefinedDictionary(cv::aruco::DICT_APRILTAG_36h11);


    std::vector<std::vector<cv::Point2f>> corners;//装tag的角点坐标
    std::vector<int> ids;


    cv::aruco::detectMarkers(img,dictionary,corners,ids);//识别Apriltag

    if(ids.size() > 0)
    {
        //将识别结果显示出来
        cv::aruco::drawDetectedMarkers(img,corners,ids);
        //pnp解算
        
        return corners;
    }

    else
        return std::vector<std::vector<cv::Point2f>>();

}
