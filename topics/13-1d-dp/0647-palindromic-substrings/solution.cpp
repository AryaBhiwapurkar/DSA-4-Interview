/*
 * 0647. Palindromic Substrings  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/palindromic-substrings/
 *
 * Problem: Count substrings of s that are palindromes. Substrings at
 *          different positions count separately.
 *
 * Examples:
 *   "abc"   -> 3
 *   "aaa"   -> 6
 *   "abba"  -> 6
 *   "a"     -> 1
 *
 * Approaches:
 *   1. Brute force (check every substring)  O(n^3) time, O(1) space
 *   2. DP table by length                   O(n^2) time, O(n^2) space
 *   3. Expand around center  ⭐              O(n^2) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int countSubstringsBrute(const string& s) {
    int n = s.size(), count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            int l = i, r = j;
            while (l < r && s[l] == s[r]) { l++; r--; }
            if (l >= r) count++;                  // pointers met: palindrome
        }
    return count;
}

// ---------- Approach 2: DP Table by Length ----------
int countSubstringsDP(const string& s) {
    int n = s.size(), count = 0;
    vector<vector<bool>> pal(n, vector<bool>(n, false));
    for (int len = 1; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            pal[i][j] = s[i] == s[j] && (len <= 2 || pal[i + 1][j - 1]);
            count += pal[i][j];
        }
    return count;
}

// ---------- Approach 3: Expand Around Center ⭐ ----------
int countFrom(const string& s, int l, int r) {
    int c = 0;
    while (l >= 0 && r < (int)s.size() && s[l] == s[r]) { c++; l--; r++; }   // each step = one more palindrome
    return c;
}

int countSubstrings(const string& s) {
    int count = 0;
    for (int i = 0; i < (int)s.size(); i++)
        count += countFrom(s, i, i) + countFrom(s, i, i + 1);   // odd + even centers
    return count;
}

// ---------- Driver ----------
int main() {
    for (string s : {"abc", "aaa", "abba", "a"}) {
        cout << "brute : " << countSubstringsBrute(s) << "\n";
        cout << "dp    : " << countSubstringsDP(s) << "\n";
        cout << "expand: " << countSubstrings(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `count += pal[i][j];` adds a bool as 0/1.
 * - vector<vector<bool>> is bit-packed: fine for flags, but elements aren't real bool&.
 * - Count fits in int: at most n(n+1)/2 = 500,500 for n = 1000.
 */
