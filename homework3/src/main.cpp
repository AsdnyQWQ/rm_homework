#include "Deetector.hpp"

void calibrate_camera();

int main()
{
    Detector detector;
    detector.detect();
    calibrate_camera();

    return 0;
}