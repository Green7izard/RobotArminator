// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "Camera.hpp"


int main(int argc, char* argv[])
{

    Vision::Camera cam(0, false);
    std::cout << "Start Camera";
    while (true) {
        cv::Mat cameraFrame;
        cam.getCurrentImage(cameraFrame);
        imshow("cam", cameraFrame);
    }
    return 0;
}

