#include "TableFinder.hpp"


namespace Vision {

    using namespace RobotArminator;

    TableFinder::TableFinder(Orientation orientation, Camera* cam) : IComputerVision(orientation), camera(cam)
    {
        tabel = detectTable();
    }


    TableFinder::~TableFinder() {
    }

    void TableFinder::run() {
        //TODO
    }

    void TableFinder::setPosition(VisionPosition position)
    {
        lastPosition = position;
        notify(lastPosition);
    }

    Table TableFinder::detectTable()
    {
        //TODO
        return Table();
    }

    VisionPosition TableFinder::convertToCoordinate(unsigned int X, unsigned int Y, std::time_t time)
    {
        //TODO
        return VisionPosition();
    }

    void TableFinder::updateImageSize(unsigned int X, unsigned int Y)
    {
        camera->setSize(X, Y);
        tabel = detectTable();
    }

}