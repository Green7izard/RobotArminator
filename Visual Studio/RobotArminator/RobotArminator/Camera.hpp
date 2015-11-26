#pragma once

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

        //The Camera
        cv::VideoCapture camera;

    public:
        Camera(int cameraNumber, bool mirrored);
        virtual ~Camera();

    };
}
