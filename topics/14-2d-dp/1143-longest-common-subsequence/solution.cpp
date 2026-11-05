/*
 * 1143. Longest Common Subsequence  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/longest-common-subsequence/
 *
 * Problem: Length of the longest subsequence shared by two strings.
 *
 * Examples:
 *   "abcde", "ace"   -> 3
 *   "abc", "abc"     -> 3
 *   "abc", "def"     -> 0
 *   "aaaa", "aa"     -> 2
 *   "bsbininm", "jmjkbkjkv" -> 1
 *
 * Approaches:
 *   1. Memoized recursion   O(m*n) time, O(m*n) space
 *   2. 2-D table  ⭐         O(m*n) time, O(m*n) space    <- go-to
 *   3. Two rows             O(m*n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
int lcs(const string& a, const string& b, int i, int j, vector<vector<int>>& memo) {
    if (i == (int)a.size() || j == (int)b.size()) return 0;   // a suffix is empty
    if (memo[i][j] != -1) return memo[i][j];
    if (a[i] == b[j]) return memo[i][j] = 1 + lcs(a, b, i + 1, j + 1, memo);
    return memo[i][j] = max(lcs(a, b, i + 1, j, memo), lcs(a, b, i, j + 1, memo));
}

int longestCommonSubsequenceMemo(const string& a, const string& b) {
    vector<vector<int>> memo(a.size(), vector<int>(b.size(), -1));
    return lcs(a, b, 0, 0, memo);
}

// ---------- Approach 2: 2-D Table ⭐ ----------
int longestCommonSubsequence(const string& a, const string& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));    // row/col 0 = empty prefix
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1           // pair them up
                                            : max(dp[i - 1][j], dp[i][j - 1]);  // drop one
    return dp[m][n];
}

// ---------- Approach 3: Two Rows ----------
int longestCommonSubsequenceRows(const string& a, const string& b) {
    int n = b.size();
    vector<int> prev(n + 1, 0), cur(n + 1, 0);
    for (char x : a) {
        for (int j = 1; j <= n; j++)
            cur[j] = x == b[j - 1] ? prev[j - 1] + 1 : max(prev[j], cur[j - 1]);
        swap(prev, cur);                           // O(1): swaps buffers
    }
    return prev[n];
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"abcde", "ace"}, {"abc", "abc"}, {"abc", "def"}, {"aaaa", "aa"}, {"bsbininm", "jmjkbkjkv"}
    };
    for (auto& [a, b] : tests) {
        cout << "memo : " << longestCommonSubsequenceMemo(a, b) << "\n";
        cout << "table: " << longestCommonSubsequence(a, b) << "\n";
        cout << "rows : " << longestCommonSubsequenceRows(a, b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - swap(prev, cur) on vectors swaps internal pointers in O(1).
 * - The ternary spans two lines: match case first, mismatch second.
 * - dp is (m+1) x (n+1) so index 0 means "empty prefix".
 */
