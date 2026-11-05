/*
 * 0329. Longest Increasing Path in a Matrix  |  Hard  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
 *
 * Problem: Length of the longest strictly increasing path moving up/down/left/
 *          right in a grid.
 *
 * Examples:
 *   [[9,9,4],[6,6,8],[2,1,1]]   -> 4
 *   [[3,4,5],[3,2,6],[2,2,1]]   -> 4
 *   [[1]]                       -> 1
 *   [[7,7],[7,7]]               -> 1
 *   [[1,2,3],[6,5,4],[7,8,9]]   -> 9
 *
 * Approaches:
 *   1. Plain DFS from every cell          exponential worst case, O(m*n) space
 *   2. DFS + memo  ⭐                      O(m*n) time, O(m*n) space   <- go-to
 *   3. Topological sort (peel by layers)  O(m*n) time, O(m*n) space
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[] = {1, -1, 0, 0}, DC[] = {0, 0, 1, -1};

// ---------- Approach 1: Plain DFS ----------
int dfsBrute(const vector<vector<int>>& g, int r, int c) {
    int best = 1;
    for (int d = 0; d < 4; d++) {
        int nr = r + DR[d], nc = c + DC[d];
        if (nr >= 0 && nr < (int)g.size() && nc >= 0 && nc < (int)g[0].size() && g[nr][nc] > g[r][c])
            best = max(best, 1 + dfsBrute(g, nr, nc));
    }
    return best;
}

int longestIncreasingPathBrute(const vector<vector<int>>& g) {
    int best = 0;
    for (int r = 0; r < (int)g.size(); r++)
        for (int c = 0; c < (int)g[0].size(); c++) best = max(best, dfsBrute(g, r, c));
    return best;
}

// ---------- Approach 2: DFS + Memo ⭐ ----------
int dfs(const vector<vector<int>>& g, int r, int c, vector<vector<int>>& memo) {
    if (memo[r][c]) return memo[r][c];             // 0 = not computed (answers are >= 1)
    int best = 1;
    for (int d = 0; d < 4; d++) {
        int nr = r + DR[d], nc = c + DC[d];
        if (nr >= 0 && nr < (int)g.size() && nc >= 0 && nc < (int)g[0].size() && g[nr][nc] > g[r][c])
            best = max(best, 1 + dfs(g, nr, nc, memo));   // strictly larger: no cycles
    }
    return memo[r][c] = best;
}

int longestIncreasingPath(const vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size(), best = 0;
    vector<vector<int>> memo(m, vector<int>(n, 0));
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) best = max(best, dfs(g, r, c, memo));
    return best;
}

// ---------- Approach 3: Topological Sort ----------
int longestIncreasingPathTopo(const vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> out(m, vector<int>(n, 0));    // number of strictly larger neighbours
    queue<pair<int, int>> q;
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) {
            for (int d = 0; d < 4; d++) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && g[nr][nc] > g[r][c]) out[r][c]++;
            }
            if (out[r][c] == 0) q.push({r, c});         // local maxima start the peel
        }
    int layers = 0;
    while (!q.empty()) {
        layers++;
        for (int sz = q.size(); sz > 0; sz--) {
            auto [r, c] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r + DR[d], nc = c + DC[d];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && g[nr][nc] < g[r][c] && --out[nr][nc] == 0)
                    q.push({nr, nc});
            }
        }
    }
    return layers;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}}, {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}}, {{1}}, {{7, 7}, {7, 7}},
        {{1, 2, 3}, {6, 5, 4}, {7, 8, 9}}
    };
    for (auto& g : tests) {
        cout << "brute: " << longestIncreasingPathBrute(g) << "\n";
        cout << "memo : " << longestIncreasingPath(g) << "\n";
        cout << "topo : " << longestIncreasingPathTopo(g) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Parallel DR/DC arrays are a compact way to loop over the 4 neighbours.
 * - `--out[nr][nc] == 0` decrements, then tests, in one expression.
 * - auto [r, c] = q.front() unpacks a pair (C++17).
 */
