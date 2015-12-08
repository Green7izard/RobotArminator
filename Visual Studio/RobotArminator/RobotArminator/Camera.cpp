#include "Camera.hpp"
#include "Logger.hpp"

namespace Vision
{

    Camera::Camera(int cameraNumber, bool mirrored, unsigned int width, unsigned int height) : height(height), width(width), cameraNumber(cameraNumber), mirrored(mirrored)
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
                std::string sender ="Camera " + std::to_string( cameraNumber);
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
            return true;
        }
    }

    int Camera::getHeight() {
        return height;
    }

    int Camera::getWidth() {
        return width;
    }

    void Camera::setSize(unsigned int newWidth, unsigned int newHeight)
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
}
