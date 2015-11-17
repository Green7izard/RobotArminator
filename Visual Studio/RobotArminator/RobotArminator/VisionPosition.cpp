#include "stdafx.h"
#include "VisionPosition.hpp"


VisionPosition::VisionPosition()
{
}

VisionPosition::VisionPosition(float X, float Y, std::time_t time, Orientation orientation)
    : X(X), Y(Y), time(time), orientation(orientation)
{
}


VisionPosition::~VisionPosition()
{
}
