#include "Deetector.hpp"
#include "pnp_solver.hpp"

//detec函数调用摄像头，同时具备识别apriltag和拍照两个功能
void Detector::detect()
{
    cv::VideoCapture cap(0);
    cv::Mat img;
    bool paused = false;



    // 设置图片保存文件夹
    std::string savePath = "shootphotos";
    int imageCount = 1;

    // 如果文件夹不存在，就自动创建
    if (!fs::exists(savePath))
    {
        fs::create_directories(savePath);
    }



    //选择Aprilag的字典家族36h11
    cv::Ptr <cv::aruco::Dictionary> dictionary =
    cv::aruco::getPredefinedDictionary(cv::aruco::DICT_APRILTAG_36h11);


    std::vector<std::vector<cv::Point2f>> corners;//装tag的角点坐标
    std::vector<int> ids;//储存识别结cv::Mat img_result = img.clone(); //克隆一个图像便于对比果



    while(true)
    {
        if(!paused)
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

        int key = cv::waitKey(33);

        //空格暂停
        if(key == 32)
            paused = !paused;

        
        //按s键拍照，搭配暂停使用
        if(key == 115 || key == 83)
        {
            // 拼接文件名
            std::string filename = savePath + "/" +std::to_string(imageCount) + ".jpg";

            // 保存图片
            if (cv::imwrite(filename, img))
            {
                std::cout << "保存成功：" << filename << std::endl;
                imageCount++;
            }
            
            
        }

        //esc退出
        if(key == 27)
            break;
    }
   
}
