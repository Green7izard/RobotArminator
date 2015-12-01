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
        int cannyUpperThreshhold = 314;
        //The lower this value, the more circles it should find
        int accumulatorThreshold = 37;

        //Parameters for ball size
        int maxRadius = 300;
        int minRadius = 10;

        float lastX = 0;
        float lastY = 0;
    public:
        CannyHCDVision(Orientation orientation, Camera* cam);
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
        int cannyUpperThreshhold = 200;
        //The lower this value, the more circles it should find
        int accumulatorThreshold = 50;
        //Hue/Color 0-180
        int minHue = 84;
        int maxHue = 106;
        //Saturation 0-255
        int minSat = 0;
        int maxSat = 256;
        //Value/Intensity 0-255
        int minInt = 117;
        int maxInt = 255;

        //Parameters for ball size
        int maxRadius = 100;
        int minRadius = 10;


        ColorHCDVision(Orientation orientation, Camera* cam);
        virtual ~ColorHCDVision();

        virtual bool locateObject(cv::Mat &image, Position2D &position) override;

        virtual void calibrate() override;
    };
}

