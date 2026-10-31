/*
 * 0091. Decode Ways  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/decode-ways/
 *
 * Problem: Digits map to letters 1->A ... 26->Z. Count the ways to split the
 *          digit string into valid codes (no leading zeros, nothing above 26).
 *
 * Examples:
 *   "12"     -> 2
 *   "226"    -> 3
 *   "06"     -> 0
 *   "10"     -> 1
 *   "2101"   -> 1
 *   "11106"  -> 2
 *   "27"     -> 1
 *
 * Approaches:
 *   1. Memoized recursion            O(n) time, O(n) space
 *   2. Two variables (bottom-up)  ⭐  O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
// ways(i) = number of decodings of s[i..].
int ways(const string& s, int i, vector<int>& memo) {
    if (i == (int)s.size()) return 1;             // consumed everything: one valid decoding
    if (s[i] == '0') return 0;                    // no code starts with 0
    if (memo[i] != -1) return memo[i];
    int res = ways(s, i + 1, memo);
    if (i + 1 < (int)s.size() && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')))
        res += ways(s, i + 2, memo);
    return memo[i] = res;
}

int numDecodingsMemo(const string& s) {
    vector<int> memo(s.size(), -1);
    return ways(s, 0, memo);
}

// ---------- Approach 2: Two Variables ⭐ ----------
int numDecodings(const string& s) {
    int prev2 = 1, prev1 = s[0] != '0';           // dp[0] (empty prefix), dp[1]
    for (int i = 2; i <= (int)s.size(); i++) {
        int cur = 0;
        if (s[i - 1] != '0') cur += prev1;        // last char as a single code
        int two = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
        if (two >= 10 && two <= 26) cur += prev2; // last two chars as one code (10..26)
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ---------- Driver ----------
int main() {
    for (string s : {"12", "226", "06", "10", "2101", "11106", "27"}) {
        cout << "memo: " << numDecodingsMemo(s) << "\n";
        cout << "dp  : " << numDecodings(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `c - '0'` turns a digit char into its int value.
 * - `int x = (cond);` stores a bool as 0/1.
 * - Char comparisons like `s[i + 1] <= '6'` work because digits are contiguous in ASCII.
 */
