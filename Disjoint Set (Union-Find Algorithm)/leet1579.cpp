class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            ++rank[rootX];
        }
        return true;
    }

    void printState() {
        cout << "Parent: ";
        for (const auto& p : parent) {
            cout << p << " ";
        }
        cout << "\nRank: ";
        for (const auto& r : rank) {
            cout << r << " ";
        }
        cout << endl;
    }
};
class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UnionFind ufAlice(n + 1);
        UnionFind ufBob(n + 1);

        cout << "Initial state of ufAlice:\n";
        ufAlice.printState();
        cout << "Initial state of ufBob:\n";
        ufBob.printState();
        int edgesUsed = 0;
        for (const auto& edge : edges) {
            if (edge[0] == 3) {
                cout << "Processing type 3 edge: " << edge[1] << " - " << edge[2] << endl;
                if (ufAlice.unionSets(edge[1], edge[2])) {
                    if (ufBob.unionSets(edge[1], edge[2])){
                        cout << "use " << endl;
                        ++edgesUsed;
                    }
                    
                }
                cout << "Alice's UnionFind state after type 3 edge:\n";
                ufAlice.printState();
                cout << "Bob's UnionFind state after type 3 edge:\n";
                ufBob.printState();
            }
        }

        for (const auto& edge : edges) {
            if (edge[0] == 1) {
                cout << "Processing type 1 edge: " << edge[1] << " - " << edge[2] << endl;
                if (ufAlice.unionSets(edge[1], edge[2])) {
                    cout << "use " << endl;
                    ++edgesUsed;
                }
                cout << "Alice's UnionFind state after type 1 edge:\n";
                ufAlice.printState();
            }
        }

        for (const auto& edge : edges) {
            if (edge[0] == 2) {
                cout << "Processing type 2 edge: " << edge[1] << " - " << edge[2] << endl;
                if (ufBob.unionSets(edge[1], edge[2])) {
                    cout << "use " << endl;
                    ++edgesUsed;
                }
                cout << "Bob's UnionFind state after type 2 edge:\n";
                ufBob.printState();
            }
        }

        for (int i = 1; i <= n; ++i) {
            if (ufAlice.find(i) != ufAlice.find(1) || ufBob.find(i) != ufBob.find(1)) {
                cout << "Graph is not fully connected for both Alice and Bob.\n";
                return -1;
            }
        }

        return edges.size() - edgesUsed;
    }
};