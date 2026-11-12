/*
 * 0340. Longest Substring with At Most K Distinct Characters  |  Medium  |  Sliding Window  |  LC Premium
 * Link: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
 *
 * Problem: Length of the longest substring with at most k distinct characters.
 *
 * Examples:
 *   s = "eceba",   k = 2  -> 3
 *   s = "aa",      k = 1  -> 2
 *   s = "abc",     k = 0  -> 0
 *   s = "abaccc",  k = 2  -> 4
 *   s = "a@a@b",   k = 2  -> 4    (non-letters allowed)
 *
 * Approaches:
 *   1. Every start, extend              O(n^2) time, O(k) space
 *   2. Shrinking window + map  ⭐       O(n) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Every Start ----------
int lengthOfLongestSubstringKDistinctBrute(const string& s, int k) {
    int n = s.size(), best = 0;
    for (int l = 0; l < n; l++) {
        unordered_set<char> seen;
        for (int r = l; r < n; r++) {
            seen.insert(s[r]);
            if ((int)seen.size() > k) break;
            best = max(best, r - l + 1);
        }
    }
    return best;
}

// ---------- Approach 2: Shrinking Window ⭐ ----------
int lengthOfLongestSubstringKDistinct(const string& s, int k) {
    unordered_map<char, int> cnt;
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        cnt[s[r]]++;
        while ((int)cnt.size() > k) {
            if (--cnt[s[l]] == 0) cnt.erase(s[l]);  // keep size == distinct count
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, int>> tests = {{"eceba", 2}, {"aa", 1}, {"abc", 0}, {"abaccc", 2}, {"a@a@b", 2}};
    for (auto& [s, k] : tests) {
        cout << "brute : " << lengthOfLongestSubstringKDistinctBrute(s, k) << "\n";
        cout << "window: " << lengthOfLongestSubstringKDistinct(s, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - if (--cnt[c] == 0) cnt.erase(c); decrements, then removes empty keys.
 * - unordered_map::size() is the number of keys (distinct chars here).
 * - Cast size() to int before comparing with a signed k.
 */
