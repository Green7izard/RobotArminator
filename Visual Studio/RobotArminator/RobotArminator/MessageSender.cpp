#include "stdafx.h"
#include "MessageSender.hpp"

template <class T>
MessageSender<T>::MessageSender()
{
}


template <class T>
MessageSender<T>::~MessageSender()
{
}

template<class T>
void MessageSender<T>::addListener(MessageBox<T> listerner)
{
    listenersMutex.lock();
    listeners.push_front(listerner);
    listenersMutex.unlock();
}

template<class T>
void MessageSender<T>::removeListener(MessageBox<T> listerner)
{
    listenersMutex.lock();
    listeners.remove(listerner);
    listenersMutex.unlock();
}

template <class T>
void MessageSender<T>::notify(T object)
{
    listenersMutex.lock();
    for each (MessageBox box in listeners)
    {
        listerens.addToQueue(object);
    }
    listenersMutex.unlock();
}



