#pragma once
#include "IComputerVision.hpp"
#include "Table.hpp"
#include "Camera.hpp"

namespace Vision
{

    class TableFinder :
        public IComputerVision
    {
    private:
        //The Last position
        VisionPosition lastPosition;
        //The tables position in the screen
        Table tabel;
        //The camera wrapper that is used
        Camera camera;
    protected:
        /**
        * Updates the last known position and pushes the change
        * @param position the new VisionPosition
        */
        void setPosition(VisionPosition position);

    public:
        /**
        * Create a TableFinder
        *
        * @param orientation Where the camera is located
        * @param cam the camera that is used
        */
        TableFinder(Orientation orientation, Camera cam);
        virtual ~TableFinder();
        Table detectTable();
        VisionPosition convertToCoordinate(unsigned int X, unsigned int Y, std::time_t time);
        virtual void locateObject() = 0;
    };
}

