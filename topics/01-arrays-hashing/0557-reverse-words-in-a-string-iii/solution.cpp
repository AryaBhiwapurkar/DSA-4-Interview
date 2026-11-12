/*
 * 0557. Reverse Words in a String III  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/reverse-words-in-a-string-iii/
 *
 * Problem: Reverse the characters of each word, keeping word order and single spaces.
 *
 * Examples:
 *   "Let's take LeetCode contest"  -> "s'teL ekat edoCteeL tsetnoc"
 *   "Mr Ding"                      -> "rM gniD"
 *   "a"                            -> "a"
 *   "ab c de"                      -> "ba c ed"
 *
 * Approaches:
 *   1. Split, reverse, join               O(n) time, O(n) space
 *   2. In-place per-word reversal  ⭐     O(n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Split, Reverse, Join ----------
string reverseWordsSplit(const string& s) {
    stringstream ss(s);
    string w, out;
    while (ss >> w) {
        reverse(w.begin(), w.end());
        out += (out.empty() ? "" : " ") + w;
    }
    return out;
}

// ---------- Approach 2: In-place Per-word ⭐ ----------
string reverseWords(string s) {
    int n = s.size(), start = 0;
    for (int i = 0; i <= n; i++)
        if (i == n || s[i] == ' ') {               // i == n catches the last word
            reverse(s.begin() + start, s.begin() + i);
            start = i + 1;
        }
    return s;
}

// ---------- Driver ----------
int main() {
    for (string s : {"Let's take LeetCode contest", "Mr Ding", "a", "ab c de"}) {
        cout << "split  : \"" << reverseWordsSplit(s) << "\"\n";
        cout << "inplace: \"" << reverseWords(s) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - stringstream >> w reads whitespace-separated words.
 * - reverse(s.begin() + l, s.begin() + r) reverses the half-open range [l, r).
 * - Loop to i <= n and test i == n first, so s[n] is never read.
 */
