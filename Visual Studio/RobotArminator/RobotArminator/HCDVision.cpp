#include "HCDVision.hpp"


namespace Vision {

    using namespace cv;

    //Canny Edge Detection
    CannyHCDVision::CannyHCDVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
        createTrackbar("Min Radius", "window", &minRadius, 256, 0);
        createTrackbar("Max Radius", "window", &maxRadius, 500, 0);
        createTrackbar("Canny Threshhold", "window", &cannyUpperThreshhold, 300, 0);
        createTrackbar("accumulator threshold", "window", &accumulatorThreshold, 100, 0);
    }


    CannyHCDVision::~CannyHCDVision()
    {
    }

    bool CannyHCDVision::locateObject(cv::Mat &image, Position2D &position)
    {
        //Turn it to greys
        cvtColor(image, image, COLOR_BGR2GRAY);
        //Blur it
        GaussianBlur(image, image, Size(9, 9), 2, 2);
        

        std::vector<Vec3f> circles;
        HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, image.rows / 8, std::max(cannyUpperThreshhold, 1), std::max(accumulatorThreshold , 1), minRadius, maxRadius);
        int closestDistance = -1;
        for (int i = 0; i < circles.size(); i++)
        {
            float x = circles[i][0];
            float y = circles[i][1];
            float pytho = x*x + y*y;
            if (pytho < closestDistance||i == 0)
            {
                closestDistance = pytho;
                Point center(cvRound(x), cvRound(y));
                position.X = x;
                position.Y = y;
#ifdef _DEBUG
                int radius = cvRound(circles[i][2]);
                circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
                circle(image, center, radius, Scalar(0, 255, 255), 3, 8, 0);
                //std::cout << "Found: " << x << "," << y << "\n";
#endif
            }
        }
        return circles.size() > 0;
    }

    //Color Filter
    ColorHCDVision::ColorHCDVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
        createTrackbar("Min Hue", "window", &minHue, 180, 0);
        createTrackbar("Max Hue", "window", &maxHue, 180, 0);
        createTrackbar("Min Sat", "window", &minSat, 256, 0);
        createTrackbar("Max Sat", "window", &maxSat, 256, 0);
        createTrackbar("Min Int", "window", &minInt, 256, 0);
        createTrackbar("Max Int", "window", &maxInt, 256, 0);
        createTrackbar("Min Radius", "window", &minRadius, 256, 0);
        createTrackbar("Max Radius", "window", &maxRadius, 500, 0);
        createTrackbar("Canny Threshhold", "window", &cannyUpperThreshhold, 300, 0);
        createTrackbar("accumulator threshold", "window", &accumulatorThreshold, 100, 0);
    }


    ColorHCDVision::~ColorHCDVision()
    {
    }

    bool ColorHCDVision::locateObject(Mat &image, Position2D &position)
    {
        GaussianBlur(image, image, Size(9,9), 2,2);
        //Turn To HSV colors
        cvtColor(image, image, CV_BGR2HSV);
        //Filter colors
        //Scalar in HSV: Hue(tint), Saturation(verzadiging), Value/intensity
        inRange(image, Scalar(minHue, minSat, minInt,0), Scalar(maxHue, maxSat, maxInt, 100), image);
        
        //bitwise_not(image, image);

        std::vector<Vec3f> circles;
        HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, image.rows / 8, cannyUpperThreshhold+1, accumulatorThreshold+1, minRadius, maxRadius);
        int closestDistance = -1;
        for (int i = 0; i < circles.size(); i++)
        {
            float x = circles[i][0];
            float y = circles[i][1];
            float pytho = x*x + y*y;
            if (pytho < closestDistance || i==0)
            {
                closestDistance = pytho;
                position.X = x;
                position.Y = y;
#ifdef _DEBUG
                int radius = cvRound(circles[i][2]);
                circle(image, Point(x, y), 3, Scalar(0, 255, 0), -1, 8, 0);
                circle(image, Point(x, y), radius, Scalar(0, 255, 255), 3, 8, 0);
                //std::cout << "Found: " << x << "," << y << "\n";
#endif
            }
        }
        return circles.size() > 0;
    }
}
