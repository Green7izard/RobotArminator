#pragma once
#include "stdafx.h"
#include <thread>
namespace RobotArminator
{
    class Thread
    {
    public:
        Thread();

        void start();
        void stop();
        virtual void run() = 0;
        virtual ~Thread();
        bool isRunning();

    private:
        std::thread thread;
    protected:
        bool running;
    };
}

