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

template <class T>
void MessageSender<T>::notify(T object)
{
    for each (MessageBox box in listeners)
    {
        listerens.addToQueue(object);
    }
}
