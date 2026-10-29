/*
 * 0242. Valid Anagram  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/valid-anagram/
 *
 * Problem: Return true if t uses exactly the same letters as s with
 *          the same counts (t is a rearrangement of s).
 *
 * Examples:
 *   s="anagram", t="nagaram"  -> true
 *   s="rat",     t="car"      -> false
 *   s="ab",      t="a"        -> false
 *
 * Approaches:
 *   1. Sort both          O(n log n) time, O(n) space
 *   2. Count array  ⭐     O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort Both ----------
bool isAnagramSorted(string s, string t) {   // by value: we sort copies
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}

// ---------- Approach 2: Count Array ⭐ ----------
bool isAnagram(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    array<int, 26> cnt{};                     // {} zero-initializes
    for (size_t i = 0; i < s.size(); i++) {
        cnt[s[i] - 'a']++;
        cnt[t[i] - 'a']--;
    }
    for (int c : cnt)
        if (c != 0) return false;
    return true;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {{"anagram", "nagaram"}, {"rat", "car"}, {"ab", "a"}};
    cout << boolalpha;
    for (auto& [s, t] : tests) {
        cout << "sorted: " << isAnagramSorted(s, t) << "\n";
        cout << "count : " << isAnagram(s, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - array<int, 26> cnt{} zero-initializes; a plain `int cnt[26];` inside a
 *   function holds garbage.
 * - c - 'a' maps 'a'..'z' to 0..25.
 * - std::string compares with == by content.
 * - sort works directly on a string (it's a container of chars).
 */
