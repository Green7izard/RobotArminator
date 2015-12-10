#pragma once
#include "IComputerVision.hpp"
#include "Thread.hpp"
#include "Table.hpp"
#include "Camera.hpp"
#include "opencv2/opencv.hpp"

namespace Vision
{
    class TableFinder :
        public IComputerVision, public RobotArminator::Thread
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

        //Check if the table is valid
        static bool validTable(Table * table);

        //check if point is valid
        static bool validPoint(Position2D * point);

        struct BigTable {
            Table * table;
            Orientation orientation;
        };

        //The width of the table in mm
        int tableWidth = DEFAULT_WIDTH;
        //The height of the table in mm
        int tableLength = DEFAULT_LENGTH;

    protected:

        //The camera wrapper that is used
        Camera* camera;

    public:

        //default width
        const static int DEFAULT_WIDTH = 1525;
        //default height
        const static int DEFAULT_LENGTH = 2740;

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
        * The main function of the class
        */
        virtual void run() override;

        /**
        * Converts a X and Y position from the camera into a VisionPosition based on the coordinate system
        *
        * @param position the location in the screen
        * @param time the systemtime
        * @param imageWidth the wdith for the current image in pixels
        * @param imageHeight the height fo the current image in pixels
        * @return VisionPosition in the worldspace
        */
        VisionPosition convertToCoordinate(Position2D &position, Time time);

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
        virtual void calibrate();

        /**
        * Sets the image size
        */
        void updateImageSize(int width = Camera::FRAME_WIDTH, int height = Camera::FRAME_HEIGHT);

        /**
        * Sets the table size in mm
        */
        void updateTableSize(int width = DEFAULT_WIDTH, int length = DEFAULT_LENGTH);

        /**
        * catches mouse clicks
        */
        static void mouseClick(int event, int x, int y, int flags, void *userdata);
    };
}

