#include "pnp_solver.hpp"

void pnp_solver(cv::Mat img,std::vector<std::vector<cv::Point2f>> imagePoints)
{
    cv::FileStorage fs("calibration_result.yml", cv::FileStorage::READ);

    if (!fs.isOpened())
    {
        std::cout << "无法打开标定文件！" << std::endl;
    }

    else
    {
        float tagSize = 100.0f;

    
    // AprilTag 四个角点的三维坐标
    // 左上角作为原点
    std::vector<cv::Point3f> objectPoints = 
    {
        {0,       0,       0},  // 左上
        {tagSize, 0,       0},  // 右上
        {tagSize, tagSize, 0}, // 右下
        {0,       tagSize, 0}  // 左下
    };

    cv::Mat rvec,tvec,cameraMatrix,distCoeffs;


    // 读取相机内参和畸变参数
    fs["cameraMatrix"] >> cameraMatrix;
    fs["distCoeffs"] >> distCoeffs;

    fs.release();

    bool success = cv::solvePnP(objectPoints,imagePoints,cameraMatrix,distCoeffs,rvec,tvec);

    if(!success)
        {
            std::cout << "PnP解算失败!" << std::endl;
        }

    std::vector<std::vector<cv::Point3f>> obj_faces = 
    {
        objectPoints,

        // 右侧面
        {
            {tagSize, 0,       0},       // 左上
            {tagSize, 0,       tagSize}, // 右上
            {tagSize, tagSize, tagSize}, // 右下
            {tagSize, tagSize, 0}        // 左下
        },

        // 左侧面
        {
            {0, 0,       0},             // 左上
            {0, 0,       tagSize},       // 右上
            {0, tagSize, tagSize},       // 右下
            {0, tagSize, 0}              // 左下
        },

        // 上方的面
        {
            {0,       0, 0},             // 左上
            {tagSize, 0, 0},             // 右上
            {tagSize, 0, tagSize},       // 右下
            {0,       0, tagSize}        // 左下
        },

        // 下方的面
        {
            {0,       tagSize, 0},       // 左上
            {tagSize, tagSize, 0},       // 右上
            {tagSize, tagSize, tagSize}, // 右下
            {0,       tagSize, tagSize}  // 左下
        },

        // 背面（与正面相对）
        {
            {0,       0,       tagSize}, // 左上
            {tagSize, 0,       tagSize}, // 右上
            {tagSize, tagSize, tagSize}, // 右下
            {0,       tagSize, tagSize}  // 左下
        }
    };

    std::vector<std::vector<cv::Point2f>> pixel_faces;
    

    //将六个面的点的坐标转为像素坐标系下的坐标
    for (int i = 0; i < obj_faces.size(); i++)
    {
        projectPoints(
            obj_faces[i],
            rvec,
            tvec,
            cameraMatrix,
            distCoeffs,
            pixel_faces[i]
        );
    }


    std::vector<std::vector<cv::Point>> intPixelFaces(6);


    
    //将所有点的数据类型从float转换为int
    for (int i = 0; i < pixel_faces.size(); i++)
    {
        for (int j = 0; j < pixel_faces[i].size(); j++)
        {
            intPixelFaces[i].push_back(
            cv::Point(
                cvRound(pixel_faces[i][j].x),
                cvRound(pixel_faces[i][j].y)
            ));
        }
    }

    cv::fillPoly(img,pixel_faces,cv::Scalar(0,255,0));

    }
}
