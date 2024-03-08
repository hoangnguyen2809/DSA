#include <iostream>
#include <vector>
#include <limits>

using namespace std;

pair<vector<vector<double>>, vector<vector<int>>> optimalBST(const vector<double>& p, const vector<double>& q) {
    int n = p.size();
    vector<vector<double>> e(n + 2, vector<double>(n + 1, 0)); // Expected cost table
    vector<vector<double>> w(n + 2, vector<double>(n + 1, 0)); // Weight table
    vector<vector<int>> root(n + 1, vector<int>(n + 1, 0)); // Root table

    // Initialize base cases
    for (int i = 1; i <= n + 1; ++i) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Compute optimal cost and root
    for (int l = 1; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            e[i][j] = numeric_limits<double>::infinity();
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; ++r) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    return make_pair(e, root);
}

int main() {
    vector<double> p = {0.0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
    vector<double> q = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};

    auto result = optimalBST(p, q);
    vector<vector<double>> e = result.first;
    vector<vector<int>> root = result.second;

    cout << "Optimal cost table (e):" << endl;
    for (int i = 1; i <= p.size(); ++i) {
        for (int j = 0; j <= p.size()-1; ++j) {
            cout << e[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nRoot table:" << endl;
    for (int i = 1; i <= p.size()-1; ++i) {
        for (int j = 1; j <= p.size()-1; ++j) {
            cout << root[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
