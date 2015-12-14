#pragma once
#include "stdafx.h"
#include <list>
#include "IMessageBox.hpp"
#include <mutex>
#include "VisionPosition.hpp"

namespace RobotArminator
{
    class MessageSender
    {
    public:
        MessageSender();
        ~MessageSender();
        void addListener(IMessageBox * listerner);
        void removeListener(IMessageBox * listerner);
    protected:
        void notify(VisionPosition object);
    private:
        std::list<IMessageBox *> listeners;
        std::mutex listenersMutex;

    };
}
