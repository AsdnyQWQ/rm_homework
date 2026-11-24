#include "AprilTagNode.hpp"


int main(int argc, char **argv)
{
     // 初始化 ROS 2
    rclcpp::init(argc, argv);

    // 创建 AprilTagNode 节点
    auto node = std::make_shared<AprilTagNode>();

    // 运行节点，等待并处理订阅到的消息
    // 收到图像时，就会执行 imageCallback()
    rclcpp::spin(node);

    // 关闭 ROS 2
    rclcpp::shutdown();

    return 0;
}