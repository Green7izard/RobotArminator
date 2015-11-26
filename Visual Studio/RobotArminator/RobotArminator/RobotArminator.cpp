// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "Camera.hpp"


int main(int argc, char* argv[])
{
    char * win= "window";
    cv::namedWindow(win, cv::WINDOW_AUTOSIZE);
    Vision::Camera cam(0);
    std::cout << "Start Camera with size " <<cam.getWidth()<<"x"<< cam.getHeight()<<"\n";
    cv::Mat cameraFrame;
    std::cout << "Frame Created\n";
    while (true) {
        cam.getCurrentImage(cameraFrame);
        cv::Size s = cameraFrame.size();
        std::cout << "Got Image\n";
        std::cout << s.width << "x" << s.height << "\n";
        imshow(win, cameraFrame);
        std::cout << "Shown the data\n";
        if (cv::waitKey(1) >= 0) break;
    }
    return 0;
}

