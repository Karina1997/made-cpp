//
// Created by Карина Зайнуллина on 08/11/2019.
//


#include <cstdint>
#include "Inversions.h"

void Inversions::merge(int64_t low, int64_t high, int64_t mid) {
    int64_t i, j, k;
    i = low;
    k = low;
    j = mid + 1;

    while (i <= mid && j <= high) {
        if (a[i] <= a[j]) {
            c[k] = a[i];
            k++;
            i++;
        } else {
            c[k] = a[j];
            k++;
            j++;
            count += mid - i + 1;
        }
    }

    while (i <= mid) {
        c[k] = a[i];
        k++;
        i++;
    }

    while (j <= high) {
        c[k] = a[j];
        k++;
        j++;
    }

    for (i = low; i < k; i++) {
        a[i] = c[i];
    }
}


Inversions::Inversions(vector<int> a, vector<int> c) : a(std::move(a)), c(std::move(c)) {}


int main() {
    string str;
    vector<int> input;
    while (!getline(cin, str).eof()) {
        input.push_back(stoi(str));
    }

    Inversions inversions = Inversions(input, vector<int>(input.size()));
    inversions.mergesort(0, input.size() - 1);
    cout << inversions.getCount() << "\n";
}
