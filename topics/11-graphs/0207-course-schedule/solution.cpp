/*
 * 0207. Course Schedule  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/course-schedule/
 *
 * Problem: n courses, pairs [a, b] meaning b before a. Can all be taken?
 *          (Is the prerequisite graph acyclic?)
 *
 * Examples:
 *   2, [[1,0]]                       -> true
 *   2, [[1,0],[0,1]]                 -> false
 *   3, []                            -> true
 *   4, [[1,0],[2,1],[3,2],[1,3]]     -> false (cycle 1-2-3)
 *   4, [[1,0],[2,0],[3,1],[3,2]]     -> true  (diamond)
 *
 * Approaches:
 *   1. DFS three-color            O(V + E) time, O(V + E) space
 *   2. Kahn's algorithm  ⭐        O(V + E) time, O(V + E) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DFS Three-Color ----------
bool hasCycle(int u, const vector<vector<int>>& adj, vector<int>& color) {
    color[u] = 1;                          // on the current path
    for (int v : adj[u]) {
        if (color[v] == 1) return true;    // back edge
        if (color[v] == 0 && hasCycle(v, adj, color)) return true;
    }
    color[u] = 2;                          // fully explored
    return false;
}

bool canFinishDFS(int n, const vector<vector<int>>& pre) {
    vector<vector<int>> adj(n);
    for (auto& p : pre) adj[p[1]].push_back(p[0]);
    vector<int> color(n, 0);
    for (int u = 0; u < n; u++)
        if (color[u] == 0 && hasCycle(u, adj, color)) return false;
    return true;
}

// ---------- Approach 2: Kahn's Algorithm ⭐ ----------
bool canFinish(int n, const vector<vector<int>>& pre) {
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0);
    for (auto& p : pre) { adj[p[1]].push_back(p[0]); indeg[p[0]]++; }   // b -> a
    queue<int> q;
    for (int u = 0; u < n; u++) if (indeg[u] == 0) q.push(u);
    int taken = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        taken++;
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    return taken == n;                     // leftovers sit on a cycle
}

// ---------- Driver ----------
int main() {
    vector<pair<int, vector<vector<int>>>> tests = {
        {2, {{1, 0}}}, {2, {{1, 0}, {0, 1}}}, {3, {}},
        {4, {{1, 0}, {2, 1}, {3, 2}, {1, 3}}}, {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}}
    };
    cout << boolalpha;
    for (auto& [n, pre] : tests) {
        cout << "dfs : " << canFinishDFS(n, pre) << "\n";
        cout << "kahn: " << canFinish(n, pre) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `if (--indeg[v] == 0)` decrements, then tests the new value.
 * - vector<vector<int>> adj(n) gives n empty adjacency lists.
 */
