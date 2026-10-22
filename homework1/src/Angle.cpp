#include"Angle.hpp"
#include<iostream>
#include<cmath>

Angle::Angle():gravity(9.8f),angle(0),initial_v(10),distance(5),max_distance(0)
{
    //构造函数  
};

double Angle::solver(int d)
{
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

double Angle::solver(int d,int h)
{
    //请先忽略
}