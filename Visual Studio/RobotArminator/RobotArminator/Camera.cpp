#include "stdafx.h"
#include "Camera.hpp"
#include "Logger.hpp"

namespace Vision
{

    Camera::Camera(int cameraNumber, bool mirrored, int width, int height) : height(height), width(width), cameraNumber(cameraNumber), mirrored(mirrored)
    {
        camera.open(cameraNumber);
        camera.set(CV_CAP_PROP_FRAME_WIDTH, width);
        camera.set(CV_CAP_PROP_FRAME_HEIGHT, height);
    }

    Camera::~Camera()
    {
        camera.release();
        delete &camera;
    }

    bool Camera::isMirrored()
    {
        return mirrored;
    }

    bool Camera::getCurrentImage(cv::Mat& output)
    {
        if (!camera.isOpened())
        {
            camera.open(cameraNumber);
            camera.set(CV_CAP_PROP_FRAME_WIDTH, width);
            camera.set(CV_CAP_PROP_FRAME_HEIGHT, height);
        }
        if (camera.isOpened())
        {
            if (!camera.read(output))
            {
                std::string sender = "Camera " + std::to_string(cameraNumber);
                RobotArminator::Logger::logWarning((char *)sender.c_str(), "Camera could not read!");
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            std::string sender = "Camera " + std::to_string(cameraNumber);
            RobotArminator::Logger::logWarning((char *)sender.c_str(), "Camera could not be opened!");
            return false;
        }
    }

    int Camera::getHeight() {
        return height;
    }

    int Camera::getWidth() {
        return width;
    }

    void Camera::setSize(int newWidth, int newHeight)
    {
        height = newHeight;
        width = newWidth;
        camera.set(CV_CAP_PROP_FRAME_WIDTH, newWidth);
        camera.set(CV_CAP_PROP_FRAME_HEIGHT, newHeight);
    }

    int Camera::getCameraNumber()
    {
        return cameraNumber;
    }



    //FILE CAMERA

    FileCamera::FileCamera(char * filename) :Camera(0), filename(filename)
    {
    }

    FileCamera::~FileCamera() {

    }

    bool FileCamera::getCurrentImage(cv::Mat& output)
    {
        output = cv::imread(filename, 1);
        return true;
    }


    //VIDEO CAMERA
    VideoCamera::VideoCamera(char * filename) :Camera(0), filename(filename)
    {
        camera.open(filename);
        camera.set(CV_CAP_PROP_FRAME_WIDTH, width);
        camera.set(CV_CAP_PROP_FRAME_HEIGHT, height);
    }

    VideoCamera::~VideoCamera() {

    }

    bool VideoCamera::getCurrentImage(cv::Mat& output)
    {
        if (camera.isOpened())
        {
            if (!camera.read(output))
            {
                std::string sender = "Video "; sender += filename;
                RobotArminator::Logger::logWarning((char *)sender.c_str(), "Video could not read!");
                return false;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
}
