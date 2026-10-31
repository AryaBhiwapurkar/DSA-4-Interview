/*
 * 0200. Number of Islands  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/number-of-islands/
 *
 * Problem: Count groups of 4-connected '1' cells in a grid of '1'/'0'.
 *
 * Examples:
 *   11110/11010/11000/00000  -> 1
 *   11000/11000/00100/00011  -> 3
 *   0                        -> 0
 *   101/010/101              -> 5
 *
 * Approaches:
 *   1. DFS flood fill  ⭐   O(m*n) time, O(m*n) stack   <- go-to
 *   2. BFS flood fill       O(m*n) time, O(min(m,n)) queue typically
 *   3. Union-Find           O(m*n * alpha) time, O(m*n) space
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: DFS Flood Fill ⭐ ----------
void sink(vector<vector<char>>& g, int r, int c) {
    if (r < 0 || c < 0 || r >= (int)g.size() || c >= (int)g[0].size() || g[r][c] != '1') return;
    g[r][c] = '0';                         // visited = sunk
    for (int d = 0; d < 4; d++) sink(g, r + DR[d], c + DC[d]);
}

int numIslands(vector<vector<char>> g) {
    int count = 0;
    for (int r = 0; r < (int)g.size(); r++)
        for (int c = 0; c < (int)g[0].size(); c++)
            if (g[r][c] == '1') { count++; sink(g, r, c); }
    return count;
}

// ---------- Approach 2: BFS Flood Fill ----------
int numIslandsBFS(vector<vector<char>> g) {
    int m = g.size(), n = g[0].size(), count = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (g[i][j] != '1') continue;
            count++;
            queue<pair<int, int>> q;
            q.push({i, j});
            g[i][j] = '0';                 // mark on push, not on pop
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR[d], nc = c + DC[d];
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n || g[nr][nc] != '1') continue;
                    g[nr][nc] = '0';
                    q.push({nr, nc});
                }
            }
        }
    return count;
}

// ---------- Approach 3: Union-Find ----------
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }   // path compression
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};

int numIslandsUF(const vector<vector<char>>& g) {
    int m = g.size(), n = g[0].size(), count = 0;
    DSU dsu(m * n);
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) {
            if (g[r][c] != '1') continue;
            count++;
            if (r + 1 < m && g[r + 1][c] == '1' && dsu.unite(r * n + c, (r + 1) * n + c)) count--;
            if (c + 1 < n && g[r][c + 1] == '1' && dsu.unite(r * n + c, r * n + c + 1)) count--;
        }
    return count;
}

// ---------- Driver ----------
vector<vector<char>> grid(const vector<string>& rows) {
    vector<vector<char>> g;
    for (auto& s : rows) g.push_back(vector<char>(s.begin(), s.end()));
    return g;
}

int main() {
    vector<vector<string>> tests = {
        {"11110", "11010", "11000", "00000"}, {"11000", "11000", "00100", "00011"}, {"0"}, {"101", "010", "101"}
    };
    for (auto& rows : tests) {
        cout << "dfs: " << numIslands(grid(rows)) << "\n";
        cout << "bfs: " << numIslandsBFS(grid(rows)) << "\n";
        cout << "uf : " << numIslandsUF(grid(rows)) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - iota(begin, end, 0) fills parent with 0, 1, 2, ...
 * - `parent[x] = find(parent[x])` inside the return compresses the path.
 * - Cell (r, c) flattens to r * n + c for array-based structures.
 */
