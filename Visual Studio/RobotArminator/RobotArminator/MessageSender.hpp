#pragma once
template <class T>
class MessageSender
{
public:
    MessageSender();
    ~MessageSender();
    template <class T>
protected:
    void notify(T Object);
};

