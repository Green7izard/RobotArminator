#include "Camera.hpp"

namespace Vision
{

    Camera::Camera(int cameraNumber, bool mirrored = false) : cameraNumber(cameraNumber), mirrored(mirrored)
    {
    }


    Camera::~Camera()
    {
    }
}
