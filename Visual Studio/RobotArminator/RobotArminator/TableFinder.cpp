#include "TableFinder.hpp"
#include <ctime>


namespace Vision {

    using namespace RobotArminator;

    TableFinder::TableFinder(Orientation orientation, Camera* cam) : IComputerVision(orientation), camera(cam)
    {
        //calibrate();
        //tabel = detectTable();
        running = false;
    }


    TableFinder::~TableFinder() {
    }

    void TableFinder::stop() 
    {
        //TODO
        running = false;
    }

    void TableFinder::run() {
        running=true;
        cv::Mat cameraFrame;
        Position2D position;
        timePoint time;
        calibrate();
        //FIXME STOPCOMMAND?
        while (running) {
            
            time = Clock::now();
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

    VisionPosition TableFinder::convertToCoordinate(Position2D &position, timePoint time)
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
        calibrate();
        //tabel = detectTable();
    }

    void TableFinder::calibrate() 
    {
        //TODO
        std::cout << "FAIL";
    }

}