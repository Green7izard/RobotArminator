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

