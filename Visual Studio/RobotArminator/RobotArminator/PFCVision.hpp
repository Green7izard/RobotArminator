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
    };
}

