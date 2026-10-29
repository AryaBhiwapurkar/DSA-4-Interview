/*
 * 0058. Length of Last Word  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/length-of-last-word/
 *
 * Problem: Return the length of the last word in a string of words and
 *          spaces (a word is a maximal run of non-space characters).
 *
 * Examples:
 *   "Hello World"                   -> 5
 *   "   fly me   to   the moon  "   -> 4
 *   "luffy is still joyboy"         -> 6
 *   "a"                             -> 1
 *
 * Approaches:
 *   1. Split, take last   O(n) time, O(n) space
 *   2. Reverse scan  ⭐    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Split, Take Last ----------
int lengthOfLastWordSplit(const string& s) {
    stringstream ss(s);
    string w, last;
    while (ss >> w) last = w;
    return last.size();
}

// ---------- Approach 2: Reverse Scan ⭐ ----------
int lengthOfLastWord(const string& s) {
    int i = (int)s.size() - 1;                 // int, not size_t: it must be able to reach -1
    while (i >= 0 && s[i] == ' ') i--;         // skip trailing spaces
    int len = 0;
    while (i >= 0 && s[i] != ' ') {
        len++;
        i--;
    }
    return len;
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"Hello World", "   fly me   to   the moon  ", "luffy is still joyboy", "a"};
    for (auto& s : tests) {
        cout << "split: " << lengthOfLastWordSplit(s) << "\n";
        cout << "scan : " << lengthOfLastWord(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Counting down with size_t wraps to a huge number instead of -1; use int.
 * - stringstream >> word skips any amount of whitespace.
 * - Implicit size_t -> int on return is fine for small sizes.
 */
