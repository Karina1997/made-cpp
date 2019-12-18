//
// Created by Карина Зайнуллина on 12/12/2019.
//

#include<iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class DSU {
public:
    explicit DSU(size_t sizeNodes, size_t sizeEdges);

    int find(int element);

    void merge(int left, int right);

    int findMST();

    vector<vector<int>> edges;

private:
    std::vector<int> parent;
    std::vector<int> rank;

};

DSU::DSU(size_t sizeNodes, size_t sizeEdges) :
        parent(sizeNodes, -1),
        rank(sizeNodes, 1),
        edges(sizeEdges, vector<int>(3)) {}

int DSU::find(int element) {
    if (parent[element] == -1) {
        return element;
    }
    return parent[element] = find(parent[element]);
}

void DSU::merge(int left, int right) {
    const int deputat_left = find(left);
    const int deputat_right = find(right);
    assert(deputat_left != deputat_right);
    if (rank[deputat_left] == rank[deputat_right]) {
        parent[deputat_right] = deputat_left;
        ++rank[deputat_left];
    } else if (rank[deputat_left] > rank[deputat_right]) {
        parent[deputat_right] = deputat_left;
    } else {
        parent[deputat_left] = deputat_right;
    }
}

int DSU::findMST() {
    sort(edges.begin(), edges.end());
    int ans = 0;
    for (auto &edge: edges) {
        int weight = edge[0];
        int start = edge[1];
        int end = edge[2];
        if (find(start) != find(end)) {
            ans += weight;
            merge(start, end);
        }
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;

    auto dsu = DSU(n, m);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to >> dsu.edges[i][0];
        dsu.edges[i][1] = from - 1;
        dsu.edges[i][2] = to - 1;
    }

    cout << dsu.findMST() << endl;
}
