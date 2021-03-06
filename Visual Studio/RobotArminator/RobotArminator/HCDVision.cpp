#include "stdafx.h"
#include "HCDVision.hpp"


namespace Vision {

    using namespace cv;

    //Canny Edge Detection
    CannyHCDVision::CannyHCDVision(Orientation orientation, Camera* cam, double tableLength, double tableWidth) :TableFinder(orientation, cam, tableLength, tableWidth)
    {
        calibrate();
    }


    CannyHCDVision::~CannyHCDVision()
    {
    }

    bool CannyHCDVision::locateObject(cv::Mat &image, Position2D &position)
    {
        //Turn it to greys
        cvtColor(image, image, COLOR_BGR2GRAY);
        //Blur it
        GaussianBlur(image, image, Size(3, 3), 0, 0);


        std::vector<Vec3f> circles;
        HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, image.rows / 8, std::max(cannyUpperThreshhold, 1), std::max(accumulatorThreshold, 1), minRadius, maxRadius);
        double closestDistance = -1;
        for (unsigned int i = 0; i < circles.size(); i++)
        {
            double x = circles[i][0];
            double y = circles[i][1];
            double pytho = x*x + y*y;
#ifdef _DEBUG
            Point center(cvRound(x), cvRound(y));
            int radius = cvRound(circles[i][2]);
            circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
            circle(image, center, radius, Scalar(0, 255, 255), 3, 8, 0);
            //std::cout << "Found: " << x << "," << y << "\n";
#endif
            if (pytho < closestDistance || i == 0)
            {
                closestDistance = pytho;

                position.X = static_cast<int>(x);
                position.Y = static_cast<int>(y);
            }
        }
        return circles.size() > 0;
    }

    void CannyHCDVision::calibrate()
    {
        TableFinder::calibrate();
        std::string windowName = "HCDVision:" + std::to_string(camera->getCameraNumber());
        std::string windowNameCanny = "HCDVision Canny:" + std::to_string(camera->getCameraNumber());
        Vision::Position2D pos;
        Mat cameraFrame;
        Mat cannyFrame;

        std::cout << "Starting calibrating: " << windowName << endl;
        std::cout << "Adjust the sliders in the windows and press 'esc' when the values are correct!" << endl;

        namedWindow(windowName, cv::WINDOW_AUTOSIZE);
        namedWindow(windowNameCanny, cv::WINDOW_AUTOSIZE);
        createTrackbar("Min Radius", windowName, &minRadius, 256, 0);
        createTrackbar("Max Radius", windowName, &maxRadius, 500, 0);
        createTrackbar("Canny Threshhold", windowNameCanny, &cannyUpperThreshhold, 400, 0);
        createTrackbar("accumulator threshold", windowName, &accumulatorThreshold, 100, 0);
        while (waitKey(33) != (char)27) {
            if (camera->getCurrentImage(cameraFrame))
            {

                if (locateObject(cameraFrame, pos))
                {
                    circle(cameraFrame, Point(pos.X, pos.Y), 10, Scalar(0, 255, 0), -1, 8, 0);
                }

                Canny(cameraFrame, cannyFrame, cannyUpperThreshhold / 3, cannyUpperThreshhold, 3);

                imshow(windowName, cameraFrame);
                imshow(windowNameCanny, cannyFrame);
            }

        }
        destroyWindow(windowName);
        destroyWindow(windowNameCanny);
    }

    //Color Filter
    ColorHCDVision::ColorHCDVision(Orientation orientation, Camera* cam, double tableLength, double tableWidth) :TableFinder(orientation, cam, tableLength, tableWidth)
    {
        calibrate();
    }


    ColorHCDVision::~ColorHCDVision()
    {
    }

    bool ColorHCDVision::locateObject(Mat &image, Position2D &position)
    {

        //Turn To HSV colors
        cvtColor(image, image, CV_BGR2HSV);
        //Filter colors
        //Scalar in HSV: Hue(tint), Saturation(verzadiging), Value/intensity
        inRange(image, Scalar(minHue, minSat, minInt, 0), Scalar(maxHue, maxSat, maxInt, 100), image);

        GaussianBlur(image, image, Size(9, 9), 0, 0);

        //bitwise_not(image, image);

        std::vector<Vec3f> circles;
        HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, image.rows / 8, cannyUpperThreshhold + 1, accumulatorThreshold + 1, minRadius, maxRadius);
        double closestDistance = -1;
        for (unsigned int i = 0; i < circles.size(); i++)
        {
            double x = circles[i][0];
            double y = circles[i][1];
            double pytho = x*x + y*y;

#ifdef _DEBUG
            int radius = cvRound(circles[i][2]);
            circle(image, Point(static_cast<int>(x), static_cast<int>(y)), 3, Scalar(0, 255, 0), -1, 8, 0);
            circle(image, Point(static_cast<int>(x), static_cast<int>(y)), radius, Scalar(0, 255, 255), 3, 8, 0);
#endif

            if (pytho < closestDistance || i == 0)
            {
                closestDistance = pytho;
                position.X = static_cast<int>(x);
                position.Y = static_cast<int>(y);
            }
        }
        return circles.size() > 0;
    }

    void ColorHCDVision::calibrate()
    {
        TableFinder::calibrate();
        std::string windowName = "ColorHCDVision:" + std::to_string(camera->getCameraNumber());
        std::string windowNameCanny = "ColorHCDVision Canny:" + std::to_string(camera->getCameraNumber());
        Vision::Position2D pos;
        Mat cameraFrame;
        Mat cannyFrame;

        std::cout << "Starting calibrating: " << windowName << endl;
        std::cout << "Adjust the sliders in the windows and press 'esc' when the values are correct!" << endl;

        namedWindow(windowName, cv::WINDOW_AUTOSIZE);
        namedWindow(windowNameCanny, cv::WINDOW_AUTOSIZE);
        createTrackbar("Min Hue", windowName, &minHue, 180, 0);
        createTrackbar("Max Hue", windowName, &maxHue, 180, 0);
        createTrackbar("Min Sat", windowName, &minSat, 256, 0);
        createTrackbar("Max Sat", windowName, &maxSat, 256, 0);
        createTrackbar("Min Int", windowName, &minInt, 256, 0);
        createTrackbar("Max Int", windowName, &maxInt, 256, 0);
        createTrackbar("Min Radius", windowName, &minRadius, 256, 0);
        createTrackbar("Max Radius", windowName, &maxRadius, 500, 0);
        createTrackbar("Canny Threshhold", windowNameCanny, &cannyUpperThreshhold, 300, 0);
        createTrackbar("accumulator threshold", windowName, &accumulatorThreshold, 100, 0);
        while (waitKey(33) != static_cast<char>(27)) {
            if (camera->getCurrentImage(cameraFrame))
            {
                if (locateObject(cameraFrame, pos))
                {
                    circle(cameraFrame, Point(pos.X, pos.Y), 10, Scalar(0, 255, 0), -1, 8, 0);
                }

                Canny(cameraFrame, cannyFrame, cannyUpperThreshhold / 3, cannyUpperThreshhold, 3);
                imshow(windowName, cameraFrame);
                imshow(windowNameCanny, cannyFrame);
            }
        }
        destroyWindow(windowName);
        destroyWindow(windowNameCanny);
    }

}
