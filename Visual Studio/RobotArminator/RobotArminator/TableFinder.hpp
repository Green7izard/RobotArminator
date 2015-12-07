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

        /**
        * Updates the last known position and pushes the change
        * @param position the new VisionPosition
        */
        void setPosition(VisionPosition position);

        //Whether its running or not
        bool running;

        //Check if the table is valid
        static bool validTable(Table * table);

        //check if point is valid
        static bool validPoint(Position2D * point);

        struct BigTable {
            Table * table;
            Orientation orientation;
        };

    protected:

        //The camera wrapper that is used
        Camera* camera;

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
        * Stops the thread action
        */
        virtual void stop();

        /**
        * Converts a X and Y position from the camera into a VisionPosition based on the coordinate system
        *
        * @param position the location in the screen
        * @param time the systemtime
        * @param imageHeight the height fo the current image in pixels
        * @return VisionPosition in the worldspace
        */
        VisionPosition convertToCoordinate(Position2D &position, timePoint time, int imageHeight);

        /**
        * Function for finding the ball.
        * @param image the incomming image
        * @return the location
        */
        virtual bool locateObject(cv::Mat &image, Position2D &position) = 0;

        /**
        * Opens a menu to calibrate the system
        *
        */
        virtual void calibrate()=0;
        
        /**
        * Sets the image size
        */
        void updateImageSize(unsigned int width = Camera::FRAME_WIDTH, unsigned int height = Camera::FRAME_HEIGHT);

        /**
        * catches mouse clicks
        */
        static void mouseClick(int event, int x, int y, int flags, void *userdata);
    };
}

