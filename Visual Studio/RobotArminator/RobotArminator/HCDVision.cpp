#include "HCDVision.hpp"


namespace Vision {
    HCDVision::HCDVision(Orientation orientation, Camera* cam) :TableFinder(orientation, cam)
    {
    }


    HCDVision::~HCDVision()
    {
    }

    void HCDVision::locateObject(cv::Mat &image, Position2D &position)
    {
        //TODO
    }
}
