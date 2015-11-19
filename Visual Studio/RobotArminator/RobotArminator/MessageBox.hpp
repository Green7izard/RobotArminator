#pragma once

namespace RobotArminator
{

    template <class T>
    class MessageBox
    {
    public:
        MessageBox();
        ~MessageBox();
        void addToMessageBox(T item);
        T MessageBox<T>::popFromMessageBox();
    };
}
