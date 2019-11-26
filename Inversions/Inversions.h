//
// Created by Карина Зайнуллина on 08/11/2019.
//

#ifndef MADE_CPP_INVERSIONS_H
#define MADE_CPP_INVERSIONS_H

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Inversions {
private:
    vector<int> a;
    vector<int> c;
    int64_t count = 0;

    void merge(int64_t low, int64_t high, int64_t mid);

public:
    int64_t getCount() { return count; };

    Inversions(vector<int> a, vector<int> c);

    void mergesort(int64_t low, int64_t high) {
        int64_t mid;
        if (low < high) {
            mid = (low + high) / 2;
            mergesort(low, mid);
            mergesort(mid + 1, high);
            merge(low, high, mid);
        }
    }
};
#endif //MADE_CPP_INVERSIONS_H
