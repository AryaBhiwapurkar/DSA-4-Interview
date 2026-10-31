/*
 * 0005. Longest Palindromic Substring  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/longest-palindromic-substring/
 *
 * Problem: Return the longest contiguous substring of s that reads the same
 *          both ways.
 *
 * Examples:
 *   "babad"             -> "bab" ("aba" also valid; all approaches keep the first)
 *   "cbbd"              -> "bb"
 *   "a"                 -> "a"
 *   "ac"                -> "a"
 *   "forgeeksskeegfor"  -> "geeksskeeg"
 *
 * Approaches:
 *   1. Brute force (check every substring)  O(n^3) time, O(1) space
 *   2. DP table by length                   O(n^2) time, O(n^2) space
 *   3. Expand around center  ⭐              O(n^2) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
bool isPal(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}

string longestPalindromeBrute(const string& s) {
    int n = s.size(), start = 0, best = 1;
    for (int i = 0; i < n; i++)
        for (int j = i + best; j < n; j++)       // only lengths that would beat best
            if (isPal(s, i, j)) { start = i; best = j - i + 1; }
    return s.substr(start, best);
}

// ---------- Approach 2: DP Table by Length ----------
string longestPalindromeDP(const string& s) {
    int n = s.size(), start = 0, best = 1;
    vector<vector<bool>> pal(n, vector<bool>(n, false));   // pal[i][j]: s[i..j] is a palindrome
    for (int len = 1; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            pal[i][j] = s[i] == s[j] && (len <= 2 || pal[i + 1][j - 1]);   // inner part already known
            if (pal[i][j] && len > best) { start = i; best = len; }
        }
    return s.substr(start, best);
}

// ---------- Approach 3: Expand Around Center ⭐ ----------
int expand(const string& s, int l, int r) {
    while (l >= 0 && r < (int)s.size() && s[l] == s[r]) { l--; r++; }
    return r - l - 1;                             // length of s[l+1..r-1]
}

string longestPalindrome(const string& s) {
    int start = 0, best = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int len = max(expand(s, i, i), expand(s, i, i + 1));   // odd and even centers
        if (len > best) { best = len; start = i - (len - 1) / 2; }
    }
    return s.substr(start, best);
}

// ---------- Driver ----------
int main() {
    for (string s : {"babad", "cbbd", "a", "ac", "forgeeksskeegfor"}) {
        cout << "brute : \"" << longestPalindromeBrute(s) << "\"\n";
        cout << "dp    : \"" << longestPalindromeDP(s) << "\"\n";
        cout << "expand: \"" << longestPalindrome(s) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - s.substr(pos, len) takes a length, not an end index.
 * - `s[l++] != s[r--]` compares then moves both pointers.
 * - Cast s.size() to int before comparing with a possibly negative index.
 * - start = i - (len - 1) / 2 works for both odd and even lengths.
 */
