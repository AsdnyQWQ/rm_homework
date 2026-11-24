#include "AprilTagNode.hpp"
#include "Detector.hpp"

void pnp_solver(cv::Mat img,std::vector<std::vector<cv::Point2f>> imagePoints,cv::Mat cameraMatrix,cv::Mat distCoeffs);

AprilTagNode::AprilTagNode() : Node("apriltag_pnpsolver_node")
{
    //创建订阅者，调用回调函数
    image_subscriber = this->create_subscription<sensor_msgs::msg::Image>
    (  "/camera/image_raw",10, 
        std::bind(&AprilTagNode::imageCallback,this,std::placeholders::_1)
    );


    camera_info_subscriber = this->create_subscription<sensor_msgs::msg::CameraInfo>
    ("/camera/camera_info",10,
    std::bind(&AprilTagNode::cameraInfoCallback,this,std::placeholders::_1)
    );

}


 void AprilTagNode::imageCallback(sensor_msgs::msg::Image::ConstSharedPtr msg)
 {
    RCLCPP_INFO(this->get_logger(), "Received an image!");
    
    // 将 ROS 2std::vector<std::vector<cv::Point2f>> 的 Image 消息转换成 OpenCV 的 cv::Mat
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

    // 获取 OpenCV 图像数据
    cv::Mat img = cv_ptr->image;
    cv::Mat imgRaw = img.clone();

    Detector detector;
    std::vector<std::vector<cv::Point2f>> imagePoints = detector.detect(img);

    if(!imagePoints.empty())
    {
        pnp_solver(img,imagePoints,cameraMatrix,distCoeffs);
    }

    cv::imshow("Image_raw",imgRaw);
    cv::imshow("result",img);
    cv::waitKey(1);
 }

 
void AprilTagNode::cameraInfoCallback(sensor_msgs::msg::CameraInfo::ConstSharedPtr camera_info_msg)
{
    // 读取相机内参
    cameraMatrix = cv::Mat(3, 3, CV_64F,        
        const_cast<double*>(camera_info_msg->k.data())).clone();

    // 读取畸变系数
    distCoeffs = cv::Mat(1, static_cast<int>(camera_info_msg->d.size()),CV_64F,
        const_cast<double*>(camera_info_msg->d.data())).clone();
}


