#pragma once
#include<list>
#include "MessageBox.hpp"
#include <mutex>

template <class T>
class MessageSender
{
public:
    MessageSender();
    ~MessageSender();
    void addListener(MessageBox<T> listerner);
    void removeListener(MessageBox<T> listerner);
protected:
     void notify(T object);
private:
    std::list<MessageBox<T>> listeners;
    std::mutex listenersMutex;

};

