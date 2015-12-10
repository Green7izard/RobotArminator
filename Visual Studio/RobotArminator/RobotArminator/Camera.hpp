#pragma once
#include "stdafx.h"

#include "opencv2/opencv.hpp"

namespace Vision
{

    class Camera
    {

    private:
        //The camera number that is used
        int cameraNumber;

        //If the images from the camera are mirrored
        bool mirrored;

    protected:
        //The Camera
        cv::VideoCapture camera;

        //The height of the image
        unsigned int width = FRAME_WIDTH;
        unsigned int height = FRAME_HEIGHT;

    public:
        //Default height
        const static int FRAME_WIDTH = 640;
        //Default width
        const static int FRAME_HEIGHT = 480;

        /**
        * Creates the camera
        *
        * @param cameraNumber the ID of the Camera (example: 0 for the laptop camera)
        * @param mirrored set it to true if the camera is mirrored like the laptop camera
        * @param width the width of the image
        * @param height the height of the image
        */
        Camera(int cameraNumber, bool mirrored = false, unsigned int width = FRAME_WIDTH, unsigned int height = FRAME_HEIGHT);

        //Deconstructor, closes the camera and terminates it
        virtual ~Camera();

        //Whether it is mirrored or not
        virtual bool isMirrored();

        /**
        * Gets the current image
        * @param output where to store it
        */
        virtual bool getCurrentImage(cv::Mat& output);

        /**
        * Sets the image size
        */
        void setSize(unsigned int width = FRAME_WIDTH, unsigned  int height = FRAME_HEIGHT);

        //Gets the hight of the image
        int getHeight();

        //Gets the width of the image
        int getWidth();

        //Get the number of the camera
        int getCameraNumber();

    };


    class FileCamera : public Camera
    {
    private:
        char * filename;

    public:

        FileCamera(char * filename);
        //Deconstructor, closes the camera and terminates it
        virtual ~FileCamera();

        /**
        * Regets the image from a file
        * @param output where to store it
        */
        virtual bool getCurrentImage(cv::Mat& output) override;
    };


    class VideoCamera : public Camera
    {
    private:
        char * filename;

    public:

        VideoCamera(char * filename);
        //Deconstructor, closes the camera and terminates it
        virtual ~VideoCamera();

        /**
        * Regets the image from a file
        * @param output where to store it
        */
        virtual bool getCurrentImage(cv::Mat& output) override;
    };
}
