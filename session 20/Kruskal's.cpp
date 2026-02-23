#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);  
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return;
        if (size[px] < size[py]) {
            parent[px] = py;
            size[py] += size[px];
        } else {
            parent[py] = px;
            size[px] += size[py];
        }
    }
};

int kruskalsMST(int V, vector<vector<int>> &edges) {
    sort(edges.begin(), edges.end(), [](vector<int> &a, vector<int> &b) {
        return a[2] < b[2];
    });

    DSU dsu(V);
    int mstWeight = 0;

    for (auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];

        if (dsu.find(u) != dsu.find(v)) {
            mstWeight += wt;
            dsu.unite(u, v);
        }
    }

    return mstWeight;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> edges(E, vector<int>(3));

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    int result = kruskalsMST(V, edges);
    cout << "Weight of MST: " << result << endl;

    return 0;
}