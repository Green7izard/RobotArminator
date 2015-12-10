#include "stdafx.h"
#include "MessageSender.hpp"

namespace RobotArminator
{
    MessageSender::MessageSender()
    {
    }

    MessageSender::~MessageSender()
    {
    }

    void MessageSender::addListener(IMessageBox* listerner)
    {
        listenersMutex.lock();
        listeners.push_front(listerner);
        listenersMutex.unlock();
    }

    void MessageSender::removeListener(IMessageBox* listerner)
    {
        listenersMutex.lock();
        listeners.remove(listerner);
        listenersMutex.unlock();
    }

    void MessageSender::notify(VisionPosition object)
    {
        listenersMutex.lock();
        for each (IMessageBox * box in listeners)
        {
            box->addToMessageBox(object);
        }
        listenersMutex.unlock();
    }
}


