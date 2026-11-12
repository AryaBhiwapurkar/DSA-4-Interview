/*
 * 0214. Shortest Palindrome  |  Hard  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/shortest-palindrome/
 *
 * Problem: Add characters only in front of s to make the shortest possible palindrome.
 *
 * Examples:
 *   "aacecaaa"  -> "aaacecaaa"
 *   "abcd"      -> "dcbabcd"
 *   ""          -> ""
 *   "aba"       -> "aba"
 *   "aaaab"     -> "baaaab"
 *
 * Approaches:
 *   1. Check prefixes from longest           O(n^2) time, O(n) space
 *   2. KMP on s + '#' + reverse(s)  ⭐       O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Check Prefixes ----------
string shortestPalindromeBrute(const string& s) {
    int n = s.size();
    auto isPal = [&](int len) {
        for (int i = 0, j = len - 1; i < j; i++, j--)
            if (s[i] != s[j]) return false;
        return true;
    };
    int k = n;
    while (k > 0 && !isPal(k)) k--;                // longest palindromic prefix
    string add = s.substr(k);
    reverse(add.begin(), add.end());
    return add + s;
}

// ---------- Approach 2: KMP ⭐ ----------
string shortestPalindrome(const string& s) {
    string rev(s.rbegin(), s.rend());
    string t = s + "#" + rev;                      // '#' stops matches crossing the middle
    vector<int> lps(t.size(), 0);
    for (int i = 1, k = 0; i < (int)t.size(); i++) {
        while (k > 0 && t[i] != t[k]) k = lps[k - 1];
        if (t[i] == t[k]) k++;
        lps[i] = k;
    }
    int k = lps.back();                            // longest palindromic prefix length
    return rev.substr(0, s.size() - k) + s;        // rev's first n-k chars = reverse(s[k:])
}

// ---------- Driver ----------
int main() {
    for (string s : {"aacecaaa", "abcd", "", "aba", "aaaab"}) {
        cout << "brute: \"" << shortestPalindromeBrute(s) << "\"\n";
        cout << "kmp  : \"" << shortestPalindrome(s) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - string rev(s.rbegin(), s.rend()) builds the reversed string.
 * - rev.substr(0, n - k) is the reverse of s.substr(k).
 * - lps.back() reads the last element (t is never empty thanks to '#').
 */
