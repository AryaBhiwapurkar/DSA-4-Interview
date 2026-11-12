/*
 * 0316. Remove Duplicate Letters  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/remove-duplicate-letters/
 *
 * Problem: Keep each letter exactly once, preserving order, so the result is lexicographically smallest.
 *
 * Examples:
 *   "bcabc"     -> "abc"
 *   "cbacdcbc"  -> "acdb"
 *   "aabbcc"    -> "abc"
 *   "zyx"       -> "zyx"
 *   "abacb"     -> "abc"
 *
 * Approaches:
 *   1. Recursive smallest-first choice     O(26 * n) time
 *   2. Greedy stack  ⭐                    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Recursive Choice ----------
string removeDuplicateLettersRec(const string& s) {
    if (s.empty()) return "";
    array<int, 26> cnt{};
    for (char c : s) cnt[c - 'a']++;
    size_t pos = 0;                                // first index of the chosen letter
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] < s[pos]) pos = i;
        if (--cnt[s[i] - 'a'] == 0) break;         // s[i] never appears again: must choose by here
    }
    char c = s[pos];
    string rest;
    for (size_t i = pos + 1; i < s.size(); i++)
        if (s[i] != c) rest += s[i];               // drop every other copy of c
    return c + removeDuplicateLettersRec(rest);
}

// ---------- Approach 2: Greedy Stack ⭐ ----------
string removeDuplicateLetters(const string& s) {
    array<int, 26> last{};
    for (int i = 0; i < (int)s.size(); i++) last[s[i] - 'a'] = i;
    array<bool, 26> used{};
    string st;
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (used[c - 'a']) continue;               // an earlier copy is already placed
        while (!st.empty() && st.back() > c && last[st.back() - 'a'] > i) {
            used[st.back() - 'a'] = false;         // it recurs later, so it can come back
            st.pop_back();
        }
        st.push_back(c);
        used[c - 'a'] = true;
    }
    return st;
}

// ---------- Driver ----------
int main() {
    for (string s : {"bcabc", "cbacdcbc", "aabbcc", "zyx", "abacb"}) {
        cout << "recursive: \"" << removeDuplicateLettersRec(s) << "\"\n";
        cout << "stack    : \"" << removeDuplicateLetters(s) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - array<bool, 26> used{} zero-initialises to false.
 * - char + string concatenates (operator+ has a char/string overload).
 * - last[c - 'a'] = i over the whole string leaves the final index of each letter.
 */
