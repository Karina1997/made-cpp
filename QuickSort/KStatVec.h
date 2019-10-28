//
// Created by Карина Зайнуллина on 28/10/2019.
//

#ifndef MADE_CPP_KSTATVEC_H
#define MADE_CPP_KSTATVEC_H

#include <iostream>
#include <utility>
#include <vector>
#include <random>

using namespace std;

class KStatVec {
private:
    vector<int> vect;
public:
    explicit KStatVec(vector<int> vect);

    int findKStat(int k);

private:
    static int getPivot(int size);

    static void replace(vector<int>::iterator a, vector<int>::iterator b);

    static vector<int>::iterator partition(vector<int>::iterator i, vector<int>::iterator begin, int pivotInd);
};
#endif //MADE_CPP_KSTATVEC_H
