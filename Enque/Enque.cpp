//
// Created by Карина Зайнуллина on 27/10/2019.
//

#include <algorithm>
#include "Enque.h"

void Enque::push_back(int k){
    {
        if (size == capacity) {
            increaseCapacity();
        }
        a[tail] = k;
        size++;
        ++tail;
        tail = tail % capacity;
    }
}

void Enque::push_front(int k) {
    if (size == capacity) {
        increaseCapacity();
    }

    if (head == 0) {
        head = capacity;
    }
    --head;
    a[head] = k;
    size++;
}

int Enque::pop_front() {
    if (size == 0) {
        return -1;
    }
    int wasHead = head;
    head = (head + 1) % capacity;
    --size;
    return a[wasHead];
}

int Enque::pop_back() {
    if (size == 0) {
        return -1;
    }
    if (tail == 0) {
        tail = capacity;
    }
    --tail;
    --size;
    return a[tail];
}

void Enque::increaseCapacity() {
    int *newArr = new int[capacity * 2];
    if (head < tail) {
        std::copy(a, a + size, newArr);
        delete[] a;
        a = newArr;
    } else {
        std::copy(a, a + tail, newArr);
        std::copy(a + head, a + capacity, newArr + capacity + head);
        head = capacity + head;
        delete[] a;
        a = newArr;
    }
    capacity *= 2;
}