//
// Created by Карина Зайнуллина on 22/10/2019.
//



#include <algorithm>
#include <iostream>

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

    void push_back(int k) {
        if (size == capacity) {
            increaseCapacity();
        }
        a[tail] = k;
        size++;
        ++tail;
        tail = tail % capacity;
    }

    void push_front(int k) {
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

    int pop_front() {
        if (size == 0) {
            return -1;
        }
        int wasHead = head;
        head = (head + 1) % capacity;
        --size;
        return a[wasHead];
    }

    int pop_back() {
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

    void increaseCapacity() {
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
};


int main() {
    Enque e;
    int n;
    int cmd;
    int num;
    bool correct = true;

    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> cmd >> num;

        switch (cmd) {
            case 1:
                e.push_front(num);
                break;
            case 2:
                correct = num == e.pop_front();
                break;
            case 3:
                e.push_back(num);
                break;
            case 4:
                correct = num == e.pop_back();
                break;
            default:
                break;
        }
    }

    if (!correct) {
        std::cout << "NO";
    } else {
        std::cout << "YES";
    }
    std::cout << std::endl;

    return 0;
}