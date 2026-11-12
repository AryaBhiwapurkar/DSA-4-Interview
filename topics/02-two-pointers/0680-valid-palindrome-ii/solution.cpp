/*
 * 0680. Valid Palindrome II  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/valid-palindrome-ii/
 *
 * Problem: Can s become a palindrome after deleting at most one character?
 *
 * Examples:
 *   "aba"    -> true
 *   "abca"   -> true
 *   "abc"    -> false
 *   "deeee"  -> true    (only skipping the left works)
 *   "eeeed"  -> true    (only skipping the right works)
 *   "abcda"  -> false
 *
 * Approaches:
 *   1. Try every deletion               O(n^2) time, O(n) space
 *   2. Two pointers + one branch  ⭐    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

bool isPal(const string& s, int lo, int hi) {
    while (lo < hi)
        if (s[lo++] != s[hi--]) return false;
    return true;
}

// ---------- Approach 1: Try Every Deletion ----------
bool validPalindromeBrute(const string& s) {
    if (isPal(s, 0, s.size() - 1)) return true;
    for (size_t i = 0; i < s.size(); i++) {
        string t = s.substr(0, i) + s.substr(i + 1);
        if (isPal(t, 0, (int)t.size() - 1)) return true;
    }
    return false;
}

// ---------- Approach 2: Two Pointers + One Branch ⭐ ----------
bool validPalindrome(const string& s) {
    int lo = 0, hi = s.size() - 1;
    while (lo < hi) {
        if (s[lo] != s[hi])                        // one of these two must be the deleted char
            return isPal(s, lo + 1, hi) || isPal(s, lo, hi - 1);
        lo++, hi--;
    }
    return true;
}

// ---------- Driver ----------
int main() {
    cout << boolalpha;
    for (string s : {"aba", "abca", "abc", "deeee", "eeeed", "abcda"}) {
        cout << "brute   : " << validPalindromeBrute(s) << "\n";
        cout << "pointers: " << validPalindrome(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - s[lo++] != s[hi--] compares, then moves both pointers.
 * - Pass indices into a helper instead of building substrings: O(1) extra space.
 * - || short-circuits: the second check only runs if the first fails.
 */
