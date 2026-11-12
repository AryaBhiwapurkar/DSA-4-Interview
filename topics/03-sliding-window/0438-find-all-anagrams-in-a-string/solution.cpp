/*
 * 0438. Find All Anagrams in a String  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/find-all-anagrams-in-a-string/
 *
 * Problem: Start indices of every substring of s that is an anagram of p.
 *
 * Examples:
 *   s = "cbaebabacd", p = "abc"  -> [0,6]
 *   s = "abab",       p = "ab"   -> [0,1,2]
 *   s = "a",          p = "ab"   -> []
 *   s = "aaab",       p = "aab"  -> [1]
 *
 * Approaches:
 *   1. Count each window from scratch     O(n * |p|) time
 *   2. Sliding count arrays               O(26 * n) time, O(1) space
 *   3. Sliding window + matches  ⭐       O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Count Each Window ----------
vector<int> findAnagramsBrute(const string& s, const string& p) {
    vector<int> out;
    array<int, 26> need{};
    for (char c : p) need[c - 'a']++;
    for (int i = 0; i + (int)p.size() <= (int)s.size(); i++) {
        array<int, 26> have{};
        for (int j = i; j < i + (int)p.size(); j++) have[s[j] - 'a']++;
        if (have == need) out.push_back(i);
    }
    return out;
}

// ---------- Approach 2: Sliding Count Arrays ----------
vector<int> findAnagramsArrays(const string& s, const string& p) {
    int m = p.size();
    vector<int> out;
    array<int, 26> need{}, have{};
    for (char c : p) need[c - 'a']++;
    for (int r = 0; r < (int)s.size(); r++) {
        have[s[r] - 'a']++;
        if (r >= m) have[s[r - m] - 'a']--;        // drop the char leaving the window
        if (r >= m - 1 && have == need) out.push_back(r - m + 1);
    }
    return out;
}

// ---------- Approach 3: Matches Counter ⭐ ----------
vector<int> findAnagrams(const string& s, const string& p) {
    int m = p.size();
    vector<int> out;
    array<int, 26> diff{};                         // window count - p count, per letter
    for (char c : p) diff[c - 'a']--;
    int matches = count(diff.begin(), diff.end(), 0);   // letters whose counts agree
    auto bump = [&](int k, int d) {
        if (diff[k] == 0) matches--;
        diff[k] += d;
        if (diff[k] == 0) matches++;
    };
    for (int r = 0; r < (int)s.size(); r++) {
        bump(s[r] - 'a', +1);
        if (r >= m) bump(s[r - m] - 'a', -1);
        if (r >= m - 1 && matches == 26) out.push_back(r - m + 1);
    }
    return out;
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<pair<string, string>> tests = {{"cbaebabacd", "abc"}, {"abab", "ab"}, {"a", "ab"}, {"aaab", "aab"}};
    for (auto& [s, p] : tests) {
        cout << "brute  : "; print(findAnagramsBrute(s, p));
        cout << "arrays : "; print(findAnagramsArrays(s, p));
        cout << "matches: "; print(findAnagrams(s, p));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::array supports == for whole-array comparison.
 * - A lambda capturing by reference ([&]) can update locals like matches.
 * - std::count(first, last, 0) counts zero entries.
 */
