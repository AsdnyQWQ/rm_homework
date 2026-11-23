#include "Deetector.hpp"
#include "pnp_solver.hpp"

//detec函数调用摄像头识别apriltag
void Detector::detect()
{
    cv::VideoCapture cap(0);
    cv::Mat img;


    //选择Aprilag的字典家族36h11
    cv::Ptr <cv::aruco::Dictionary> dictionary =
    cv::aruco::getPredefinedDictionary(cv::aruco::DICT_APRILTAG_36h11);


    std::vector<std::vector<cv::Point2f>> corners;//装tag的角点坐标
    std::vector<int> ids;
    cv::Mat img_result = img.clone(); 



    while(true)
    {
        cap >> img;
        cv::Mat imgRaw = img.clone();

        cv::aruco::detectMarkers(img,dictionary,corners,ids);//识别Apriltag

        if(ids.size() > 0)
        {
            //将识别结果显示出来
            cv::aruco::drawDetectedMarkers(img,corners,ids);
            //pnp解算
            pnp_solver(img,corners);
            cv::imshow("result",img);
        }

        cv::imshow("Image_raw",imgRaw);

        cv::waitKey(33);

        
    }
   
}
