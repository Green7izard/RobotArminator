#include "stdafx.h"
#include "PFCVision.hpp"
#include "configuration.hpp"
#include <sstream>
#include <iostream>
#include <map>
#include <string>

namespace Vision {


    PFCVision::PFCVision(Orientation orientation, Camera* cam, double  tableLength, double tableWidth) :TableFinder(orientation, cam, tableLength, tableWidth)
    {
        resetPosition();
        calibrate();
    }


    PFCVision::~PFCVision()
    {
    }

    bool PFCVision::isFilled(Position2D & point)
    {
        return point.X >= 0 && point.Y >= 0;
    }

    void PFCVision::resetPosition()
    {
        lastPosition.X = -1;
        lastPosition.Y = -1;
    }

    bool PFCVision::locateObject(cv::Mat &image, Position2D &position)
    {
        //filter
        cv::cvtColor(image, image, cv::COLOR_BGR2HSV);

        if (erodeDilate > 0) {
            cv::erode(image, image, cv::Mat(), cv::Point(-1, -1), erodeDilate);
            cv::dilate(image, image, cv::Mat(), cv::Point(-1, -1), erodeDilate);
        }
        cv::inRange(image, cv::Scalar(minHue, minSat, minInt), cv::Scalar(maxHue, maxSat, maxInt), image);

        double totalX = 0;
        double totalY = 0;
        //cv::minMaxLoc(image, 0, 0, 0, &location);

        cv::Mat locations;   // output, locations of non-zero pixels
        cv::findNonZero(image, locations);//probably faster, but crashes

        double numberOfParticles = 0;
        for (unsigned int i = 0; i < locations.total(); i++) {
            cv::Point current = locations.at<cv::Point>(i);
            double currentXValue = static_cast<double>(current.x);
            double currentYValue = static_cast<double>(current.y);
            double weight = static_cast<double>(defaultWeight) / 10.0;

            //If there is a last position try to change the weight
            if (isFilled(lastPosition))
            {
                //calculate simple distance
                double dist = static_cast<double>(std::abs(lastPosition.X - current.x) + std::abs(lastPosition.Y - current.y));
                weight += static_cast<double>(weightFactor) / static_cast<double>((dist * (static_cast<double>(weightDecay) / 10.0)) * 10.0 + 1.0);
            }

            totalX += currentXValue*weight;
            totalY += currentYValue*weight;
            numberOfParticles = numberOfParticles + weight;
        }


        //Drawing
        if (numberOfParticles > 0) {

            position.X = static_cast<int>(totalX / numberOfParticles);
            position.Y = static_cast<int>(totalY / numberOfParticles);
            //std::cout << numberOfParticles << " Found: " << position.X << "," << position.Y << std::endl;
            lastPosition = position;
            return true;
        }
        return false;
    }

    void PFCVision::calibrate()
    {
        resetPosition();
        TableFinder::calibrate();
        std::string windowName = "Camera - " + std::to_string(camera->getCameraNumber());
        std::string windowNameFiltered = "PFC Filtered: - " + std::to_string(camera->getCameraNumber());
        Vision::Position2D pos;
        cv::Mat cameraFrame;
        cv::Mat orignalFrame;

        std::cout << "Starting calibrating: " << windowName << endl;
        std::cout << "Adjust the sliders in the windows and press 'esc' when the values are correct!" << endl;

        cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
        cv::namedWindow(windowNameFiltered, cv::WINDOW_AUTOSIZE);

        if (orientation == TOP) {
            ConfigFile cfg("CameraConfigTop.cfg");
            minHue = cfg.getValueOfKey<int>("minHue");
            maxHue = cfg.getValueOfKey<int>("maxHue");
            minSat = cfg.getValueOfKey<int>("minSat");
            minInt = cfg.getValueOfKey<int>("minInt");
        }
        else {
            ConfigFile cfg("CameraConfigSide.cfg");
            minHue = cfg.getValueOfKey<int>("minHue");
            maxHue = cfg.getValueOfKey<int>("maxHue");
            minSat = cfg.getValueOfKey<int>("minSat");
            minInt = cfg.getValueOfKey<int>("minInt");
        }

        cv::createTrackbar("Min Hue", windowNameFiltered, &minHue, 180, 0);
        cv::createTrackbar("Max Hue", windowNameFiltered, &maxHue, 180, 0);
        cv::createTrackbar("Min Sat", windowNameFiltered, &minSat, 255, 0);
        cv::createTrackbar("Max Sat", windowNameFiltered, &maxSat, 255, 0);
        cv::createTrackbar("Min Int", windowNameFiltered, &minInt, 255, 0);
        cv::createTrackbar("Max Int", windowNameFiltered, &maxInt, 255, 0);
        cv::createTrackbar("Erode/Dilate", windowNameFiltered, &erodeDilate, 20, 0);

        cv::createTrackbar("Weight for center", windowNameFiltered, &weightFactor, 200, 0);
        cv::createTrackbar("Weight decay", windowNameFiltered, &weightDecay, 200, 0);
        cv::createTrackbar("Default weight", windowNameFiltered, &weightDecay, 200, 0);

        while (cv::waitKey(33) != (char)27) {
            camera->getCurrentImage(cameraFrame);

            cameraFrame.copyTo(orignalFrame);

            if (locateObject(cameraFrame, pos))
            {
                cv::circle(cameraFrame, cv::Point(pos.X, pos.Y), 50, cv::Scalar(100, 255, 255), 2, 8, 0);
                cv::circle(orignalFrame, cv::Point(pos.X, pos.Y), 10, cv::Scalar(0, 255, 0), -1, 8, 0);
                cv::circle(orignalFrame, cv::Point(pos.X, pos.Y), 50, cv::Scalar(0, 0, 255), 3, 8, 0);
            }
            cv::imshow(windowName, orignalFrame);
            cv::imshow(windowNameFiltered, cameraFrame);
            //Wait till escape is 
        }
        cv::destroyWindow(windowName);
        cv::destroyWindow(windowNameFiltered);
        resetPosition();
    }


    //Color Tracker



    ColorFilter::ColorFilter(Orientation orientation, Camera* cam, double tableLength, double tableWidth) :TableFinder(orientation, cam, tableLength, tableWidth)
    {
        calibrate();
    }


    ColorFilter::~ColorFilter()
    {
    }

    bool ColorFilter::locateObject(cv::Mat &image, Position2D &position)
    {
        //filter
        cv::cvtColor(image, image, cv::COLOR_BGR2HSV);
        cv::inRange(image, cv::Scalar(minHue, minSat, minInt), cv::Scalar(maxHue, maxSat, maxInt), image);
        //Take out single pixel errors
        //cv::erode(image, image, cv::Mat(), cv::Point(-1, -1), 1);
        //cv::dilate(image, image, cv::Mat(), cv::Point(-1, -1), 1);

        //calculating
        cv::Point location;
        cv::minMaxLoc(image, 0, 0, 0, &location);

        //Drawing
        if (location.x != 0 || location.y != 0) {
            position.X = location.x;
            position.Y = location.y;
            return true;
        }
        return false;
    }

    void ColorFilter::calibrate()
    {
        TableFinder::calibrate();
        std::string windowName = "Camera - " + std::to_string(camera->getCameraNumber());
        std::string windowNameFiltered = "Color Filtered: - " + std::to_string(camera->getCameraNumber());
        Vision::Position2D pos;
        cv::Mat cameraFrame;

        std::cout << "Starting calibrating: " << windowName << endl;
        std::cout << "Adjust the sliders in the windows and press 'esc' when the values are correct!" << endl;

        cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
        cv::namedWindow(windowNameFiltered, cv::WINDOW_AUTOSIZE);

        cv::createTrackbar("Min Hue", windowNameFiltered, &minHue, 180, 0);
        cv::createTrackbar("Max Hue", windowNameFiltered, &maxHue, 180, 0);
        cv::createTrackbar("Min Sat", windowNameFiltered, &minSat, 255, 0);
        cv::createTrackbar("Max Sat", windowNameFiltered, &maxSat, 255, 0);
        cv::createTrackbar("Min Int", windowNameFiltered, &minInt, 255, 0);
        cv::createTrackbar("Max Int", windowNameFiltered, &maxInt, 255, 0);

        while (cv::waitKey(33) != (char)27) {
            camera->getCurrentImage(cameraFrame);
            cv::imshow(windowName, cameraFrame);
            if (locateObject(cameraFrame, pos))
            {
                cv::circle(cameraFrame, cv::Point(pos.X, pos.Y), 10, cv::Scalar(0, 255, 0), -1, 8, 0);
            }
            cv::imshow(windowNameFiltered, cameraFrame);
        }
        cv::destroyWindow(windowName);
        cv::destroyWindow(windowNameFiltered);
    }
}
