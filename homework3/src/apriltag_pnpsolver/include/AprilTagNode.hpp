#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <cv_bridge/cv_bridge.h> 
#include <opencv2/core.hpp>

class AprilTagNode:public rclcpp::Node
{
    private:
    cv::Mat cameraMatrix,distCoeffs;

    //图像回调函数
    void imageCallback(sensor_msgs::msg::Image::ConstSharedPtr img_msg);

    // 接收相机标定结果
    void cameraInfoCallback(sensor_msgs::msg::CameraInfo::ConstSharedPtr camera_info_msg);

    //图像订阅者
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber;
    
    //相机标定结果订阅者
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr camera_info_subscriber;

    public:
    AprilTagNode();
};
