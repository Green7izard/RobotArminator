#include "stdafx.h"
#include "PFCVision.hpp"


namespace Vision {


    PFCVision::PFCVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
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
        cv::inRange(image, cv::Scalar(minHue, minSat, minInt), cv::Scalar(maxHue, maxSat, maxInt), image);

        float totalX = 0;
        float totalY = 0;
        //cv::minMaxLoc(image, 0, 0, 0, &location);

        cv::Mat locations;   // output, locations of non-zero pixels
        cv::findNonZero(image, locations);//probably faster, but crashes

        float numberOfParticles = 0;
        for (int i = 0; i < locations.total(); i++) {
            cv::Point current = locations.at<cv::Point>(i);
            float currentXValue = current.x;
            float currentYValue = current.y;
            float weight = ((float)defaultWeight / 5);

            //If there is a last position try to change the weight
            if (isFilled(lastPosition))
            {
                //calculate simple distance
                float dist = std::abs(lastPosition.X - current.x) + std::abs(lastPosition.Y - current.y);
                weight += (float)weightFactor / ((dist * ((float)weightDecay / 10)) * 10 + 0.00000001);
            }

            totalX += currentXValue*weight;
            totalY += currentYValue*weight;
            numberOfParticles = numberOfParticles + weight;
        }


        //Drawing
        if (numberOfParticles > 0) {
#ifdef _DEBUG
            cv::Point location(totalX, totalY);
            cv::circle(image, location, 3, cv::Scalar(0, 255, 0), -1, 8, 0);// circle center     
            cv::circle(image, location, 50, cv::Scalar(0, 0, 255), 3, 8, 0);// circle outline
#endif
            position.X = (int)(totalX / numberOfParticles);
            position.Y = (int)(totalY / numberOfParticles);

            std::cout << numberOfParticles << " Found: " << position.X << "," << position.Y << std::endl;
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

        cv::createTrackbar("Weight for center", windowNameFiltered, &weightFactor, 200, 0);
        cv::createTrackbar("Weight decay", windowNameFiltered, &weightDecay, 200, 0);
        cv::createTrackbar("Default weight", windowNameFiltered, &weightDecay, 200, 0);

        while (true) {
            camera->getCurrentImage(cameraFrame);
            cv::imshow(windowName, cameraFrame);
            if (locateObject(cameraFrame, pos))
            {
                cv::circle(cameraFrame, cv::Point(pos.X, pos.Y), 10, cv::Scalar(0, 255, 0), -1, 8, 0);
            }
            cv::imshow(windowNameFiltered, cameraFrame);
            //Wait till escape is 
            if (cv::waitKey(33) >= (char)27) break;
        }
        cv::destroyWindow(windowName);
        cv::destroyWindow(windowNameFiltered);
        resetPosition();
    }


    //Color Tracker



    ColorFilter::ColorFilter(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
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

        /*
        cv::vector<cv::Point> locations;   // output, locations of non-zero pixels
        if (cv::countNonZero(image) > 0) {
            cv::findNonZero(filteredFrame, locations);//probably faster, but crashes
            location = locations[0];
        }
        else {
            return false;
        }
        */


        //Drawing
        if (location.x != 0 || location.y != 0) {
            cv::circle(image, location, 3, cv::Scalar(0, 255, 0), -1, 8, 0);// circle center     
            cv::circle(image, location, 50, cv::Scalar(0, 0, 255), 3, 8, 0);// circle outline
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
        std::string windowNameFiltered = "PFC Filtered: - " + std::to_string(camera->getCameraNumber());
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

        while (true) {
            camera->getCurrentImage(cameraFrame);
            cv::imshow(windowName, cameraFrame);
            if (locateObject(cameraFrame, pos))
            {
                cv::circle(cameraFrame, cv::Point(pos.X, pos.Y), 10, cv::Scalar(0, 255, 0), -1, 8, 0);
            }
            cv::imshow(windowNameFiltered, cameraFrame);
            //Wait till escape is 
            if (cv::waitKey(33) >= (char)27) break;
        }
        cv::destroyWindow(windowName);
        cv::destroyWindow(windowNameFiltered);
    }
}
