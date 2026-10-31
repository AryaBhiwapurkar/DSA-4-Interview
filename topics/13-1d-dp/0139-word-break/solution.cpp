/*
 * 0139. Word Break  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/word-break/
 *
 * Problem: Can s be split into a sequence of dictionary words (each word
 *          reusable any number of times)?
 *
 * Examples:
 *   "leetcode", ["leet","code"]                         -> true
 *   "applepenapple", ["apple","pen"]                    -> true
 *   "catsandog", ["cats","dog","sand","and","cat"]      -> false
 *   "cars", ["car","ca","rs"]                           -> true (greedy "car" fails)
 *   "aaaaaaaaaaaaaaaaaaab", ["a","aa","aaa"]            -> false (blows up plain recursion)
 *
 * Approaches:
 *   1. Plain recursion over prefixes   O(W^n) worst case, O(n) space
 *   2. Memoized recursion              O(n * W * L) time, O(n) space
 *   3. Bottom-up prefix DP  ⭐          O(n * W * L) time, O(n) space   <- go-to
 *   W = dictionary size, L = max word length.
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Plain Recursion ----------
bool canBreak(const string& s, int i, const vector<string>& dict) {
    if (i == (int)s.size()) return true;
    for (auto& w : dict)
        if (s.compare(i, w.size(), w) == 0 && canBreak(s, i + w.size(), dict)) return true;
    return false;
}

bool wordBreakBrute(const string& s, const vector<string>& dict) { return canBreak(s, 0, dict); }

// ---------- Approach 2: Memoized Recursion ----------
bool canBreakMemo(const string& s, int i, const vector<string>& dict, vector<int>& memo) {
    if (i == (int)s.size()) return true;
    if (memo[i] != -1) return memo[i];
    for (auto& w : dict)
        if (s.compare(i, w.size(), w) == 0 && canBreakMemo(s, i + w.size(), dict, memo)) {
            memo[i] = 1;
            return true;
        }
    memo[i] = 0;                                  // suffix from i is a dead end: never retry it
    return false;
}

bool wordBreakMemo(const string& s, const vector<string>& dict) {
    vector<int> memo(s.size(), -1);
    return canBreakMemo(s, 0, dict, memo);
}

// ---------- Approach 3: Bottom-up Prefix DP ⭐ ----------
bool wordBreak(const string& s, const vector<string>& dict) {
    int n = s.size();
    vector<bool> dp(n + 1, false);                // dp[i]: s[0..i) can be split
    dp[0] = true;
    for (int i = 1; i <= n; i++)
        for (auto& w : dict) {
            int len = w.size();
            if (len <= i && dp[i - len] && s.compare(i - len, len, w) == 0) { dp[i] = true; break; }
        }
    return dp[n];
}

// ---------- Driver ----------
int main() {
    vector<pair<string, vector<string>>> tests = {
        {"leetcode", {"leet", "code"}},
        {"applepenapple", {"apple", "pen"}},
        {"catsandog", {"cats", "dog", "sand", "and", "cat"}},
        {"cars", {"car", "ca", "rs"}},
        {"aaaaaaaaaaaaaaaaaaab", {"a", "aa", "aaa"}},
    };
    cout << boolalpha;
    for (auto& [s, dict] : tests) {
        cout << "brute: " << wordBreakBrute(s, dict) << "\n";
        cout << "memo : " << wordBreakMemo(s, dict) << "\n";
        cout << "dp   : " << wordBreak(s, dict) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - s.compare(pos, len, w) == 0 tests a substring match without allocating a substr.
 * - `cout << boolalpha` prints bools as true/false.
 * - An int memo (-1 / 0 / 1) gives a third "unknown" state that vector<bool> can't hold.
 */
