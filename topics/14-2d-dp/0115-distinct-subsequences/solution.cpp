/*
 * 0115. Distinct Subsequences  |  Hard  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/distinct-subsequences/
 *
 * Problem: Count the ways to pick positions in s that spell t (subsequences of
 *          s equal to t).
 *
 * Examples:
 *   "rabbbit", "rabbit"   -> 3
 *   "babgbag", "bag"      -> 5
 *   "abc", ""             -> 1  (the empty subsequence)
 *   "", "a"               -> 0
 *   "aaa", "aa"           -> 3
 *
 * Approaches:
 *   1. Memoized recursion (i, j)        O(m*n) time, O(m*n) space
 *   2. 2-D table  ⭐                     O(m*n) time, O(m*n) space   <- go-to
 *   3. 1-D row, j iterated backwards    O(m*n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;   // intermediates can overflow even 64 bits; unsigned wraparound is defined

// ---------- Approach 1: Memoized Recursion ----------
ull ways(const string& s, const string& t, int i, int j, vector<vector<ull>>& memo, vector<vector<bool>>& done) {
    if (j == (int)t.size()) return 1;
    if (s.size() - i < t.size() - j) return 0;    // not enough characters left
    if (done[i][j]) return memo[i][j];
    done[i][j] = true;
    ull r = ways(s, t, i + 1, j, memo, done);      // skip s[i]
    if (s[i] == t[j]) r += ways(s, t, i + 1, j + 1, memo, done);   // use s[i] as t[j]
    return memo[i][j] = r;
}

int numDistinctMemo(const string& s, const string& t) {
    vector<vector<ull>> memo(s.size() + 1, vector<ull>(t.size() + 1));
    vector<vector<bool>> done(s.size() + 1, vector<bool>(t.size() + 1, false));
    return (int)ways(s, t, 0, 0, memo, done);
}

// ---------- Approach 2: 2-D Table ⭐ ----------
int numDistinct(const string& s, const string& t) {
    int m = s.size(), n = t.size();
    vector<vector<ull>> dp(m + 1, vector<ull>(n + 1, 0));   // ways s[:i] produces t[:j]
    for (int i = 0; i <= m; i++) dp[i][0] = 1;             // empty t: pick nothing
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];                       // don't use s[i-1]
            if (s[i - 1] == t[j - 1]) dp[i][j] += dp[i - 1][j - 1];
        }
    return (int)dp[m][n];
}

// ---------- Approach 3: 1-D Row ----------
int numDistinctRow(const string& s, const string& t) {
    int n = t.size();
    vector<ull> row(n + 1, 0);
    row[0] = 1;
    for (char c : s)
        for (int j = n; j >= 1; j--)               // backwards: row[j-1] is still the previous row
            if (c == t[j - 1]) row[j] += row[j - 1];
    return (int)row[n];
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {{"rabbbit", "rabbit"}, {"babgbag", "bag"}, {"abc", ""}, {"", "a"}, {"aaa", "aa"}};
    for (auto& [s, t] : tests) {
        cout << "memo : " << numDistinctMemo(s, t) << "\n";
        cout << "table: " << numDistinct(s, t) << "\n";
        cout << "row  : " << numDistinctRow(s, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Signed overflow is UB; unsigned wraps mod 2^64, and the final answer (< 2^31) is exact
 *   because the DP only adds.
 * - s.size() - i is unsigned; it's safe here because i <= s.size().
 * - A separate `done` grid avoids a sentinel when 0 is a valid count.
 */
