#include "PFCVision.hpp"


namespace Vision {
    PFCVision::PFCVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
		calibrate();
    }


    PFCVision::~PFCVision()
    {
    }

    bool PFCVision::locateObject(cv::Mat &image, Position2D &position)
    {
		//filter
		cv::cvtColor(image, image, cv::COLOR_BGR2HSV);
		cv::inRange(image, cv::Scalar(6 * 1.8, 80 * 2.5, 80 * 2.5), cv::Scalar(40 * 1.8, 255, 255), image);
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
}
