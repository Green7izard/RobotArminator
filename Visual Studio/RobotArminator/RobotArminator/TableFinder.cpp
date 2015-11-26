#include "TableFinder.hpp"
#include <ctime>


namespace Vision {

    using namespace RobotArminator;

    TableFinder::TableFinder(Orientation orientation, Camera* cam) : IComputerVision(orientation), camera(cam)
    {
        tabel = detectTable();
    }


    TableFinder::~TableFinder() {
    }

    void TableFinder::run() {
        cv::Mat cameraFrame;
        Position2D position;
        std::time_t time;
        while (true) {
            time = std::time(nullptr);
            camera->getCurrentImage(cameraFrame);
            locateObject(cameraFrame, position);
            setPosition(convertToCoordinate(position.X, position.Y, time));
            if (cv::waitKey(1) >= 0) break;
        }
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