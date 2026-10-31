/*
 * 0210. Course Schedule II  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/course-schedule-ii/
 *
 * Problem: n courses, pairs [a, b] meaning b before a. Return any order
 *          that takes every course, or [] if impossible.
 *
 * Examples:
 *   2, [[1,0]]                    -> [0,1]
 *   4, [[1,0],[2,0],[3,1],[3,2]]  -> [0,2,1,3] or [0,1,2,3]
 *   1, []                         -> [0]
 *   2, [[1,0],[0,1]]              -> []
 *
 * Approaches:
 *   1. DFS post-order (reversed)   O(V + E) time, O(V + E) space
 *   2. Kahn's algorithm  ⭐         O(V + E) time, O(V + E) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DFS Post-Order ----------
bool post(int u, const vector<vector<int>>& adj, vector<int>& color, vector<int>& out) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) return false;   // back edge: cycle
        if (color[v] == 0 && !post(v, adj, color, out)) return false;
    }
    color[u] = 2;
    out.push_back(u);                      // after everything that depends on u
    return true;
}

vector<int> findOrderDFS(int n, const vector<vector<int>>& pre) {
    vector<vector<int>> adj(n);
    for (auto& p : pre) adj[p[1]].push_back(p[0]);
    vector<int> color(n, 0), out;
    for (int u = 0; u < n; u++)
        if (color[u] == 0 && !post(u, adj, color, out)) return {};
    reverse(out.begin(), out.end());
    return out;
}

// ---------- Approach 2: Kahn's Algorithm ⭐ ----------
vector<int> findOrder(int n, const vector<vector<int>>& pre) {
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0), order;
    for (auto& p : pre) { adj[p[1]].push_back(p[0]); indeg[p[0]]++; }
    queue<int> q;
    for (int u = 0; u < n; u++) if (indeg[u] == 0) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    if ((int)order.size() < n) return {};  // cycle
    return order;
}

// ---------- Driver ----------
bool valid(int n, const vector<vector<int>>& pre, const vector<int>& order) {
    if ((int)order.size() != n) return false;
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[order[i]] = i;
    for (auto& p : pre) if (pos[p[1]] > pos[p[0]]) return false;
    return true;
}

void print(const string& label, int n, const vector<vector<int>>& pre, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "] valid: " << (valid(n, pre, v) ? "true" : "false") << "\n";
}

int main() {
    vector<pair<int, vector<vector<int>>>> tests = {
        {2, {{1, 0}}}, {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}}, {1, {}}, {2, {{1, 0}, {0, 1}}}
    };
    for (auto& [n, pre] : tests) {
        print("dfs ", n, pre, findOrderDFS(n, pre));
        print("kahn", n, pre, findOrder(n, pre));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Returning {} from a vector<int> function gives an empty vector.
 * - pos[order[i]] = i inverts a permutation for O(1) "who comes first" checks.
 */
