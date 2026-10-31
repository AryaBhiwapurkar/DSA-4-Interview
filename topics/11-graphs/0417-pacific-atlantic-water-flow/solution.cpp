/*
 * 0417. Pacific Atlantic Water Flow  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/pacific-atlantic-water-flow/
 *
 * Problem: Rain flows from a cell to any 4-neighbour of equal or lower height.
 *          The Pacific touches the top and left edges, the Atlantic the bottom
 *          and right. Return cells that can drain into both oceans.
 *
 * Examples:
 *   [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
 *       -> [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
 *   [[1]]            -> [[0,0]]
 *   [[1,1],[1,1]]    -> all four cells
 *   [[3,2,1]]        -> all three cells (one row touches both oceans)
 *
 * Approaches:
 *   1. DFS from every cell           O((m*n)^2) time, O(m*n) space
 *   2. Reverse DFS from oceans  ⭐    O(m*n) time, O(m*n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: DFS from Every Cell ----------
vector<vector<int>> pacificAtlanticBrute(const vector<vector<int>>& h) {
    int m = h.size(), n = h[0].size();
    vector<vector<int>> res;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            bool pac = false, atl = false;
            vector<vector<bool>> seen(m, vector<bool>(n, false));
            vector<pair<int, int>> st = {{i, j}};
            seen[i][j] = true;
            while (!st.empty() && !(pac && atl)) {
                auto [r, c] = st.back(); st.pop_back();
                pac |= r == 0 || c == 0;
                atl |= r == m - 1 || c == n - 1;
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR[d], nc = c + DC[d];
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n || seen[nr][nc] || h[nr][nc] > h[r][c]) continue;   // downhill only
                    seen[nr][nc] = true;
                    st.push_back({nr, nc});
                }
            }
            if (pac && atl) res.push_back({i, j});
        }
    return res;
}

// ---------- Approach 2: Reverse DFS from Both Oceans ⭐ ----------
void climb(const vector<vector<int>>& h, int r, int c, vector<vector<bool>>& seen) {
    seen[r][c] = true;
    for (int d = 0; d < 4; d++) {
        int nr = r + DR[d], nc = c + DC[d];
        if (nr < 0 || nc < 0 || nr >= (int)h.size() || nc >= (int)h[0].size()) continue;
        if (seen[nr][nc] || h[nr][nc] < h[r][c]) continue;   // uphill (or level) only
        climb(h, nr, nc, seen);
    }
}

vector<vector<int>> pacificAtlantic(const vector<vector<int>>& h) {
    int m = h.size(), n = h[0].size();
    vector<vector<bool>> pac(m, vector<bool>(n, false)), atl = pac;
    for (int i = 0; i < m; i++) {
        if (!pac[i][0]) climb(h, i, 0, pac);
        if (!atl[i][n - 1]) climb(h, i, n - 1, atl);
    }
    for (int j = 0; j < n; j++) {
        if (!pac[0][j]) climb(h, 0, j, pac);
        if (!atl[m - 1][j]) climb(h, m - 1, j, atl);
    }
    vector<vector<int>> res;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (pac[i][j] && atl[i][j]) res.push_back({i, j});
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<int>> v) {
    sort(v.begin(), v.end());              // normalize: any order is accepted
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << "[" << v[i][0] << "," << v[i][1] << "]";
    cout << "]\n";
}

int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}},
        {{1}}, {{1, 1}, {1, 1}}, {{3, 2, 1}}
    };
    for (auto& h : tests) {
        print("brute  ", pacificAtlanticBrute(h));
        print("reverse", pacificAtlantic(h));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `pac |= cond` on a bool ORs in the new condition.
 * - `vector<vector<bool>> pac(...), atl = pac;` declares two equal-shaped grids.
 * - Recursion depth up to m*n = 4e4 fits the default stack.
 */
