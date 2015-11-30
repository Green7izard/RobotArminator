#pragma once
#include "TableFinder.hpp"

namespace Vision {
    /**
    * Vision class that uses Canny Edge Detection and Hough Circle Detection
    */
    class HCDVision :
        public TableFinder
    {
    public:
        HCDVision(Orientation orientation, Camera* cam);
        virtual ~HCDVision();

        virtual void locateObject(cv::Mat &image, Position2D &position) override;
    };
}

