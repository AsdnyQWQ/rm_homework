class Angle
{
    private:
        const double gravity;//定义重力加速度常量
        double angle;  //定义发射角度
        double initial_v;//定义初速度
        double distance;//定义距离
        double max_distance;//定义最远攻击距离
        double height;//定义高度
        double time;//定义时间

    public:
        double solver( double d);
        double solver( double d, double h);
        Angle();
};