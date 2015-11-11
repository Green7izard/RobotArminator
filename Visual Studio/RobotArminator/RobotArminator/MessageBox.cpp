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
