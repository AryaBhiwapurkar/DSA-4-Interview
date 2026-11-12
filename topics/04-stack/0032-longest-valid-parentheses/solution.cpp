/*
 * 0032. Longest Valid Parentheses  |  Hard  |  Stack
 * Link: https://leetcode.com/problems/longest-valid-parentheses/
 *
 * Problem: Length of the longest well-formed parentheses substring.
 *
 * Examples:
 *   "(()"       -> 2
 *   ")()())"    -> 4
 *   ""          -> 0
 *   "()(())"    -> 6
 *   "())(())"   -> 4
 *
 * Approaches:
 *   1. Check every even-length substring     O(n^2) time (with a running balance)
 *   2. DP ending at i                        O(n) time, O(n) space
 *   3. Index stack with base  ⭐             O(n) time, O(n) space   <- go-to
 *   (+ two-pass counters, O(1) space, shown as an extra function)
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Every Substring ----------
int longestValidParenthesesBrute(const string& s) {
    int n = s.size(), best = 0;
    for (int i = 0; i < n; i++) {
        int bal = 0;
        for (int j = i; j < n; j++) {
            bal += s[j] == '(' ? 1 : -1;
            if (bal < 0) break;                    // can't recover
            if (bal == 0) best = max(best, j - i + 1);
        }
    }
    return best;
}

// ---------- Approach 2: DP ----------
int longestValidParenthesesDP(const string& s) {
    int n = s.size(), best = 0;
    vector<int> dp(n, 0);                          // longest valid ending at i
    for (int i = 1; i < n; i++) {
        if (s[i] != ')') continue;
        if (s[i - 1] == '(') dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
        else {
            int j = i - dp[i - 1] - 1;             // char before the block ending at i-1
            if (j >= 0 && s[j] == '(') dp[i] = dp[i - 1] + 2 + (j >= 1 ? dp[j - 1] : 0);
        }
        best = max(best, dp[i]);
    }
    return best;
}

// ---------- Approach 3: Index Stack ⭐ ----------
int longestValidParentheses(const string& s) {
    vector<int> st = {-1};                         // base: index before the current run
    int best = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') st.push_back(i);
        else {
            st.pop_back();
            if (st.empty()) st.push_back(i);       // unmatched ')': new base
            else best = max(best, i - st.back());
        }
    }
    return best;
}

// ---------- Extra: Two-pass Counters, O(1) Space ----------
int longestValidParenthesesCounters(const string& s) {
    int best = 0, open = 0, close = 0;
    for (char c : s) {
        (c == '(' ? open : close)++;
        if (open == close) best = max(best, 2 * close);
        else if (close > open) open = close = 0;
    }
    open = close = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        (s[i] == '(' ? open : close)++;
        if (open == close) best = max(best, 2 * open);
        else if (open > close) open = close = 0;
    }
    return best;
}

// ---------- Driver ----------
int main() {
    for (string s : {"(()", ")()())", "", "()(())", "())(())"}) {
        cout << "brute   : " << longestValidParenthesesBrute(s) << "\n";
        cout << "dp      : " << longestValidParenthesesDP(s) << "\n";
        cout << "stack   : " << longestValidParentheses(s) << "\n";
        cout << "counters: " << longestValidParenthesesCounters(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (cond ? a : b)++ increments whichever variable the ternary selects (both are lvalues).
 * - vector<int> st = {-1} seeds the stack with a sentinel.
 * - open = close = 0 resets both counters in one statement.
 */
