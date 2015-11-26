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

    void Camera::getCurrentImage(cv::Mat& output)
    {
        if (!camera.isOpened())
        {
            camera.open(cameraNumber);
            camera.set(CV_CAP_PROP_FRAME_WIDTH, width);
            camera.set(CV_CAP_PROP_FRAME_HEIGHT, height);
        }
        if(camera.isOpened())
        {
            if (!camera.read(output))
            {
                char * sender = "Camera # ";
                sender[8] = cameraNumber;
                RobotArminator::Logger::logWarning(sender, "Camera could not read!");
            }
        }
        else
        {
            char * sender = "Camera # ";
            sender[8] = cameraNumber;
            RobotArminator::Logger::logWarning(sender, "Camera could not be opened!");
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
}
