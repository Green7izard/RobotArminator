#pragma once
#include "IComputerVision.hpp"
#include "Table.hpp"
#include "Camera.hpp"
#include "opencv2/opencv.hpp"

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
        * //TODO
        * The main function of the class
        */
        virtual void run();

        /**
        * Converts a X and Y position from the camera into a VisionPosition based on the coordinate system
        *
        * @param position the location in the screen
        * @param time the systemtime
        * @return VisionPosition in the worldspace
        */
        VisionPosition convertToCoordinate(Position2D &position, std::time_t time);

        /**
        * Function for finding the ball.
        * @param image the incomming image
        * @return the location
        */
        virtual bool locateObject(cv::Mat &image, Position2D &position) = 0;
        
        /**
        * Sets the image size
        */
        void updateImageSize(unsigned int width = Camera::FRAME_WIDTH, unsigned int height = Camera::FRAME_HEIGHT);
    };
}

