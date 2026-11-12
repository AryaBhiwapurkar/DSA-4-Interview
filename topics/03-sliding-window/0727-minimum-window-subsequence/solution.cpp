/*
 * 0727. Minimum Window Subsequence  |  Hard  |  Sliding Window  |  LC Premium
 * Link: https://leetcode.com/problems/minimum-window-subsequence/
 *
 * Problem: Shortest substring of s1 containing s2 as a subsequence (left-most on ties), or "".
 *
 * Examples:
 *   s1 = "abcdebdde", s2 = "bde"                                 -> "bcde"
 *   s1 = "jmeqksfrsdcmsiwvaovztaqenprpvnbstl", s2 = "u"          -> ""
 *   s1 = "abc", s2 = "abc"                                       -> "abc"
 *   s1 = "fgrqsqsnodwmxzkzxwqegkndaa", s2 = "kzed"               -> "kzxwqegknd"
 *
 * Approaches:
 *   1. DP of latest start               O(|s1| * |s2|) time, O(|s2|) space
 *   2. Forward-backward  ⭐             O(|s1| * |s2|) worst time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DP of Latest Start ----------
string minWindowDP(const string& s1, const string& s2) {
    int m = s2.size(), bestLen = INT_MAX, bestStart = -1;
    vector<int> start(m, -1);                      // start[j]: latest start matching s2[0..j]
    for (int i = 0; i < (int)s1.size(); i++) {
        for (int j = m - 1; j >= 0; j--)           // high to low: read last step's start[j-1]
            if (s1[i] == s2[j]) start[j] = j == 0 ? i : start[j - 1];
        if (start[m - 1] >= 0 && i - start[m - 1] + 1 < bestLen) {
            bestLen = i - start[m - 1] + 1;
            bestStart = start[m - 1];
        }
    }
    return bestStart < 0 ? "" : s1.substr(bestStart, bestLen);
}

// ---------- Approach 2: Forward-Backward ⭐ ----------
string minWindow(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size(), bestStart = -1, bestLen = INT_MAX;
    int i = 0, j = 0;
    while (i < n) {
        if (s1[i] == s2[j] && ++j == m) {          // s2 fully matched, ending at i
            int end = i;
            for (j = m - 1; j >= 0; i--)           // walk back to the latest start
                if (s1[i] == s2[j]) j--;
            i++;                                   // i is now the window start
            if (end - i + 1 < bestLen) bestLen = end - i + 1, bestStart = i;   // strict: keep left-most
            j = 0;                                 // restart just after this start
        }
        i++;
    }
    return bestStart < 0 ? "" : s1.substr(bestStart, bestLen);
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"abcdebdde", "bde"}, {"jmeqksfrsdcmsiwvaovztaqenprpvnbstl", "u"}, {"abc", "abc"},
        {"fgrqsqsnodwmxzkzxwqegkndaa", "kzed"}};
    for (auto& [a, b] : tests) {
        cout << "dp      : \"" << minWindowDP(a, b) << "\"\n";
        cout << "backward: \"" << minWindow(a, b) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - if (a && ++j == m) only increments j when a is true (short-circuit).
 * - for (j = m - 1; j >= 0; i--) reuses existing variables as loop counters.
 * - Updating start[] from high j to low j reuses one array as "previous row".
 */
