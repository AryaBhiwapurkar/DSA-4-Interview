/*
 * 0120. Triangle  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/triangle/
 *
 * Problem: Minimum top-to-bottom path sum in a number triangle, stepping to
 *          index i or i+1 of the next row.
 *
 * Examples:
 *   [[2],[3,4],[6,5,7],[4,1,8,3]]   -> 11
 *   [[-10]]                         -> -10
 *   [[1],[2,3],[100,100,1]]         -> 5   (greedy gives 103)
 *   [[-1],[2,3],[1,-1,-3]]          -> -1
 *
 * Approaches:
 *   1. Top-down memo              O(n^2) time, O(n^2) space
 *   2. Bottom-up, O(n) space  ⭐   O(n^2) time, O(n) space    <- go-to
 *   3. Top-down table             O(n^2) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Top-down Memo ----------
int best(const vector<vector<int>>& t, int r, int i, vector<vector<int>>& memo, vector<vector<bool>>& done) {
    if (r == (int)t.size() - 1) return t[r][i];
    if (done[r][i]) return memo[r][i];
    done[r][i] = true;
    return memo[r][i] = t[r][i] + min(best(t, r + 1, i, memo, done), best(t, r + 1, i + 1, memo, done));
}

int minimumTotalMemo(const vector<vector<int>>& t) {
    int n = t.size();
    vector<vector<int>> memo(n, vector<int>(n));
    vector<vector<bool>> done(n, vector<bool>(n, false));   // values can be negative: no sentinel
    return best(t, 0, 0, memo, done);
}

// ---------- Approach 2: Bottom-up, O(n) Space ⭐ ----------
int minimumTotal(const vector<vector<int>>& t) {
    vector<int> dp = t.back();                     // copy of the last row
    for (int r = (int)t.size() - 2; r >= 0; r--)
        for (int i = 0; i <= r; i++)
            dp[i] = t[r][i] + min(dp[i], dp[i + 1]);   // dp[i+1] not overwritten yet
    return dp[0];
}

// ---------- Approach 3: Top-down Table ----------
int minimumTotalTopDown(const vector<vector<int>>& t) {
    int n = t.size();
    vector<int> dp = {t[0][0]};
    for (int r = 1; r < n; r++) {
        vector<int> nxt(r + 1);
        nxt[0] = dp[0] + t[r][0];                  // left edge: one parent
        nxt[r] = dp[r - 1] + t[r][r];              // right edge: one parent
        for (int i = 1; i < r; i++) nxt[i] = t[r][i] + min(dp[i - 1], dp[i]);
        dp = nxt;
    }
    return *min_element(dp.begin(), dp.end());
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}, {{-10}}, {{1}, {2, 3}, {100, 100, 1}}, {{-1}, {2, 3}, {1, -1, -3}}
    };
    for (auto& t : tests) {
        cout << "memo    : " << minimumTotalMemo(t) << "\n";
        cout << "bottomup: " << minimumTotal(t) << "\n";
        cout << "topdown : " << minimumTotalTopDown(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `vector<int> dp = t.back();` copies, so the input is untouched.
 * - A separate `done` grid replaces a sentinel when every int value is a valid answer.
 * - *min_element(v.begin(), v.end()) returns the smallest value.
 */
