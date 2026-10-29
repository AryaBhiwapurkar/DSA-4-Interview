/*
 * 0383. Ransom Note  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/ransom-note/
 *
 * Problem: Return true if ransomNote can be built from the letters of
 *          magazine, using each magazine letter at most once.
 *
 * Examples:
 *   note="a",  mag="b"    -> false
 *   note="aa", mag="ab"   -> false
 *   note="aa", mag="aab"  -> true
 *
 * Approaches:
 *   1. Brute force (mark used)   O(m*n) time, O(n) space
 *   2. Count array  ⭐            O(m+n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
bool canConstructBrute(const string& note, string mag) {   // copy: we overwrite used letters
    for (char c : note) {
        size_t pos = mag.find(c);
        if (pos == string::npos) return false;
        mag[pos] = '#';                                    // mark as used
    }
    return true;
}

// ---------- Approach 2: Count Array ⭐ ----------
bool canConstruct(const string& note, const string& mag) {
    array<int, 26> cnt{};
    for (char c : mag) cnt[c - 'a']++;
    for (char c : note)
        if (--cnt[c - 'a'] < 0) return false;              // needed more than available
    return true;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {{"a", "b"}, {"aa", "ab"}, {"aa", "aab"}};
    cout << boolalpha;
    for (auto& [note, mag] : tests) {
        cout << "brute: " << canConstructBrute(note, mag) << "\n";
        cout << "count: " << canConstruct(note, mag) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - string::find returns string::npos when not found.
 * - --x < 0 decrements first, then compares (pre-decrement).
 * - array<int, 26> cnt{} is zero-initialized.
 */
