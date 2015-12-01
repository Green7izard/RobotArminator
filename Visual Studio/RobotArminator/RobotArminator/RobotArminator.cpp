// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "Camera.hpp"
#include "HCDVision.hpp"
#include "Orientation.hpp"


int main(int argc, char* argv[])
{
    char * win= "window";
    cv::namedWindow(win, cv::WINDOW_AUTOSIZE);
    Vision::Camera cam(0);
    Vision::Position2D pos;
    std::cout << "Start Camera with size " <<cam.getWidth()<<"x"<< cam.getHeight()<<"\n";
    cv::Mat cameraFrame;
    Vision::CannyHCDVision HCD(RobotArminator::SIDE, &cam);
    std::cout << "Frame Created\n";
    while (true) {
        cam.getCurrentImage(cameraFrame);
        cv::Size s = cameraFrame.size();
        //std::cout << "Got Image\n";
        //std::cout << s.width << "x" << s.height << "\n";
        if (HCD.locateObject(cameraFrame, pos))
        {
            std::cout << "Found at: " << pos.X << "," << pos.Y << "\n";
        }
        else
        {
            std::cout << "Could not find the ball... Last at: " << pos.X << "," << pos.Y << "\n";
        }
        imshow(win, cameraFrame);
        //std::cout << "Shown the data\n";
        if (cv::waitKey(1) >= 0) break;
    }
    return 0;
}

