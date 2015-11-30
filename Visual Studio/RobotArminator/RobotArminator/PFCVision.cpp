#include "PFCVision.hpp"


namespace Vision {
    PFCVision::PFCVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
    }


    PFCVision::~PFCVision()
    {
    }

    void PFCVision::locateObject(cv::Mat &image, Position2D &position)
    {
        //TODO
    }
}
