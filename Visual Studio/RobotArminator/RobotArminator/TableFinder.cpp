#include "TableFinder.hpp"


namespace Vision {

    using namespace RobotArminator;
    
    TableFinder::TableFinder(Orientation orientation, Camera cam) : IComputerVision(orientation), camera(cam)
    {
        tabel = detectTable();
    }
    

    TableFinder::~TableFinder() {
    }

    void TableFinder::setPosition(VisionPosition position)
    {
        lastPosition = position;
        notify(position);
    }

    Table TableFinder::detectTable() 
    {
        //TODO
        return Table();
    }
    /*
    VisionPosition TableFinder::convertToCoordinate(unsigned int X, unsigned int Y, timePoint)
    {
        //TODO
        return VisionPosition();
    }
    */
}