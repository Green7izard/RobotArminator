#include "stdafx.h"
#include "MessageSender.hpp"

namespace RobotArminator
{

    template <class T>
    MessageSender<T>::MessageSender()
    {
    }


    template <class T>
    MessageSender<T>::~MessageSender()
    {
    }

    template<class T>
    void MessageSender<T>::addListener(IMessageBox* listerner)
    {
        listenersMutex.lock();
        listeners.push_front(listerner);
        listenersMutex.unlock();
    }

    template<class T>
    void MessageSender<T>::removeListener(IMessageBox* listerner)
    {
        listenersMutex.lock();
        listeners.remove(listerner);
        listenersMutex.unlock();
    }

    template <class T>
    void MessageSender<T>::notify(T object)
    {
        listenersMutex.lock();
        for each (IMessageBox * box in listeners)
        {
            box->addToMessageBox(object);
        }
        listenersMutex.unlock();
    }
}


