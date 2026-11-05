/*
 * 0064. Minimum Path Sum  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/minimum-path-sum/
 *
 * Problem: Smallest sum of cells on a right/down path from the top-left to the
 *          bottom-right of a grid of non-negative costs.
 *
 * Examples:
 *   [[1,3,1],[1,5,1],[4,2,1]]   -> 7
 *   [[1,2,3],[4,5,6]]           -> 12
 *   [[5]]                       -> 5
 *   [[1,2,3]]                   -> 6
 *   [[1],[2],[3]]               -> 6
 *
 * Approaches:
 *   1. Memoized recursion   O(m*n) time, O(m*n) space
 *   2. 2-D table            O(m*n) time, O(m*n) space
 *   3. 1-D rolling row  ⭐   O(m*n) time, O(n) space     <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
int cost(const vector<vector<int>>& g, int r, int c, vector<vector<int>>& memo) {
    if (r < 0 || c < 0) return INT_MAX;            // never chosen by min
    if (r == 0 && c == 0) return g[0][0];
    if (memo[r][c] != -1) return memo[r][c];
    return memo[r][c] = g[r][c] + min(cost(g, r - 1, c, memo), cost(g, r, c - 1, memo));
}

int minPathSumMemo(const vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> memo(m, vector<int>(n, -1));
    return cost(g, m - 1, n - 1, memo);
}

// ---------- Approach 2: 2-D Table ----------
int minPathSumTable(const vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> dp(m, vector<int>(n));
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) {
            if (r == 0 && c == 0) dp[r][c] = g[r][c];
            else if (r == 0) dp[r][c] = g[r][c] + dp[r][c - 1];      // only left
            else if (c == 0) dp[r][c] = g[r][c] + dp[r - 1][c];      // only top
            else dp[r][c] = g[r][c] + min(dp[r - 1][c], dp[r][c - 1]);
        }
    return dp[m - 1][n - 1];
}

// ---------- Approach 3: 1-D Rolling Row ⭐ ----------
int minPathSum(const vector<vector<int>>& g) {
    int n = g[0].size();
    vector<int> row(n, INT_MAX);
    row[0] = 0;                                    // so the start cell adds to 0
    for (auto& cells : g) {
        row[0] += cells[0];
        for (int c = 1; c < n; c++)
            row[c] = cells[c] + min(row[c], row[c - 1]);   // row[c] = top, row[c-1] = left
    }
    return row[n - 1];
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}, {{1, 2, 3}, {4, 5, 6}}, {{5}}, {{1, 2, 3}}, {{1}, {2}, {3}}
    };
    for (auto& g : tests) {
        cout << "memo : " << minPathSumMemo(g) << "\n";
        cout << "table: " << minPathSumTable(g) << "\n";
        cout << "row  : " << minPathSum(g) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - INT_MAX is safe as "no neighbour" only inside min(); never add to it.
 * - In the row version, the first row's INT_MAX "tops" always lose to the left neighbour.
 * - vector<vector<int>> dp(m, vector<int>(n)) value-initialises to 0.
 */
