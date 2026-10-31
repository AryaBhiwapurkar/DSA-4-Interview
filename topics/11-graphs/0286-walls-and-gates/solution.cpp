/*
 * 0286. Walls and Gates  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/walls-and-gates/
 *
 * Problem: Grid of -1 (wall), 0 (gate), INF (room). Fill each room in place
 *          with its distance to the nearest gate (INF if unreachable).
 *
 * Examples (I = INF = 2147483647):
 *   [[I,-1,0,I],[I,I,I,-1],[I,-1,I,-1],[0,-1,I,I]]  -> [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
 *   [[-1]]                                         -> [[-1]]
 *   [[I,I],[I,I]]                                  -> unchanged (no gate)
 *   [[0,-1,I]]                                     -> [[0,-1,I]] (walled off)
 *
 * Approaches:
 *   1. BFS from each gate      O(k*m*n) time, O(m*n) space
 *   2. Multi-source BFS  ⭐     O(m*n) time, O(m*n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;
const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: BFS from Each Gate ----------
void wallsAndGatesEach(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (g[i][j] != 0) continue;
            vector<vector<int>> dist(m, vector<int>(n, -1));
            queue<pair<int, int>> q;
            q.push({i, j});
            dist[i][j] = 0;
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR[d], nc = c + DC[d];
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n || dist[nr][nc] != -1 || g[nr][nc] <= 0) continue;
                    dist[nr][nc] = dist[r][c] + 1;
                    g[nr][nc] = min(g[nr][nc], dist[nr][nc]);   // keep the closest gate
                    q.push({nr, nc});
                }
            }
        }
}

// ---------- Approach 2: Multi-Source BFS ⭐ ----------
void wallsAndGates(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    queue<pair<int, int>> q;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (g[i][j] == 0) q.push({i, j});   // all gates start together
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + DR[d], nc = c + DC[d];
            if (nr < 0 || nc < 0 || nr >= m || nc >= n || g[nr][nc] != INF) continue;   // INF = unvisited room
            g[nr][nc] = g[r][c] + 1;
            q.push({nr, nc});
        }
    }
}

// ---------- Driver ----------
void print(const string& label, const vector<vector<int>>& g) {
    cout << label << ": [";
    for (size_t i = 0; i < g.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < g[i].size(); j++) cout << (j ? "," : "") << g[i][j];
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<vector<int>>> tests = {
        {{INF, -1, 0, INF}, {INF, INF, INF, -1}, {INF, -1, INF, -1}, {0, -1, INF, INF}},
        {{-1}}, {{INF, INF}, {INF, INF}}, {{0, -1, INF}}
    };
    for (auto& t : tests) {
        auto a = t, b = t;
        wallsAndGatesEach(a);
        wallsAndGates(b);
        print("each ", a);
        print("multi", b);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - INT_MAX is exactly LeetCode's INF (2^31 - 1).
 * - `auto a = t, b = t;` makes two independent copies of the grid.
 * - g[r][c] + 1 never overflows here: only gates and filled rooms are popped.
 */
