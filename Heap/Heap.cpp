//
// Created by Карина Зайнуллина on 20/10/2019.
//

#include<iostream>

using namespace std;

void swap(int &x, int &y);

class Heap {
private:
    int *arr;
    int capacity;
    int heapSize;
public:
    explicit Heap() {
        heapSize = 0;
        capacity = 10;
        arr = new int[capacity];
    };

    ~Heap() {
        delete[] arr;
        heapSize = 0;
        capacity = 0;
    }

    int extractMin();
    void insertKey(int k);

    int getSize() const{
        return heapSize;
    };

private:
    static int parent(int i) { return (i - 1) / 2; }

    static int left(int i) { return (2 * i + 1); }

    static int right(int i) { return (2 * i + 2); }

    void siftUp();

    void siftDown(int);

    void increaseCapacity();
};


void Heap::insertKey(int k){
    if (heapSize == capacity) {
        increaseCapacity();
    }

    arr[heapSize] = k;
    heapSize++;
    siftUp();
}

void Heap::siftUp() {
    int i = heapSize - 1;
    while (i != 0 && arr[parent(i)] > arr[i]) {
        swap(arr[i], arr[parent(i)]);
        i = parent(i);
    }
}

void Heap::increaseCapacity() {
    capacity *= 2;
    int *newArr = new int[capacity];
    for (int i = 0; i < heapSize; ++i) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
}

int Heap::extractMin() {
    if (heapSize <= 0)
        return 0;

    heapSize--;
    int root = arr[0];
    arr[0] = arr[heapSize];
    siftDown(0);

    return root;
}


void Heap::siftDown(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapSize && arr[l] < arr[smallest])
        smallest = l;
    if (r < heapSize && arr[r] < arr[smallest])
        smallest = r;
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        siftDown(smallest);
    }
}

void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

int heapMain() {
    int heapSize;
    std::cin >> heapSize;
    Heap heap;
    int k;

    for (int i = 0; i < heapSize; ++i) {
        cin >> k;
        heap.insertKey(k);
    }
    int sum = 0;

    while (heap.getSize() > 1) {
        int pairSum = heap.extractMin() + heap.extractMin();
        sum += pairSum;
        heap.insertKey(pairSum);
    }

    cout << sum;
    return 0;
}


