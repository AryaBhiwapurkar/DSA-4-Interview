/*
 * 0424. Longest Repeating Character Replacement  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/longest-repeating-character-replacement/
 *
 * Problem: Uppercase string, at most k character changes; return the
 *          longest substring that can become one repeated letter.
 *
 * Examples:
 *   "ABAB", k=2       -> 4
 *   "AABABBA", k=1    -> 4
 *   "AAAA", k=0       -> 4
 *   "ABCDE", k=1      -> 2
 *
 * Approaches:
 *   1. Brute force                   O(n^2) time, O(26) space
 *   2. Per-letter window             O(26*n) time, O(1) space
 *   3. Window + max frequency  ⭐     O(n) time, O(26) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int characterReplacementBrute(const string& s, int k) {
    int n = s.size(), best = 0;
    for (int i = 0; i < n; i++) {
        array<int, 26> cnt{};
        int maxf = 0;
        for (int j = i; j < n; j++) {
            maxf = max(maxf, ++cnt[s[j] - 'A']);
            if ((j - i + 1) - maxf > k) break;           // needs more than k changes
            best = max(best, j - i + 1);
        }
    }
    return best;
}

// ---------- Approach 2: Per-Letter Window ----------
int characterReplacementPerLetter(const string& s, int k) {
    int best = 0;
    for (char c = 'A'; c <= 'Z'; c++) {
        int l = 0, others = 0;                           // chars in window that aren't c
        for (int r = 0; r < (int)s.size(); r++) {
            if (s[r] != c) others++;
            while (others > k) if (s[l++] != c) others--;
            best = max(best, r - l + 1);
        }
    }
    return best;
}

// ---------- Approach 3: Window + Max Frequency ⭐ ----------
int characterReplacement(const string& s, int k) {
    array<int, 26> cnt{};
    int l = 0, maxf = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        maxf = max(maxf, ++cnt[s[r] - 'A']);
        if ((r - l + 1) - maxf > k) cnt[s[l++] - 'A']--;  // slide, don't shrink: maxf may be stale, that's fine
        best = max(best, r - l + 1);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, int>> tests = {{"ABAB", 2}, {"AABABBA", 1}, {"AAAA", 0}, {"ABCDE", 1}};
    for (auto& [s, k] : tests) {
        cout << "brute     : " << characterReplacementBrute(s, k) << "\n";
        cout << "per-letter: " << characterReplacementPerLetter(s, k) << "\n";
        cout << "maxfreq   : " << characterReplacement(s, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - max(maxf, ++cnt[i]) increments first, then compares.
 * - `while (cond) if (...) x--;` is a one-statement loop body (keep it readable).
 * - char loop: for (char c = 'A'; c <= 'Z'; c++).
 */
