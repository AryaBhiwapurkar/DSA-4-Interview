/*
 * 0994. Rotting Oranges  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/rotting-oranges/
 *
 * Problem: 0 empty, 1 fresh, 2 rotten. Each minute rot spreads to 4-neighbours.
 *          Minutes until no fresh orange remains, or -1.
 *
 * Examples:
 *   [[2,1,1],[1,1,0],[0,1,1]]  -> 4
 *   [[2,1,1],[0,1,1],[1,0,1]]  -> -1
 *   [[0,2]]                    -> 0
 *   [[1]]                      -> -1 (no rotten source)
 *   [[0]]                      -> 0
 *
 * Approaches:
 *   1. Repeated full-grid simulation    O((m*n)^2) time, O(m*n) space
 *   2. Multi-source BFS  ⭐              O(m*n) time, O(m*n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: Repeated Full-Grid Simulation ----------
int orangesRottingSim(vector<vector<int>> g) {
    int m = g.size(), n = g[0].size(), minutes = 0;
    while (true) {
        auto next = g;                     // rot spreads one step per minute
        bool changed = false, fresh = false;
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++) {
                if (g[r][c] != 1) continue;
                fresh = true;
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR[d], nc = c + DC[d];
                    if (nr >= 0 && nc >= 0 && nr < m && nc < n && g[nr][nc] == 2) { next[r][c] = 2; changed = true; break; }
                }
            }
        if (!fresh) return minutes;
        if (!changed) return -1;
        g = move(next);
        minutes++;
    }
}

// ---------- Approach 2: Multi-Source BFS ⭐ ----------
int orangesRotting(vector<vector<int>> g) {
    int m = g.size(), n = g[0].size(), fresh = 0, minutes = 0;
    queue<pair<int, int>> q;
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) {
            if (g[r][c] == 2) q.push({r, c});   // every rotten orange starts at once
            else if (g[r][c] == 1) fresh++;
        }
    while (!q.empty() && fresh > 0) {      // stop as soon as nothing is fresh
        for (int sz = q.size(); sz > 0; sz--) {
            auto [r, c] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr < 0 || nc < 0 || nr >= m || nc >= n || g[nr][nc] != 1) continue;
                g[nr][nc] = 2;
                fresh--;
                q.push({nr, nc});
            }
        }
        minutes++;
    }
    return fresh == 0 ? minutes : -1;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}, {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}, {{0, 2}}, {{1}}, {{0}}
    };
    for (auto& g : tests) {
        cout << "sim: " << orangesRottingSim(g) << "\n";
        cout << "bfs: " << orangesRotting(g) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (int sz = q.size(); sz > 0; sz--)` freezes the level size before pushing.
 * - `auto next = g;` deep-copies a vector<vector<int>>.
 */
