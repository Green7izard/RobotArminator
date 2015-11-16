#pragma once
template <class T>
class MessageSender
{
public:
    MessageSender();
    ~MessageSender();
   
protected:
     void notify(T Object);
private:
    List<MessageBox> listeners;
};

