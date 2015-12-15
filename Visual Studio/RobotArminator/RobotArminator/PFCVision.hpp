#pragma once
#include "TableFinder.hpp"

namespace Vision {
    /**
    * Vision class that uses Particle Filter-based Color Tracking
    */
    class PFCVision :
        public TableFinder
    {
    public:
        PFCVision(Orientation orientation, Camera* cam);
        virtual ~PFCVision();
        virtual bool locateObject(cv::Mat &image, Position2D &position) override;
        virtual void calibrate() override;
        //Check if the position has a value
        bool isFilled(Position2D &point);
        //Reset the current position
        void resetPosition();
    private:
        //The last known position
        Position2D lastPosition;

        //Hue/Color 0-180
        int minHue = 10;				// 6 * 1.8, 80 * 2.5, 80 * 2.5
        int maxHue = 72;			//40 * 1.8, 255, 255
        //Saturation 0-255
        int minSat = 200;
        int maxSat = 255;
        //Value/Intensity 0-255
        int minInt = 200;
        int maxInt = 255;

        //Weight at the exact point
        int weightFactor = 20;
        //Weight loss over distance
        int weightDecay = 10;
        //Default Weight
        int defaultWeight = 5;
    };

    class ColorFilter :
        public TableFinder
    {
    public:
        ColorFilter(Orientation orientation, Camera* cam);
        virtual ~ColorFilter();
        virtual bool locateObject(cv::Mat &image, Position2D &position) override;
        virtual void calibrate() override;
    private:
        //Hue/Color 0-180
        int minHue = 10;				// 6 * 1.8, 80 * 2.5, 80 * 2.5
        int maxHue = 72;			//40 * 1.8, 255, 255
                                    //Saturation 0-255
        int minSat = 200;
        int maxSat = 255;
        //Value/Intensity 0-255
        int minInt = 200;
        int maxInt = 255;
    };
}

