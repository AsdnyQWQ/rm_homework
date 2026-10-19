#include"Angle.hpp"
#include<iostream>
#include<cmath>

Angle::Angle():gravity(9.8f),angle(0),initial_v(0),distance(0),max_distance(0)
{
    //构造函数，对可自行改变的物理参数初始化为0，重力加速度初始化为9.8
};

double Angle::solver(int v,int d)
{
    initial_v = v;
    distance = d;
    
    max_distance = std::pow(initial_v,2)/gravity;//计算最大攻击距离
    if(distance <= max_distance)
    {
        angle = std::asin((distance*gravity)/(initial_v*initial_v))/2.0;
        return angle;
    }//未超过最大攻击距离时计算角度，结果为弧度制
    else
        return -1;//超过距离，返回-1表示无法命中
}