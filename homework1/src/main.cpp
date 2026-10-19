#include"Angle.hpp"
#include<iostream>

int main()
{
    //定义初速度和距离模拟实际发射环境
    int initial_v = 10;
    int distance = 5;

    double angle_radian;//弧度制表角度
    double angle_degree;//角度制表角度
    double pi = 3.141592653589;//定义圆周率
   

    Angle Angle;
    double angel = Angle.solver(initial_v,distance);
    if(angel == -1.0)
        std::cout << "无法命中目标" << std::endl;//判断能否命中
    else
    {
        angle_radian = angel;
        angle_degree = angel*180.0/pi;//换算为角度制
        std::cout << "抬升角大小为（弧度制）：" << angle_radian << 
        std::endl << "抬升角大小为（角度制）：" << angle_degree << std::endl;
    }
    return 0;
}