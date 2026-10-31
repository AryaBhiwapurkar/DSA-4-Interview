/*
 * 0261. Graph Valid Tree  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/graph-valid-tree/
 *
 * Problem: Do n nodes and these undirected edges form a tree
 *          (connected and acyclic)?
 *
 * Examples:
 *   5, [[0,1],[0,2],[0,3],[1,4]]         -> true
 *   5, [[0,1],[1,2],[2,3],[1,3],[1,4]]   -> false
 *   1, []                                -> true
 *   4, [[0,1],[2,3]]                     -> false (two components)
 *   4, [[0,1],[1,2],[2,0]]               -> false (cycle, node 3 isolated)
 *
 * Approaches:
 *   1. DFS connectivity + edge count     O(n + E) time, O(n + E) space
 *   2. Edge count + Union-Find  ⭐        O(n + E * alpha) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DFS Connectivity + Edge Count ----------
bool validTreeDFS(int n, const vector<vector<int>>& edges) {
    if ((int)edges.size() != n - 1) return false;
    vector<vector<int>> adj(n);
    for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
    vector<bool> seen(n, false);
    vector<int> st = {0};
    seen[0] = true;
    int reached = 1;
    while (!st.empty()) {
        int u = st.back(); st.pop_back();
        for (int v : adj[u]) if (!seen[v]) { seen[v] = true; reached++; st.push_back(v); }
    }
    return reached == n;                   // n-1 edges + connected => acyclic
}

// ---------- Approach 2: Edge Count + Union-Find ⭐ ----------
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;          // already connected: this edge closes a cycle
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};

bool validTree(int n, const vector<vector<int>>& edges) {
    if ((int)edges.size() != n - 1) return false;
    DSU dsu(n);
    for (auto& e : edges)
        if (!dsu.unite(e[0], e[1])) return false;
    return true;
}

// ---------- Driver ----------
int main() {
    vector<pair<int, vector<vector<int>>>> tests = {
        {5, {{0, 1}, {0, 2}, {0, 3}, {1, 4}}}, {5, {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}}},
        {1, {}}, {4, {{0, 1}, {2, 3}}}, {4, {{0, 1}, {1, 2}, {2, 0}}}
    };
    cout << boolalpha;
    for (auto& [n, edges] : tests) {
        cout << "dfs: " << validTreeDFS(n, edges) << "\n";
        cout << "uf : " << validTree(n, edges) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - A vector<int> used as a stack (push_back / back / pop_back) is an iterative DFS.
 * - Union by rank + path compression gives near-constant find().
 */
