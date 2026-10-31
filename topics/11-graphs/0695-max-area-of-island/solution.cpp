/*
 * 0695. Max Area of Island  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/max-area-of-island/
 *
 * Problem: Largest number of cells in a 4-connected group of 1s (0 if none).
 *
 * Examples:
 *   8x13 LeetCode grid       -> 6
 *   [[0,0,0,0,0,0,0,0]]      -> 0
 *   [[1,1],[1,0]]            -> 3
 *   [[1,0],[0,1]]            -> 1 (diagonal doesn't connect)
 *
 * Approaches:
 *   1. DFS returning area  ⭐   O(m*n) time, O(m*n) stack   <- go-to
 *   2. BFS counting pops        O(m*n) time, O(m*n) queue
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: DFS Returning Area ⭐ ----------
int area(vector<vector<int>>& g, int r, int c) {
    if (r < 0 || c < 0 || r >= (int)g.size() || c >= (int)g[0].size() || g[r][c] != 1) return 0;
    g[r][c] = 0;                           // sink before recursing
    int a = 1;
    for (int d = 0; d < 4; d++) a += area(g, r + DR[d], c + DC[d]);
    return a;
}

int maxAreaOfIsland(vector<vector<int>> g) {
    int best = 0;
    for (int r = 0; r < (int)g.size(); r++)
        for (int c = 0; c < (int)g[0].size(); c++)
            if (g[r][c] == 1) best = max(best, area(g, r, c));
    return best;
}

// ---------- Approach 2: BFS Counting Pops ----------
int maxAreaOfIslandBFS(vector<vector<int>> g) {
    int m = g.size(), n = g[0].size(), best = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (g[i][j] != 1) continue;
            int a = 0;
            queue<pair<int, int>> q;
            q.push({i, j});
            g[i][j] = 0;
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                a++;
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR[d], nc = c + DC[d];
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n || g[nr][nc] != 1) continue;
                    g[nr][nc] = 0;
                    q.push({nr, nc});
                }
            }
            best = max(best, a);
        }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
         {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
         {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}},
        {{0, 0, 0, 0, 0, 0, 0, 0}}, {{1, 1}, {1, 0}}, {{1, 0}, {0, 1}}
    };
    for (auto& g : tests) {
        cout << "dfs: " << maxAreaOfIsland(g) << "\n";
        cout << "bfs: " << maxAreaOfIslandBFS(g) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Taking the grid by value gives each approach its own copy to sink.
 * - `a += area(...)` accumulates the recursive contributions.
 */
