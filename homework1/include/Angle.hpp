class Angle
{
    private:
        const float gravity;//定义重力加速度常量
        double angle;  //定义发射角度
        int initial_v;//定义初速度
        int distance;//定义距离
        double max_distance;//定义最远攻击距离
    public:
        double solver(int v, int d);
        Angle();
};