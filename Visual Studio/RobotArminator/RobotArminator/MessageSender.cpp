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
    void MessageSender<T>::addListener(IMessageBox<T>* listerner)
    {
        listenersMutex.lock();
        listeners.push_front(listerner);
        listenersMutex.unlock();
    }

    template<class T>
    void MessageSender<T>::removeListener(IMessageBox<T>* listerner)
    {
        listenersMutex.lock();
        listeners.remove(listerner);
        listenersMutex.unlock();
    }

    template <class T>
    void MessageSender<T>::notify(T object)
    {
        listenersMutex.lock();
        for each (IMessageBox<T> * box in listeners)
        {
            box->addToMessageBox(object);
        }
        listenersMutex.unlock();
    }
}


