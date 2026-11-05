/*
 * 0097. Interleaving String  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/interleaving-string/
 *
 * Problem: Can s3 be formed by merging s1 and s2 while keeping each one's
 *          character order?
 *
 * Examples:
 *   "aabcc", "dbbca", "aadbbcbcac"   -> true
 *   "aabcc", "dbbca", "aadbbbaccc"   -> false
 *   "", "", ""                       -> true
 *   "a", "", "a"                     -> true
 *   "ab", "c", "abcd"                -> false  (length mismatch)
 *
 * Approaches:
 *   1. Memoized recursion (i, j)    O(m*n) time, O(m*n) space
 *   2. 2-D table  ⭐                 O(m*n) time, O(m*n) space   <- go-to
 *   3. 1-D row                      O(m*n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
bool ok(const string& a, const string& b, const string& c, int i, int j, vector<vector<int>>& memo) {
    if (i == (int)a.size() && j == (int)b.size()) return true;
    int& m = memo[i][j];                           // -1 unknown, 0 false, 1 true
    if (m != -1) return m;
    int k = i + j;
    m = (i < (int)a.size() && a[i] == c[k] && ok(a, b, c, i + 1, j, memo)) ||
        (j < (int)b.size() && b[j] == c[k] && ok(a, b, c, i, j + 1, memo));
    return m;
}

bool isInterleaveMemo(const string& s1, const string& s2, const string& s3) {
    if (s1.size() + s2.size() != s3.size()) return false;
    vector<vector<int>> memo(s1.size() + 1, vector<int>(s2.size() + 1, -1));
    return ok(s1, s2, s3, 0, 0, memo);
}

// ---------- Approach 2: 2-D Table ⭐ ----------
bool isInterleave(const string& s1, const string& s2, const string& s3) {
    int m = s1.size(), n = s2.size();
    if (m + n != (int)s3.size()) return false;
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));   // s1[:i] + s2[:j] form s3[:i+j]
    dp[0][0] = true;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            if (i > 0 && s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) dp[i][j] = true;   // last from s1
            if (j > 0 && s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]) dp[i][j] = true;   // last from s2
        }
    return dp[m][n];
}

// ---------- Approach 3: 1-D Row ----------
bool isInterleaveRow(const string& s1, const string& s2, const string& s3) {
    int m = s1.size(), n = s2.size();
    if (m + n != (int)s3.size()) return false;
    vector<bool> row(n + 1, false);
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            if (i == 0 && j == 0) { row[j] = true; continue; }
            bool fromS1 = i > 0 && row[j] && s1[i - 1] == s3[i + j - 1];   // row[j] = dp[i-1][j]
            bool fromS2 = j > 0 && row[j - 1] && s2[j - 1] == s3[i + j - 1];
            row[j] = fromS1 || fromS2;
        }
    return row[n];
}

// ---------- Driver ----------
int main() {
    vector<array<string, 3>> tests = {
        {"aabcc", "dbbca", "aadbbcbcac"}, {"aabcc", "dbbca", "aadbbbaccc"}, {"", "", ""}, {"a", "", "a"}, {"ab", "c", "abcd"}
    };
    cout << boolalpha;
    for (auto& [s1, s2, s3] : tests) {
        cout << "memo : " << isInterleaveMemo(s1, s2, s3) << "\n";
        cout << "table: " << isInterleave(s1, s2, s3) << "\n";
        cout << "row  : " << isInterleaveRow(s1, s2, s3) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - An int memo (-1/0/1) distinguishes "unknown" from false.
 * - Structured bindings work on std::array: auto& [s1, s2, s3].
 * - cout << boolalpha prints true/false instead of 1/0.
 */
