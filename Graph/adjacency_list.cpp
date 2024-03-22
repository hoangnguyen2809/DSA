#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

struct Edge {
    int u, v, weight;
};

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
    }

    vector<Edge> primMST(int r) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        vector<int> key(V, INT_MAX);

        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        pq.push(make_pair(r, 0));
        key[r] = 0;

        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();

            visited[u] = true;

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push(make_pair(v, weight));
                }
            }
        }

        vector<Edge> mst;
        for (int i = 1; i < V; i++) {
            mst.push_back({ parent[i], i, key[i] });
        }

        return mst;
    }
};

int main() {
    Graph graph(9);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 7, 8);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 7, 11);
    graph.addEdge(2, 3, 7);
    graph.addEdge(2, 8, 2);
    graph.addEdge(2, 5, 4);
    graph.addEdge(3, 4, 9);
    graph.addEdge(3, 5, 14);
    graph.addEdge(4, 5, 10);
    graph.addEdge(5, 6, 2);
    graph.addEdge(6, 7, 1);
    graph.addEdge(6, 8, 6);
    graph.addEdge(7, 8, 7);


    int startVertex = 0;
    vector<Edge> mst = graph.primMST(startVertex);

    cout << "Minimum Spanning Tree Edges:" << endl;
    for (const auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }

    return 0;
}