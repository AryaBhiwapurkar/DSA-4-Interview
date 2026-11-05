/*
 * 0010. Regular Expression Matching  |  Hard  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/regular-expression-matching/
 *
 * Problem: Does pattern p (with '.' = any char, 'x*' = zero or more x) match
 *          the whole string s?
 *
 * Examples:
 *   "aa", "a"                 -> false
 *   "aa", "a*"                -> true
 *   "ab", ".*"                -> true
 *   "aab", "c*a*b"            -> true
 *   "mississippi", "mis*is*p*." -> false
 *   "", "a*b*"                -> true
 *
 * Approaches:
 *   1. Plain recursion            exponential time, O(m+n) space
 *   2. Top-down memo (i, j)  ⭐    O(m*n) time, O(m*n) space   <- go-to
 *   3. Bottom-up table            O(m*n) time, O(m*n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Plain Recursion ----------
bool goBrute(const string& s, const string& p, int i, int j) {
    if (j == (int)p.size()) return i == (int)s.size();
    bool first = i < (int)s.size() && (p[j] == s[i] || p[j] == '.');
    if (j + 1 < (int)p.size() && p[j + 1] == '*')
        return goBrute(s, p, i, j + 2) || (first && goBrute(s, p, i + 1, j));   // zero copies / one more
    return first && goBrute(s, p, i + 1, j + 1);
}

bool isMatchBrute(const string& s, const string& p) { return goBrute(s, p, 0, 0); }

// ---------- Approach 2: Top-down Memo ⭐ ----------
bool go(const string& s, const string& p, int i, int j, vector<vector<int>>& memo) {
    if (j == (int)p.size()) return i == (int)s.size();
    int& m = memo[i][j];                           // -1 unknown, 0 false, 1 true
    if (m != -1) return m;
    bool first = i < (int)s.size() && (p[j] == s[i] || p[j] == '.');
    if (j + 1 < (int)p.size() && p[j + 1] == '*')
        m = go(s, p, i, j + 2, memo) || (first && go(s, p, i + 1, j, memo));   // skip "x*" / eat one, stay
    else
        m = first && go(s, p, i + 1, j + 1, memo);
    return m;
}

bool isMatch(const string& s, const string& p) {
    vector<vector<int>> memo(s.size() + 1, vector<int>(p.size() + 1, -1));
    return go(s, p, 0, 0, memo);
}

// ---------- Approach 3: Bottom-up Table ----------
bool isMatchTable(const string& s, const string& p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));   // s[i:] matches p[j:]
    dp[m][n] = true;
    for (int i = m; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--) {
            bool first = i < m && (p[j] == s[i] || p[j] == '.');
            if (j + 1 < n && p[j + 1] == '*') dp[i][j] = dp[i][j + 2] || (first && dp[i + 1][j]);
            else dp[i][j] = first && dp[i + 1][j + 1];
        }
    return dp[0][0];
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"aa", "a"}, {"aa", "a*"}, {"ab", ".*"}, {"aab", "c*a*b"}, {"mississippi", "mis*is*p*."}, {"", "a*b*"}
    };
    cout << boolalpha;
    for (auto& [s, p] : tests) {
        cout << "brute: " << isMatchBrute(s, p) << "\n";
        cout << "memo : " << isMatch(s, p) << "\n";
        cout << "table: " << isMatchTable(s, p) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `first && go(...)` short-circuits, so the recursive call runs only when s[i] exists and matches.
 * - dp is (m+1) x (n+1): row m is "s exhausted", which can still match "x*" pairs.
 * - p[j + 2] is never read: dp[i][j + 2] is valid because j + 1 < n means j + 2 <= n.
 */
