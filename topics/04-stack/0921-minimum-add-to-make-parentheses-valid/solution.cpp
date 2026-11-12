/*
 * 0921. Minimum Add to Make Parentheses Valid  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
 *
 * Problem: Fewest '(' or ')' insertions that make the string valid.
 *
 * Examples:
 *   "())"   -> 1
 *   "((("   -> 3
 *   ")("    -> 2
 *   "()"    -> 0
 *   ")))"   -> 3
 *
 * Approaches:
 *   1. Remove "()" pairs repeatedly     O(n^2) time
 *   2. Stack                            O(n) time, O(n) space
 *   3. Two counters  ⭐                 O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Remove Pairs ----------
int minAddToMakeValidPairs(string s) {
    size_t p;
    while ((p = s.find("()")) != string::npos) s.erase(p, 2);
    return s.size();                               // everything left is unmatched
}

// ---------- Approach 2: Stack ----------
int minAddToMakeValidStack(const string& s) {
    vector<char> st;
    int unmatchedClose = 0;
    for (char c : s) {
        if (c == '(') st.push_back(c);
        else if (!st.empty()) st.pop_back();
        else unmatchedClose++;
    }
    return st.size() + unmatchedClose;
}

// ---------- Approach 3: Two Counters ⭐ ----------
int minAddToMakeValid(const string& s) {
    int open = 0, add = 0;
    for (char c : s) {
        if (c == '(') open++;
        else if (open > 0) open--;                 // matched
        else add++;                                // needs an inserted '('
    }
    return add + open;                             // leftover '(' each need a ')'
}

// ---------- Driver ----------
int main() {
    for (string s : {"())", "(((", ")(", "()", ")))"}) {
        cout << "pairs   : " << minAddToMakeValidPairs(s) << "\n";
        cout << "stack   : " << minAddToMakeValidStack(s) << "\n";
        cout << "counters: " << minAddToMakeValid(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - while ((p = s.find("()")) != npos) assigns and tests in the condition.
 * - s.erase(pos, len) deletes a substring in place (O(n)).
 * - With one bracket type, a stack of '(' is just a counter.
 */
