#include"Detector.hpp"

int hmin=0,smin=20,vmin=223,hmax=179,smax=70,vmax=255;

void Detector::detect(std::string path)
{
    cv::Mat img,imgBlur,imgHSV,mask;
    cv::VideoCapture cap(path);
    std::vector <HSVrange> Color; 

    //创建滑动条
    cv::namedWindow("Trackbars",cv::WINDOW_NORMAL);
    cv::resizeWindow("Trackbars",640,100);

    cv::createTrackbar("hmin", "Trackbars", &hmin, 179);
    cv::createTrackbar("smin", "Trackbars", &smin, 255);
    cv::createTrackbar("vmin", "Trackbars", &vmin, 255);
    cv::createTrackbar("hmax", "Trackbars", &hmax, 179);
    cv::createTrackbar("smax", "Trackbars", &smax, 255);
    cv::createTrackbar("vmax", "Trackbars", &vmax, 255);


    Color.insert 
    (Color.end(),
    {
        {"orange",cv::Scalar(0,120,150),cv::Scalar(24,255,255)},
        {"yello",cv::Scalar(25,100,188),cv::Scalar(34,255,255)},
        {"red",cv::Scalar(156,175,70),cv::Scalar(179,255,255)},
        {"white",cv::Scalar(0,20,223),cv::Scalar(179,70,255)},
        {"blue",cv::Scalar(100,120,130),cv::Scalar(124,255,255)}
    }
    );




    while(true)
    {
        cap >> img;
        cv::Mat imgRaw =img.clone();

        cv::GaussianBlur(img,imgBlur,cv::Size(5,5),3,0);
        cv::cvtColor(imgBlur,imgHSV,cv::COLOR_BGR2HSV);//转HSV

        cv::Mat imgBinary = Detector::tuneHSV(imgHSV);

        for(int i=0; i <= Color.size()-1; i++)
        {
            //二值化识别特定颜色
            cv::inRange(imgHSV,Color[i].lower,Color[i].upper,mask);
            //读取二值化白色部分面积
            int whit_range = countNonZero(mask);

            //if(whit_range > 20000)
            drawResult(mask,img,Color[i].color);
            
            
        }

        cv::imshow("Image_raw",imgRaw);
        cv::imshow("Image_binary",imgBinary);
        cv::imshow("result",img);
 
        if(cv::waitKey(33) != -1)
            break;
    }
}



void Detector::drawResult(cv::Mat mask,cv::Mat img,std::string color)
{
    cv::Mat imgDil;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(30,30));
    cv::dilate(mask,imgDil,kernel);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;//储存轮廓的点

    cv::findContours(imgDil,contours,hierarchy,
        cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);//找到轮廓
    
    //储存多边形拐点坐标
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    
    for(int i = 0;i < contours.size(); i++)
    {
        int area = cv::contourArea(contours[i]);//计算轮廓面积
        if(area > 20000)
        {
            float peri = cv::arcLength(contours[i],true);//计算轮廓的周长
            cv::approxPolyDP(contours[i],conPoly[i],0.01 * peri,true);//寻找拐点

            boundRect[i] = cv::boundingRect(conPoly[i]);//储存矩形，这个矩形是最大xy和最小xy连成的
                     
            cv::rectangle(img,boundRect[i].tl(),
            boundRect[i].br(),cv::Scalar(0,255,0),4);//画矩形
            cv::putText(img,color,{boundRect[i].x,boundRect[i].y-10},
                cv::FONT_HERSHEY_DUPLEX, 0.75,cv::Scalar(0,255,0),2);
        }
    }
}






cv::Mat Detector::tuneHSV(cv::Mat imgHSV)
{
    cv::Mat imgBinary; 

    cv::Scalar lower(hmin,smin,vmin);
    cv::Scalar upper(hmax,smax,vmax);
    cv::inRange(imgHSV,lower,upper,imgBinary);
    
    return imgBinary;
}





void Detector::detect()
{
    cv::VideoCapture cap(0);//调用摄像头
    cv::Mat img;

    //选择Aprilag的字典家族36h11
    cv::Ptr <cv::aruco::Dictionary> dictionary =
    cv::aruco::getPredefinedDictionary(cv::aruco::DICT_APRILTAG_36h11);

    std::vector<std::vector<cv::Point2f>> corners;//装tag的角点坐标
    std::vector<int> ids;//储存识别结果

    while(true)
    {
        cap >> img;

        cv::Mat img_result = img.clone(); //克隆一个图像便于对比

        cv::aruco::detectMarkers(img,dictionary,corners,ids);//识别Apriltag

        if(ids.size() > 0)
        {
            //将识别结果显示出来
            cv::aruco::drawDetectedMarkers(img_result,corners,ids);
        }

        cv::imshow("Image_raw",img);
        cv::imshow("Image_result",img_result);

        if(cv::waitKey(33) != -1)
            break;
    }
   
}
