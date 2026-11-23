#include "calibrate_camera.hpp"


void calibrate_camera()
{
    std::vector<std::string> imgShoot;
    cv::glob("shootphotos/*.jpg", imgShoot);

    cv::Size patternSize(9, 6);
    float squareSize = 25.0f;

    std::vector<cv::Point2f> corners;//棋盘角点坐标
    std::vector<cv::Point3f> obj;//角点在三维世界坐标


    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;



    //将棋盘所有点坐标储存在obj中作为世界坐标系
    for (int i = 0; i < patternSize.height; i++)
    {
        for (int j = 0; j < patternSize.width; j++)
        {
            obj.push_back(cv::Point3f(j * squareSize,i * squareSize,0));
        }
    }


    //识别图片中所有网格点的坐标
    cv::Size imgSize;
    for(int i = 0; i < imgShoot.size(); i++)//读取棋盘上每一个网格点的坐标
    {
        corners.clear();
        cv::Mat img = cv::imread(imgShoot[i]);
        cv::Mat imgGray;
        imgSize = img.size();//读取棋盘上每一个网格点的坐标

        cv::cvtColor(img,imgGray,cv::COLOR_BGR2BGRA);

        bool found = cv::findChessboardCornersSB(imgGray,patternSize,corners);

        objectPoints.push_back(obj);//储存棋盘三维坐标
        imagePoints.push_back(corners);//储存角点坐标
    }

    // 相机内参矩阵
    cv::Mat cameraMatrix;

    // 畸变系数
    cv::Mat distCoeffs;

    // 每张图片对应的旋转向量
    std::vector<cv::Mat> rvecs;

    // 每张图片对应的平移向量
    std::vector<cv::Mat> tvecs;

    // 执行标定，返回 RMS 重投影误差
    double rms = cv::calibrateCamera(objectPoints,imagePoints,imgSize,
    cameraMatrix,distCoeffs,rvecs,tvecs);


    // 创建文件，使用写入模式
    cv::FileStorage fs("calibration_result.yml", cv::FileStorage::WRITE);

    // 保存相机标定参数
    fs << "cameraMatrix" << cameraMatrix;
    fs << "distCoeffs" << distCoeffs;

    // 保存每张图片对应的外参
    fs << "rvecs" << rvecs;
    fs << "tvecs" << tvecs;

    // 保存 RMS
    fs << "rms" << rms;

    // 保存图像尺寸
    fs << "imageWidth" << imgSize.width;
    fs << "imageHeight" << imgSize.height;

    // 关闭文件
    fs.release();
}