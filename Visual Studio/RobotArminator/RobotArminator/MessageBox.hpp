#pragma once
#include<queue>
#include <mutex>

namespace RobotArminator
{

    template <class T>
    class MessageBox
    {
    public:
        MessageBox();
        ~MessageBox();
        void addToQueue(T item);
        T MessageBox<T>::popFromQueue();
    private:
        std::queue<T> queue;
        std::mutex queueMutux;
    };
}
