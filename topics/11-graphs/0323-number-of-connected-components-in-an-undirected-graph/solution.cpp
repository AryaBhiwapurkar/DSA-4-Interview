/*
 * 0323. Number of Connected Components in an Undirected Graph  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
 *
 * Problem: n nodes, undirected edges. Count the connected components.
 *
 * Examples:
 *   5, [[0,1],[1,2],[3,4]]          -> 2
 *   5, [[0,1],[1,2],[2,3],[3,4]]    -> 1
 *   3, []                           -> 3
 *   4, [[0,1],[1,2],[2,0]]          -> 2 (cycle + isolated node)
 *
 * Approaches:
 *   1. DFS from each unvisited node    O(n + E) time, O(n + E) space
 *   2. Union-Find with count  ⭐        O(n + E * alpha) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DFS ----------
int countComponentsDFS(int n, const vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
    vector<bool> seen(n, false);
    int count = 0;
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;
        count++;                           // new component
        vector<int> st = {s};
        seen[s] = true;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (int v : adj[u]) if (!seen[v]) { seen[v] = true; st.push_back(v); }
        }
    }
    return count;
}

// ---------- Approach 2: Union-Find with Count ⭐ ----------
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

int countComponents(int n, const vector<vector<int>>& edges) {
    DSU dsu(n);
    int count = n;                         // every node starts alone
    for (auto& e : edges)
        if (dsu.unite(e[0], e[1])) count--;   // only real merges reduce the count
    return count;
}

// ---------- Driver ----------
int main() {
    vector<pair<int, vector<vector<int>>>> tests = {
        {5, {{0, 1}, {1, 2}, {3, 4}}}, {5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}}, {3, {}}, {4, {{0, 1}, {1, 2}, {2, 0}}}
    };
    for (auto& [n, edges] : tests) {
        cout << "dfs: " << countComponentsDFS(n, edges) << "\n";
        cout << "uf : " << countComponents(n, edges) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Member named rank_ avoids clashing with std::rank (bits/stdc++ + using namespace std).
 * - unite() returning bool lets the caller count successful merges.
 */
