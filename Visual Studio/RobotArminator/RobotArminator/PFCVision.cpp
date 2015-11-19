#include "PFCVision.hpp"


namespace Vision {
    PFCVision::PFCVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
    }


    PFCVision::~PFCVision()
    {
    }
}
