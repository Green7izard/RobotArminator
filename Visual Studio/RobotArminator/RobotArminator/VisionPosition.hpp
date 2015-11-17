#pragma once
#include <ctime>
#include "Orientation.hpp"
struct VisionPosition
{
public:
    VisionPosition();
    VisionPosition(float X, float Y, std::time_t time, Orientation orientation);
    ~VisionPosition();
    float X;
    float Y;
    std::time_t time;
    Orientation orientation;
};

