#include "stdafx.h"
#include "MessageBox.hpp"
namespace RobotArminator
{
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
        queueMutux.lock();
        queue.push(item);
        queueMutux.unlock();
    }

    template<class T>
    T MessageBox<T>::popFromQueue()
    {
        queueMutux.lock();
        T item = queue.pop();
        queueMutux.unlock();
        return item;
    }
}