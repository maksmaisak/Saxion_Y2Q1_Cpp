//
// Created by Maksym Maisak on 24/10/18.
//

#ifndef SAXION_Y2Q1_CPP_RECEIVER_H
#define SAXION_Y2Q1_CPP_RECEIVER_H

#include <set>

template<typename TMessage>
class Receiver {

public:

    Receiver()  { m_receivers.insert(this); }
    ~Receiver() { m_receivers.erase (this); }

    static void accept(const TMessage& info) {
        for (Receiver<TMessage>* receiver : m_receivers) {
            receiver->receive(info);
        }
    }

    virtual void receive(const TMessage& info) = 0;

private:
    static std::set<Receiver*> m_receivers;
};

template<typename T>
std::set<Receiver<T>*> Receiver<T>::m_receivers;


#endif //SAXION_Y2Q1_CPP_RECEIVER_H
