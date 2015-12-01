#include "PFCVision.hpp"


namespace Vision {
    PFCVision::PFCVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
    }


    PFCVision::~PFCVision()
    {
    }

    bool PFCVision::locateObject(cv::Mat &image, Position2D &position)
    {
        //TODO
        return false;
    }
}
