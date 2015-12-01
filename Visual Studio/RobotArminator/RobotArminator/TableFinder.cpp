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
        //FIXME STOPCOMMAND?
        while (true) {
            
            time(&time);
            camera->getCurrentImage(cameraFrame);
            if (locateObject(cameraFrame, position))
            {
                setPosition(convertToCoordinate(position, time));
            }
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

    VisionPosition TableFinder::convertToCoordinate(Position2D &position, std::time_t time)
    {
        //TODO Change it based on the table
        VisionPosition pos;
        pos.X = (float)position.X;
        pos.Y = (float)position.Y;
        pos.time = time;
        return pos;
    }

    void TableFinder::updateImageSize(unsigned int X, unsigned int Y)
    {
        camera->setSize(X, Y);
        tabel = detectTable();
    }

}