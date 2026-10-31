/*
 * 1584. Min Cost to Connect All Points  |  Medium  |  Advanced Graphs
 * Link: https://leetcode.com/problems/min-cost-to-connect-all-points/
 *
 * Problem: Points on a plane; connecting two costs their Manhattan distance.
 *          Return the minimum total cost so every point is connected.
 *
 * Examples:
 *   [[0,0],[2,2],[3,10],[5,2],[7,0]]  -> 20
 *   [[3,12],[-2,5],[-4,1]]            -> 18
 *   [[0,0]]                           -> 0
 *   [[0,0],[1,1],[1,0],[-1,1]]        -> 4
 *
 * Approaches:
 *   1. Kruskal (sort all edges + Union-Find)  O(n^2 log n) time, O(n^2) space
 *   2. Prim with a heap                       O(n^2 log n) time, O(n^2) space
 *   3. Prim with an array  ⭐                  O(n^2) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

int manhattan(const vector<int>& a, const vector<int>& b) { return abs(a[0] - b[0]) + abs(a[1] - b[1]); }

// ---------- Approach 1: Kruskal ----------
int findRoot(vector<int>& parent, int x) {
    while (parent[x] != x) x = parent[x] = parent[parent[x]];   // path halving
    return x;
}

int minCostConnectPointsKruskal(const vector<vector<int>>& pts) {
    int n = pts.size();
    vector<array<int, 3>> edges;                  // (cost, i, j)
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) edges.push_back({manhattan(pts[i], pts[j]), i, j});
    sort(edges.begin(), edges.end());
    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0);
    int total = 0, used = 0;
    for (auto [w, i, j] : edges) {
        int a = findRoot(parent, i), b = findRoot(parent, j);
        if (a == b) continue;                     // would form a cycle
        parent[a] = b;
        total += w;
        if (++used == n - 1) break;
    }
    return total;
}

// ---------- Approach 2: Prim with a heap ----------
int minCostConnectPointsHeap(const vector<vector<int>>& pts) {
    int n = pts.size(), total = 0, added = 0;
    vector<bool> in(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;   // (cost to reach, point)
    pq.push({0, 0});
    while (added < n) {
        auto [w, u] = pq.top(); pq.pop();
        if (in[u]) continue;                      // already attached by a cheaper edge
        in[u] = true;
        total += w;
        added++;
        for (int v = 0; v < n; v++)
            if (!in[v]) pq.push({manhattan(pts[u], pts[v]), v});
    }
    return total;
}

// ---------- Approach 3: Prim with an array ⭐ ----------
int minCostConnectPoints(const vector<vector<int>>& pts) {
    int n = pts.size(), total = 0;
    vector<int> dist(n, INT_MAX);                 // cheapest edge from the tree to each point
    vector<bool> in(n, false);
    dist[0] = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++)               // closest point not yet in the tree
            if (!in[v] && (u == -1 || dist[v] < dist[u])) u = v;
        in[u] = true;
        total += dist[u];
        for (int v = 0; v < n; v++)
            if (!in[v]) dist[v] = min(dist[v], manhattan(pts[u], pts[v]));
    }
    return total;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}},
        {{3, 12}, {-2, 5}, {-4, 1}},
        {{0, 0}},
        {{0, 0}, {1, 1}, {1, 0}, {-1, 1}},
    };
    for (auto& p : tests) {
        cout << "kruskal   : " << minCostConnectPointsKruskal(p) << "\n";
        cout << "prim heap : " << minCostConnectPointsHeap(p) << "\n";
        cout << "prim array: " << minCostConnectPoints(p) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `iota(v.begin(), v.end(), 0)` fills 0, 1, 2, ... (Union-Find init).
 * - `x = parent[x] = parent[parent[x]]` is path halving in one line.
 * - `for (auto [w, i, j] : edges)` unpacks std::array<int, 3>.
 * - Linear "argmin over unvisited" beats a heap when the graph is complete (E = n^2).
 */
