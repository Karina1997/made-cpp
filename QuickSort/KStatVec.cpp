//
// Created by Карина Зайнуллина on 28/10/2019.
//

#include "KStatVec.h"

int KStatVec::getPivot(int size) {
    random_device r;

    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(0, size - 1);
    return uniform_dist(e1);
}

void KStatVec::replace(vector<int>::iterator a, vector<int>::iterator b) {
    iter_swap(a, b);
}

vector<int>::iterator KStatVec::partition(vector<int>::iterator i, vector<int>::iterator begin, int pivotInd) {
    replace(begin + pivotInd, begin);
    int pivot = *begin;
    auto j = i;
    while (begin < j) {
        if (*j <= pivot) {
            j--;
        } else {
            replace(i, j);
            i--;
            j--;
        }
    }
    replace(i, begin);
    return i;
}


KStatVec::KStatVec(vector<int> vect) : vect(std::move(vect)) {}

int KStatVec::findKStat(int k) {
    auto begin = vect.begin();
    auto end = begin + vect.size() - 1;
    vector<int>::iterator resIter;
    while (true) {
        if (begin == end) {
            return *begin;
        }
        int pivotInd = getPivot(end - begin);
        resIter = partition(end, begin, pivotInd);
        if (resIter - vect.begin() == k) {
            return *resIter;
        } else if (resIter - vect.begin() < k) {
            begin = resIter + 1;
        } else {
            end = resIter - 1;
        }
    }
}

int main() {
    int arrSize, kStat;
    cin >> arrSize >> kStat;

    vector<int> g1;

    int obj;
    for (int i = 0; i < arrSize; i++) {
        cin >> obj;
        g1.push_back(obj);
    }
    KStatVec k = KStatVec(g1);
    cout << k.findKStat(kStat);
}