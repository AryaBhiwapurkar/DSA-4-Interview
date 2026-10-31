/*
 * 0778. Swim in Rising Water  |  Hard  |  Advanced Graphs
 * Link: https://leetcode.com/problems/swim-in-rising-water/
 *
 * Problem: n x n grid of distinct heights 0..n^2-1. At time t you can move
 *          between adjacent cells with height <= t. Least t to go from
 *          (0,0) to (n-1,n-1).
 *
 * Examples:
 *   [[0,2],[1,3]]  -> 3
 *   [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]  -> 16
 *   [[0]]          -> 0
 *   [[3,2],[0,1]]  -> 3 (the start cell itself is the bottleneck)
 *
 * Approaches:
 *   1. Binary search on t + DFS          O(n^2 log n) time, O(n^2) space
 *   2. Dijkstra on the max height  ⭐     O(n^2 log n) time, O(n^2) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: Binary search on t + DFS ----------
bool canReach(const vector<vector<int>>& g, int t) {
    int n = g.size();
    if (g[0][0] > t) return false;
    vector<vector<bool>> seen(n, vector<bool>(n, false));
    vector<pair<int, int>> st = {{0, 0}};
    seen[0][0] = true;
    while (!st.empty()) {
        auto [r, c] = st.back(); st.pop_back();
        if (r == n - 1 && c == n - 1) return true;
        for (int d = 0; d < 4; d++) {
            int nr = r + DR[d], nc = c + DC[d];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n || seen[nr][nc] || g[nr][nc] > t) continue;
            seen[nr][nc] = true;
            st.push_back({nr, nc});
        }
    }
    return false;
}

int swimInWaterBinary(const vector<vector<int>>& g) {
    int n = g.size(), lo = 0, hi = n * n - 1;
    while (lo < hi) {                             // smallest t with canReach(t) true
        int mid = lo + (hi - lo) / 2;
        if (canReach(g, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Approach 2: Dijkstra on the max height ⭐ ----------
int swimInWater(const vector<vector<int>>& g) {
    int n = g.size();
    vector<vector<bool>> seen(n, vector<bool>(n, false));
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;   // (time needed, r, c)
    pq.push({g[0][0], 0, 0});
    seen[0][0] = true;
    while (true) {
        auto [t, r, c] = pq.top(); pq.pop();
        if (r == n - 1 && c == n - 1) return t;
        for (int d = 0; d < 4; d++) {
            int nr = r + DR[d], nc = c + DC[d];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n || seen[nr][nc]) continue;
            seen[nr][nc] = true;                  // safe on push: key only grows with t
            pq.push({max(t, g[nr][nc]), nr, nc}); // path cost = highest cell on it
        }
    }
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{0, 2}, {1, 3}},
        {{0, 1, 2, 3, 4}, {24, 23, 22, 21, 5}, {12, 13, 14, 15, 16}, {11, 17, 18, 19, 20}, {10, 9, 8, 7, 6}},
        {{0}},
        {{3, 2}, {0, 1}},
    };
    for (auto& g : tests) {
        cout << "binary  : " << swimInWaterBinary(g) << "\n";
        cout << "dijkstra: " << swimInWater(g) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `array<int, 3>` in a min-heap acts like a (key, r, c) tuple.
 * - `lo + (hi - lo) / 2` is the overflow-safe midpoint habit.
 * - vector<pair<int,int>> with push_back/pop_back is an explicit DFS stack.
 */
