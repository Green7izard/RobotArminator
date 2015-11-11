#pragma once
#include<queue>

template <class T>
class MessageBox
{
public:
    MessageBox();
    ~MessageBox();
    void addToQueue(T item);
private:    
    std::queue<T> queue;
};

