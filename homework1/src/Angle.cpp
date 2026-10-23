#include"Angle.hpp"
#include<iostream>
#include<cmath>

Angle::Angle():gravity(9.8),angle(0),initial_v(10.0),distance(5.0),max_distance(0),height(1.0)
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
        return -1.0;//超过距离，返回-1表示无法命中
}

double Angle::solver(int d,int h)
{
    distance = d;
    height = h;

    //分布计算结果，详见草稿
    double ch1 = height + gravity * std::pow(distance,2)/std::pow(initial_v,2);
    double ch2 = std::sqrt(distance * distance + height * height);
    double ch3 = std::atan(height/distance);

     if(ch1 <= ch2)
    {
        angle = (asin(ch1/ch2)+ch3)/2;
        return angle;
    }
    else
        return -1.0;//返回-1表示无法命中
}