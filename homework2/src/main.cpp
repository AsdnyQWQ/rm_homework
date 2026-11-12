#include"Detector.hpp"

int main()
{   
    std::string path = std::string(VIDEO_PATH) + "/p.mp4";

    Detector detector;
    detector.detect(path);
    return 0;
} 