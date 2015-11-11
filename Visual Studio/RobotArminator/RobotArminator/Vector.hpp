#pragma once

namespace RobotArminator
{
    struct Vector
    {
    public:
        Vector();
        Vector(double x, double y, double z);
        virtual ~Vector();
        double x;
        double y;
        double z;
    };
}

