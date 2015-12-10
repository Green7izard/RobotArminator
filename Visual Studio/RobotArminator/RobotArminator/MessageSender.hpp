#pragma once
#include<list>
#include "IMessageBox.hpp"
#include <mutex>

namespace RobotArminator
{

    template <class T>
    class MessageSender
    {
    public:
        MessageSender();
        ~MessageSender();
        void addListener(IMessageBox * listerner);
        void removeListener(IMessageBox * listerner);
    protected:
        void notify(T object);
    private:
        std::list<IMessageBox *> listeners;
        std::mutex listenersMutex;

    };
}
