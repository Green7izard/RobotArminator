#pragma once
#include "IComputerVision.hpp"
#include "Table.hpp"
#include "Camera.hpp"

namespace Vision
{
    class TableFinder :
        public IComputerVision
    {

        friend class Camera;
    private:

        //The Last position
        VisionPosition lastPosition;

        //The tables position in the screen
        Table tabel;

        //The camera wrapper that is used
        Camera* camera;
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
        TableFinder(Orientation orientation, Camera* cam);

        /**
        * Deconstructor: Terminates the camera
        */
        virtual ~TableFinder();

        /**
        * Attempts to detect the table!
        * @return a Table struct with the values of the corners
        */
        Table detectTable();

        /**
        * Converts a X and Y position from the camera into a VisionPosition based on the coordinate system
        *
        * @param X the coordinate on the horizontal level
        * @param Y the coordinate on the vertical level
        * @param time the systemtime
        * @return VisionPosition in the worldspace
        */
        VisionPosition convertToCoordinate(unsigned int X, unsigned int Y, std::time_t time);
        virtual void locateObject() = 0;
    };
}

