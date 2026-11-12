/*
 * 1249. Minimum Remove to Make Valid Parentheses  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
 *
 * Problem: Remove the fewest parentheses so the string is valid; return any valid result.
 *
 * Examples:
 *   "lee(t(c)o)de)"  -> "lee(t(c)o)de"
 *   "a)b(c)d"        -> "ab(c)d"
 *   "))(("           -> ""
 *   "(a(b)"          -> "a(b)"   (two-pass gives "(ab)": also valid)
 *   "abc"            -> "abc"
 *
 * Approaches:
 *   1. Two passes with a counter         O(n) time, O(n) space
 *   2. Index stack + removal set  ⭐     O(n) time, O(n) space   <- go-to
 *   (Any valid minimal answer is accepted; the two approaches may pick different brackets.)
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Two Passes ----------
string minRemoveToMakeValidTwoPass(const string& s) {
    string a;
    int bal = 0;
    for (char c : s) {                             // drop ')' that would go negative
        if (c == ')' && bal == 0) continue;
        bal += c == '(' ? 1 : c == ')' ? -1 : 0;
        a += c;
    }
    string b;
    for (int i = (int)a.size() - 1; i >= 0; i--) { // drop the last `bal` extra '('
        if (a[i] == '(' && bal > 0) { bal--; continue; }
        b += a[i];
    }
    reverse(b.begin(), b.end());
    return b;
}

// ---------- Approach 2: Index Stack ⭐ ----------
string minRemoveToMakeValid(const string& s) {
    vector<int> st;                                // indices of unmatched '('
    vector<bool> drop(s.size(), false);
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') st.push_back(i);
        else if (s[i] == ')') {
            if (st.empty()) drop[i] = true;        // nothing to match
            else st.pop_back();
        }
    }
    for (int i : st) drop[i] = true;               // leftover '(' are unmatched
    string out;
    for (int i = 0; i < (int)s.size(); i++)
        if (!drop[i]) out += s[i];
    return out;
}

// ---------- Driver ----------
int main() {
    for (string s : {"lee(t(c)o)de)", "a)b(c)d", "))((", "(a(b)", "abc"}) {
        cout << "two-pass: \"" << minRemoveToMakeValidTwoPass(s) << "\"\n";
        cout << "stack   : \"" << minRemoveToMakeValid(s) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Nested ternary maps '(' / ')' / letter to +1 / -1 / 0.
 * - Build the result with += then reverse, instead of inserting at the front.
 * - vector<bool> drop(n) marks positions to skip when rebuilding.
 */
