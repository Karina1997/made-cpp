//
// Created by Карина Зайнуллина on 09/12/2019.
//

#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Graph {
    int V;


    list<int> *adj;
public:
    explicit Graph(int V);


    void addEdge(int v, int w);


    int BFS(int from, int to);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

int Graph::BFS(int from, int to) {
    vector<int> minLen(V, -1);
    vector<int> wayNum(V, 0);

    queue<int> queue;

    queue.push(from);
    minLen[from] = 0;
    wayNum[from] = 1;

    list<int>::iterator i;
    while (!queue.empty()) {
        from = queue.front();
        queue.pop();

        for (i = adj[from].begin(); i != adj[from].end(); ++i) {
            if (minLen[*i] == -1) {
                minLen[*i] = minLen[from] + 1;
                wayNum[*i] = wayNum[from];
                queue.push(*i);
            } else if (minLen[from] + 1 == minLen[*i]) {
                wayNum[*i] = wayNum[*i] + wayNum[from];
            }
        }
    }
    return wayNum[to];
}

int main() {
    size_t n, m;
    std::cin >> n >> m;

    auto g = Graph(n);
    for (size_t i = 0; i < m; ++i) {
        int32_t a, b;
        std::cin >> a >> b;
        g.addEdge(a, b);
        g.addEdge(b, a);

    }

    int32_t from, to;
    std::cin >> from >> to;

    std::cout << g.BFS(from, to) << std::endl;

    return 0;
}