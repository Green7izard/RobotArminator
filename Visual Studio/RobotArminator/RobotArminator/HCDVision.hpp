#pragma once
#include "TableFinder.hpp"

namespace Vision {
    /**
    * Vision class that uses Canny Edge Detection and Hough Circle Detection
    */
    class CannyHCDVision :
        public TableFinder
    {

    private:
        //If values have a gradient higher then this it is accepted as a edge
        int cannyUpperThreshhold = 300;
        //The lower this value, the more circles it should find
        int accumulatorThreshold = 30;

        //Parameters for ball size
        int maxRadius = 300;
        int minRadius = 10;

        double lastX = 0;
        double lastY = 0;

    public:
        CannyHCDVision(Orientation orientation, Camera* cam, double length, double width);
        virtual ~CannyHCDVision();

        virtual bool locateObject(cv::Mat &image, Position2D &position) override;

        virtual void calibrate() override;
    };

    /**
    * Vision class that uses Canny Edge Detection and Hough Circle Detection
    */
    class ColorHCDVision :
        public TableFinder
    {
    public:
        //If values have a gradient higher then this it is accepted as a edge
        int cannyUpperThreshhold = 300;
        //The lower this value, the more circles it should find
        int accumulatorThreshold = 25;
        //Hue/Color 0-180
        int minHue = 7;
        int maxHue = 42;
        //Saturation 0-255
        int minSat = 10;
        int maxSat = 222;
        //Value/Intensity 0-255
        int minInt = 125;
        int maxInt = 255;

        //Parameters for ball size
        int maxRadius = 300;
        int minRadius = 10;


        ColorHCDVision(Orientation orientation, Camera* cam, double length, double width);
        virtual ~ColorHCDVision();

        virtual bool locateObject(cv::Mat &image, Position2D &position) override;

        virtual void calibrate() override;
    };
}

