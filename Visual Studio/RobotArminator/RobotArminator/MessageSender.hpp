#pragma once
#include<list>
#include "MessageBox.hpp"

template <class T>
class MessageSender
{
public:
    MessageSender();
    ~MessageSender();
   
protected:
     void notify(T object);
private:
    std::list<MessageBox<T>> listeners;
};

