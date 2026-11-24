cmake_minimum_required(VERSION 3.10)
project(apriltag_pnpsolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(ament_cmake REQUIRED)#ROS 2 使用的 CMake 构建工具
find_package(rclcpp REQUIRED)#ROS 2 的 C++ 接口，用来创建节点、订阅话题等
find_package(sensor_msgs REQUIRED)#提供图像等传感器消息的数据类型
find_package(cv_bridge REQUIRED)#将 ROS 2 图像消息转换成 OpenCV 的 cv::Mat

include_directories(${OpenCV_INCLUDE_DIRS})


include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(app ${SOURCES})

target_link_libraries(app ${OpenCV_LIBS})

#ros2依赖声明
ament_target_dependencies(app rclcpp sensor_msgs cv_bridge)

install(TARGETS app DESTINATION lib/${PROJECT_NAME})

ament_package()