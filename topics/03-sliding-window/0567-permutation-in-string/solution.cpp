/*
 * 0567. Permutation in String  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/permutation-in-string/
 *
 * Problem: Return true if some permutation of s1 is a substring of s2.
 *
 * Examples:
 *   s1="ab",  s2="eidbaooo"  -> true
 *   s1="ab",  s2="eidboaoo"  -> false
 *   s1="abc", s2="ab"        -> false
 *   s1="adc", s2="dcda"      -> true
 *
 * Approaches:
 *   1. Sort every window            O(n * m log m) time, O(m) space
 *   2. Fixed window + counts  ⭐     O(26 * n) time, O(1) space   <- go-to
 *   3. Window + matches counter     O(n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort Every Window ----------
bool checkInclusionSort(string s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    sort(s1.begin(), s1.end());
    for (int i = 0; i + m <= n; i++) {
        string w = s2.substr(i, m);
        sort(w.begin(), w.end());
        if (w == s1) return true;
    }
    return false;
}

// ---------- Approach 2: Fixed Window + Count Arrays ⭐ ----------
bool checkInclusion(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    if (m > n) return false;
    array<int, 26> need{}, win{};
    for (int i = 0; i < m; i++) need[s1[i] - 'a']++, win[s2[i] - 'a']++;
    if (need == win) return true;                    // first window
    for (int r = m; r < n; r++) {
        win[s2[r] - 'a']++;                          // char entering
        win[s2[r - m] - 'a']--;                      // char leaving
        if (need == win) return true;
    }
    return false;
}

// ---------- Approach 3: Window + Matches Counter ----------
bool checkInclusionMatches(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    if (m > n) return false;
    array<int, 26> need{}, win{};
    for (int i = 0; i < m; i++) need[s1[i] - 'a']++, win[s2[i] - 'a']++;
    int matches = 0;                                 // letters whose counts agree
    for (int c = 0; c < 26; c++) matches += need[c] == win[c];
    auto update = [&](int c, int delta) {
        if (win[c] == need[c]) matches--;            // was equal, about to change
        win[c] += delta;
        if (win[c] == need[c]) matches++;            // equal after the change
    };
    for (int r = m; r < n; r++) {
        if (matches == 26) return true;
        update(s2[r] - 'a', +1);
        update(s2[r - m] - 'a', -1);
    }
    return matches == 26;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {{"ab", "eidbaooo"}, {"ab", "eidboaoo"}, {"abc", "ab"}, {"adc", "dcda"}};
    cout << boolalpha;
    for (auto& [s1, s2] : tests) {
        cout << "sort   : " << checkInclusionSort(s1, s2) << "\n";
        cout << "counts : " << checkInclusion(s1, s2) << "\n";
        cout << "matches: " << checkInclusionMatches(s1, s2) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::array supports == for element-wise comparison.
 * - A lambda capturing by reference [&] can update local variables.
 * - bool adds as 0/1: matches += (a == b).
 */
