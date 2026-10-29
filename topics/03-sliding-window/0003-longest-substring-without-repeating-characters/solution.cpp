/*
 * 0003. Longest Substring Without Repeating Characters  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * Problem: Return the length of the longest substring with all-distinct
 *          characters.
 *
 * Examples:
 *   "abcabcbb"  -> 3
 *   "bbbbb"     -> 1
 *   "pwwkew"    -> 3
 *   ""          -> 0
 *   "abba"      -> 2
 *
 * Approaches:
 *   1. Brute force                   O(n^2) time, O(alphabet) space
 *   2. Window + set  ⭐               O(n) time, O(min(n, alphabet)) space   <- go-to
 *   3. Window + last-seen index      O(n) time, O(alphabet) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int lengthOfLongestSubstringBrute(const string& s) {
    int best = 0, n = s.size();
    for (int i = 0; i < n; i++) {
        bool seen[256] = {};
        for (int j = i; j < n && !seen[(unsigned char)s[j]]; j++) {
            seen[(unsigned char)s[j]] = true;
            best = max(best, j - i + 1);
        }
    }
    return best;
}

// ---------- Approach 2: Window + Set ⭐ ----------
int lengthOfLongestSubstring(const string& s) {
    unordered_set<char> window;
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        while (window.count(s[r])) window.erase(s[l++]);   // shrink until s[r] is no longer inside
        window.insert(s[r]);
        best = max(best, r - l + 1);                        // window is valid here
    }
    return best;
}

// ---------- Approach 3: Window + Last-Seen Index ----------
int lengthOfLongestSubstringJump(const string& s) {
    array<int, 256> last;
    last.fill(-1);
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        unsigned char c = s[r];
        l = max(l, last[c] + 1);                            // max: never move l backwards ("abba")
        last[c] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"abcabcbb", "bbbbb", "pwwkew", "", "abba"};
    for (auto& s : tests) {
        cout << "brute: " << lengthOfLongestSubstringBrute(s) << "\n";
        cout << "set  : " << lengthOfLongestSubstring(s) << "\n";
        cout << "jump : " << lengthOfLongestSubstringJump(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - window.erase(s[l++]) erases s[l], then advances l.
 * - Index arrays with (unsigned char) so chars >= 128 aren't negative.
 * - array::fill(-1) sets a sentinel for "never seen".
 */
