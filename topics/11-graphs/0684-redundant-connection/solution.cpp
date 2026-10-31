/*
 * 0684. Redundant Connection  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/redundant-connection/
 *
 * Problem: A tree on 1..n plus one extra edge. Return an edge whose removal
 *          leaves a tree (the last such edge in input order).
 *
 * Examples:
 *   [[1,2],[1,3],[2,3]]                  -> [2,3]
 *   [[1,2],[2,3],[3,4],[1,4],[1,5]]      -> [1,4]
 *   [[1,2],[2,3],[1,3],[3,4]]            -> [1,3]
 *
 * Approaches:
 *   1. DFS before each edge     O(n^2) time, O(n) space
 *   2. Union-Find  ⭐            O(n * alpha) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DFS Before Each Edge ----------
bool reachable(int u, int target, const vector<vector<int>>& adj, vector<bool>& seen) {
    if (u == target) return true;
    seen[u] = true;
    for (int v : adj[u]) if (!seen[v] && reachable(v, target, adj, seen)) return true;
    return false;
}

vector<int> findRedundantConnectionDFS(const vector<vector<int>>& edges) {
    int n = edges.size();
    vector<vector<int>> adj(n + 1);
    for (auto& e : edges) {
        vector<bool> seen(n + 1, false);
        if (reachable(e[0], e[1], adj, seen)) return e;   // already connected: this edge closes the cycle
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    return {};
}

// ---------- Approach 2: Union-Find ⭐ ----------
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};

vector<int> findRedundantConnection(const vector<vector<int>>& edges) {
    DSU dsu(edges.size() + 1);             // labels are 1..n
    for (auto& e : edges)
        if (!dsu.unite(e[0], e[1])) return e;
    return {};
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [" << v[0] << "," << v[1] << "]\n";
}

int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 2}, {1, 3}, {2, 3}}, {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}, {{1, 2}, {2, 3}, {1, 3}, {3, 4}}
    };
    for (auto& edges : tests) {
        print("dfs", findRedundantConnectionDFS(edges));
        print("uf ", findRedundantConnection(edges));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Returning `e` (a const vector<int>&) from a vector<int> function copies it.
 * - n edges on n nodes, so edges.size() + 1 sizes a 1-indexed DSU.
 */
