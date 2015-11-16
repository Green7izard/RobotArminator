#pragma once

enum Orientation { UP, SIDE };

class IComputerVision
{
public:
   
    IComputerVision(Orientation orientation);
    virtual ~IComputerVision();
private:
    Orientation orientation;

};

