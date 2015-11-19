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
        void addListener(IMessageBox<T> * listerner);
        void removeListener(IMessageBox<T> * listerner);
    protected:
        void notify(T object);
    private:
        std::list<IMessageBox<T> *> listeners;
        std::mutex listenersMutex;

    };
}
