#include"Angle.hpp"
#include<iostream>

int main()
{
    //定义距离模拟实际发射环境
    double distance = 4.0;
    double height = 2.0;

    double angle;//接受返回值
    double angle_radian;//弧度制表角度
    double angle_degree;//角度制表角度
    double pi = 3.141592653589;//定义圆周率
   

    Angle shooter1;
    //判断h是否为0以判断调用哪个函数
    if(height == 0)
        angle = shooter1.solver(distance);
    else
        angle = shooter1.solver(distance,height);


    if(angle == -1.0)
        std::cout << "无法命中目标" << std::endl;//判断能否命中
    else
    {
        angle_radian = angle;
        angle_degree = angle*180.0/pi;//换算为角度制
        std::cout << "抬升角大小为（弧度制）：" << angle_radian << 
        std::endl << "抬升角大小为（角度制）：" << angle_degree << std::endl;
    }
    return 0;
}