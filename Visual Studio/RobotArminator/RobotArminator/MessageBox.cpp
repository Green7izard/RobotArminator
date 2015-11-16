#include "stdafx.h"
#include "MessageBox.hpp"

template <class T>
MessageBox<T>::MessageBox()
{
}

template <class T>
MessageBox<T>::~MessageBox()
{
}

template<class T>
void MessageBox<T>::addToQueue(T item)
{
    queue.push(item);
}

template<class T>
T MessageBox<T>::popFromQueue()
{
    queueMutux.lock();
    T item = queue.pop();
    queueMutux.unlock();
    return item;
}