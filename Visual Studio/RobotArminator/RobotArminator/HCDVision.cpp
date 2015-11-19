#include "HCDVision.hpp"


namespace Vision {
    HCDVision::HCDVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
    }


    HCDVision::~HCDVision()
    {
    }
}
