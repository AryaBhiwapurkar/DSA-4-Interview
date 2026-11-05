/*
 * 0072. Edit Distance  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/edit-distance/
 *
 * Problem: Minimum inserts, deletes and replacements to turn word1 into word2.
 *
 * Examples:
 *   "horse", "ros"            -> 3
 *   "intention", "execution"  -> 5
 *   "", "abc"                 -> 3
 *   "abc", ""                 -> 3
 *   "same", "same"            -> 0
 *
 * Approaches:
 *   1. Memoized recursion   O(m*n) time, O(m*n) space
 *   2. 2-D table  ⭐         O(m*n) time, O(m*n) space    <- go-to
 *   3. Two rows             O(m*n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
int ed(const string& a, const string& b, int i, int j, vector<vector<int>>& memo) {
    if (i == (int)a.size()) return b.size() - j;   // insert the rest of b
    if (j == (int)b.size()) return a.size() - i;   // delete the rest of a
    if (memo[i][j] != -1) return memo[i][j];
    if (a[i] == b[j]) return memo[i][j] = ed(a, b, i + 1, j + 1, memo);
    return memo[i][j] = 1 + min({ed(a, b, i + 1, j + 1, memo),    // replace
                                 ed(a, b, i + 1, j, memo),        // delete
                                 ed(a, b, i, j + 1, memo)});      // insert
}

int minDistanceMemo(const string& a, const string& b) {
    vector<vector<int>> memo(a.size(), vector<int>(b.size(), -1));
    return ed(a, b, 0, 0, memo);
}

// ---------- Approach 2: 2-D Table ⭐ ----------
int minDistance(const string& a, const string& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; i++) dp[i][0] = i;     // delete everything
    for (int j = 0; j <= n; j++) dp[0][j] = j;     // insert everything
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = a[i - 1] == b[j - 1]
                           ? dp[i - 1][j - 1]
                           : 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
    return dp[m][n];
}

// ---------- Approach 3: Two Rows ----------
int minDistanceRows(const string& a, const string& b) {
    int m = a.size(), n = b.size();
    vector<int> prev(n + 1), cur(n + 1);
    iota(prev.begin(), prev.end(), 0);             // row 0: 0, 1, ..., n
    for (int i = 1; i <= m; i++) {
        cur[0] = i;
        for (int j = 1; j <= n; j++)
            cur[j] = a[i - 1] == b[j - 1] ? prev[j - 1] : 1 + min({prev[j - 1], prev[j], cur[j - 1]});
        swap(prev, cur);
    }
    return prev[n];
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"horse", "ros"}, {"intention", "execution"}, {"", "abc"}, {"abc", ""}, {"same", "same"}
    };
    for (auto& [a, b] : tests) {
        cout << "memo : " << minDistanceMemo(a, b) << "\n";
        cout << "table: " << minDistance(a, b) << "\n";
        cout << "rows : " << minDistanceRows(a, b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - min({x, y, z}) for three-way minimum.
 * - iota(begin, end, 0) fills 0, 1, 2, ... (from <numeric>).
 * - b.size() - j is size_t arithmetic; it's safe here since j <= b.size(), then converts to int.
 */
