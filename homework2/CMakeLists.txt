cmake_minimum_required(VERSION 3.10)
project(rm_homework2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_definitions(-DVIDEO_PATH="${CMAKE_SOURCE_DIR}")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(app ${SOURCES})

target_link_libraries(app ${OpenCV_LIBS})