/*
 * 0678. Valid Parenthesis String  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/valid-parenthesis-string/
 *
 * Problem: '*' can be '(', ')' or empty. Can s be a valid parentheses string?
 *
 * Examples:
 *   "()"       -> true
 *   "(*)"      -> true
 *   "(*))"     -> true
 *   "(((*)"    -> false
 *   "*("       -> false
 *   ")*"       -> false
 *   ""         -> true
 *
 * Approaches:
 *   1. Memo on (index, open count)       O(n^2) time, O(n^2) space
 *   2. Two stacks of indices             O(n) time, O(n) space
 *   3. Range of open counts [lo, hi]  ⭐  O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memo ----------
bool ok(const string& s, int i, int opened, vector<vector<int>>& memo) {
    if (opened < 0 || opened > (int)s.size()) return false;   // more ')' than '(' so far
    if (i == (int)s.size()) return opened == 0;
    int& m = memo[i][opened];
    if (m != -1) return m;
    if (s[i] == '(') m = ok(s, i + 1, opened + 1, memo);
    else if (s[i] == ')') m = ok(s, i + 1, opened - 1, memo);
    else m = ok(s, i + 1, opened + 1, memo) || ok(s, i + 1, opened - 1, memo) || ok(s, i + 1, opened, memo);
    return m;
}

bool checkValidStringMemo(const string& s) {
    vector<vector<int>> memo(s.size() + 1, vector<int>(s.size() + 1, -1));
    return ok(s, 0, 0, memo);
}

// ---------- Approach 2: Two Stacks ----------
bool checkValidStringStacks(const string& s) {
    vector<int> opens, stars;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') opens.push_back(i);
        else if (s[i] == '*') stars.push_back(i);
        else if (!opens.empty()) opens.pop_back();     // prefer a real '('
        else if (!stars.empty()) stars.pop_back();
        else return false;
    }
    while (!opens.empty() && !stars.empty()) {     // leftover '(' needs a '*' after it
        if (opens.back() > stars.back()) return false;
        opens.pop_back();
        stars.pop_back();
    }
    return opens.empty();
}

// ---------- Approach 3: Open-count Range ⭐ ----------
bool checkValidString(const string& s) {
    int lo = 0, hi = 0;                            // min / max possible unmatched '('
    for (char ch : s) {
        if (ch == '(') { lo++; hi++; }
        else if (ch == ')') { lo--; hi--; }
        else { lo--; hi++; }                       // '*': close one, or open one
        if (hi < 0) return false;                  // too many ')' even with every '*' as '('
        lo = max(lo, 0);                           // negative counts aren't real choices
    }
    return lo == 0;
}

// ---------- Driver ----------
int main() {
    cout << boolalpha;
    for (string s : {"()", "(*)", "(*))", "(((*)", "*(", ")*", ""}) {
        cout << "memo  : " << checkValidStringMemo(s) << "\n";
        cout << "stacks: " << checkValidStringStacks(s) << "\n";
        cout << "range : " << checkValidString(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - An int memo (-1 / 0 / 1) caches bool results with an "unknown" state.
 * - vector<int> works as a stack: push_back / back / pop_back.
 * - lo = max(lo, 0) clamps after each step.
 */
