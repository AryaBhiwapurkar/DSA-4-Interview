/*
 * 0028. Find the Index of the First Occurrence in a String  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
 *
 * Problem: Return the index of the first occurrence of needle in
 *          haystack, or -1 if it does not occur.
 *
 * Examples:
 *   "sadbutsad", "sad"     -> 0
 *   "leetcode",  "leeto"   -> -1
 *   "abc",       "c"       -> 2
 *   "aabaaabaaac", "aabaaac" -> 4
 *
 * Approaches:
 *   1. Brute-force window  ⭐  O(n*m) time, O(1) space   <- go-to
 *   2. KMP                    O(n+m) time, O(m) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute-Force Window ⭐ ----------
int strStr(const string& haystack, const string& needle) {
    int n = haystack.size(), m = needle.size();         // int: n - m may be negative
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && haystack[i + j] == needle[j]) j++;
        if (j == m) return i;
    }
    return -1;
}

// ---------- Approach 2: KMP ----------
int strStrKMP(const string& haystack, const string& needle) {
    int n = haystack.size(), m = needle.size();
    vector<int> lps(m, 0);                               // lps[i]: longest proper prefix == suffix of needle[0..i]
    for (int i = 1, len = 0; i < m;) {
        if (needle[i] == needle[len]) lps[i++] = ++len;
        else if (len > 0) len = lps[len - 1];            // fall back, don't advance i
        else lps[i++] = 0;
    }
    for (int i = 0, j = 0; i < n;) {
        if (haystack[i] == needle[j]) {
            i++, j++;
            if (j == m) return i - m;
        } else if (j > 0) {
            j = lps[j - 1];                              // reuse the matched prefix
        } else {
            i++;
        }
    }
    return -1;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"sadbutsad", "sad"}, {"leetcode", "leeto"}, {"abc", "c"}, {"aabaaabaaac", "aabaaac"}
    };
    for (auto& [h, nd] : tests) {
        cout << "brute: " << strStr(h, nd) << "\n";
        cout << "kmp  : " << strStrKMP(h, nd) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - size() is unsigned: size() - m underflows to a huge number; copy to int first.
 * - for (int i = 1, len = 0; i < m;) declares two loop vars and leaves the step to the body.
 * - lps[i++] = ++len assigns the incremented len, then advances i.
 * - Built-in: haystack.find(needle) returns string::npos if absent.
 */
