/*
 * 0130. Surrounded Regions  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/surrounded-regions/
 *
 * Problem: Flip every 'O' region that doesn't touch the grid border to 'X',
 *          in place.
 *
 * Examples:
 *   XXXX/XOOX/XXOX/XOXX  -> XXXX/XXXX/XXXX/XOXX
 *   X                    -> X
 *   OO/OO                -> OO/OO (all on the border)
 *   XXX/XOX/XXX          -> XXX/XXX/XXX
 *
 * Approaches:
 *   1. BFS per region            O(m*n) time, O(m*n) space
 *   2. DFS from border  ⭐        O(m*n) time, O(m*n) stack   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: BFS per Region ----------
void solveBFS(vector<vector<char>>& b) {
    int m = b.size(), n = b[0].size();
    vector<vector<bool>> seen(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (b[i][j] != 'O' || seen[i][j]) continue;
            vector<pair<int, int>> region;
            bool border = false;
            queue<pair<int, int>> q;
            q.push({i, j});
            seen[i][j] = true;
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                region.push_back({r, c});
                if (r == 0 || c == 0 || r == m - 1 || c == n - 1) border = true;
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR[d], nc = c + DC[d];
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n || seen[nr][nc] || b[nr][nc] != 'O') continue;
                    seen[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
            if (!border) for (auto [r, c] : region) b[r][c] = 'X';
        }
}

// ---------- Approach 2: DFS from the Border ⭐ ----------
void markSafe(vector<vector<char>>& b, int r, int c) {
    if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size() || b[r][c] != 'O') return;
    b[r][c] = 'T';                         // connected to the border: safe
    for (int d = 0; d < 4; d++) markSafe(b, r + DR[d], c + DC[d]);
}

void solve(vector<vector<char>>& b) {
    int m = b.size(), n = b[0].size();
    for (int i = 0; i < m; i++) { markSafe(b, i, 0); markSafe(b, i, n - 1); }
    for (int j = 0; j < n; j++) { markSafe(b, 0, j); markSafe(b, m - 1, j); }
    for (auto& row : b)
        for (char& ch : row) {
            if (ch == 'O') ch = 'X';       // enclosed
            else if (ch == 'T') ch = 'O';  // restore safe cells
        }
}

// ---------- Driver ----------
vector<vector<char>> grid(const vector<string>& rows) {
    vector<vector<char>> g;
    for (auto& s : rows) g.push_back(vector<char>(s.begin(), s.end()));
    return g;
}

void print(const string& label, const vector<vector<char>>& g) {
    cout << label << ": [";
    for (size_t i = 0; i < g.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < g[i].size(); j++) cout << (j ? "," : "") << '"' << g[i][j] << '"';
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<string>> tests = {{"XXXX", "XOOX", "XXOX", "XOXX"}, {"X"}, {"OO", "OO"}, {"XXX", "XOX", "XXX"}};
    for (auto& rows : tests) {
        auto a = grid(rows), b = grid(rows);
        solveBFS(a);
        solve(b);
        print("bfs   ", a);
        print("border", b);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (char& ch : row)` edits cells in place through a reference.
 * - auto [r, c] = q.front(); unpacks a pair (copy, so pop() afterwards is safe).
 * - Recursion depth up to m*n = 4e4 frames fits the default 8 MB stack.
 */
