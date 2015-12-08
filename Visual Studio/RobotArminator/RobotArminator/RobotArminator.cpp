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
    
    Vision::Camera cam(0);
    cam.setSize(1280, 720);
    Vision::Position2D pos;
    std::cout << "Start Camera with size " <<cam.getWidth()<<"x"<< cam.getHeight()<<"\n";
    cv::Mat cameraFrame;
    Vision::ColorHCDVision HCD(RobotArminator::TOP, &cam);
    std::cout << "Frame Created\n";

    cv::namedWindow(win, cv::WINDOW_AUTOSIZE);
    while (true) {
        cam.getCurrentImage(cameraFrame);
        cv::Size s = cameraFrame.size();
        //std::cout << "Got Image\n";
        //std::cout << s.width << "x" << s.height << "\n";
        if (HCD.locateObject(cameraFrame, pos))
        {
            std::cout << "Found at: " << pos.X << "," << pos.Y << std::endl;
            RobotArminator::VisionPosition newPos = HCD.convertToCoordinate(pos, RobotArminator::Clock::now(), s.width, s.height);
            std::cout << "Converted to: " << newPos.X << "," << newPos.Y << std::endl;
        }
        else
        {
            std::cout << "Could not find the ball... Last at: " << pos.X << "," << pos.Y << std::endl;
        }
        imshow(win, cameraFrame);
        //std::cout << "Shown the data\n";
        if (cv::waitKey(1) >= 0) break;
    }
    return 0;
}

