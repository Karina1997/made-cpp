//
// Created by Карина Зайнуллина on 27/10/2019.
//

#ifndef MADE_CPP_ENQUE_H
#define MADE_CPP_ENQUE_H


class Enque {
private:
    int *a;
    int size;
    int capacity;
    int head;
    int tail;
public:
    Enque() {
        capacity = 10;
        size = 0;
        head = 0;
        tail = 0;
        a = new int[capacity];
    }

    ~Enque() {
        capacity = 0;
        size = 0;
        head = 0;
        tail = 0;
        delete a;
    }

    void push_back(int k);

    void push_front(int k);

    int pop_front();

    int pop_back();

    void increaseCapacity();
};



#endif //MADE_CPP_ENQUE_H
