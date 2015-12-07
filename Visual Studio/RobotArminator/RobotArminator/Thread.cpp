#include "stdafx.h"
#include "Thread.hpp"
namespace RobotArminator
{

    Thread::Thread()
    {
        running = false;
    }


    void Thread::start()
    {
        running = true;
        thread = std::thread(&Thread::run, this);
    }

    void Thread::stop()
    {
        thread.join();
        running = false;
    }

    Thread::~Thread()
    {

    }

    bool Thread::isRunning()
    {
        return running;
    }
}