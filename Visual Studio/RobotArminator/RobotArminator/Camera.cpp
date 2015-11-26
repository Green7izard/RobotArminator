#include "Camera.hpp"
#include "Logger.hpp"

namespace Vision
{

	Camera::Camera(int cameraNumber, bool mirrored = false) : cameraNumber(cameraNumber), mirrored(mirrored), camera(cameraNumber)
    {
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

    void Camera::getCurrentImage(cv::Mat output)
    {
        if (!camera.isOpened())
        {
            camera.open(cameraNumber);
        }
        if(camera.isOpened())
        {
            camera.read(output);
        }
        else
        {
            char * sender = "Camera # ";
            sender[8] = cameraNumber;
            RobotArminator::Logger::logWarning(sender, "Camera could not be opened!");
        }
    }
}
