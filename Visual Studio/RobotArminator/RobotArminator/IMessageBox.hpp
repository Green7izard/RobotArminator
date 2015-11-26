#pragma once

namespace RobotArminator
{

    template <class T>
    class IMessageBox
    {
    public:
        IMessageBox();
        virtual ~IMessageBox()=0;
        virtual void addToMessageBox(T item)=0;
    };
    template<class T>
    inline IMessageBox<T>::IMessageBox()
    {
    }
}
