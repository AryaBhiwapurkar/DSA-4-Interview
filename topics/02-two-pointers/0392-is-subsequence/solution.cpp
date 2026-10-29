/*
 * 0392. Is Subsequence  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/is-subsequence/
 *
 * Problem: Return true if s can be formed by deleting some characters of t
 *          without reordering the rest.
 *
 * Examples:
 *   s="abc", t="ahbgdc"  -> true
 *   s="axc", t="ahbgdc"  -> false
 *   s="",    t="abc"     -> true
 *   s="aa",  t="a"       -> false
 *
 * Approaches:
 *   1. Two pointers  ⭐                 O(|t|) time, O(1) space   <- go-to
 *   2. Index t + binary search         O(|s| log |t|) per query, O(|t|) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Two Pointers ⭐ ----------
bool isSubsequence(const string& s, const string& t) {
    size_t i = 0;
    for (size_t j = 0; j < t.size() && i < s.size(); j++)
        if (t[j] == s[i]) i++;                                 // greedy: match as early as possible
    return i == s.size();
}

// ---------- Approach 2: Index t + Binary Search ----------
bool isSubsequenceIndexed(const string& s, const string& t) {
    array<vector<int>, 26> pos;                                 // pos[c] = sorted indices of c in t
    for (int j = 0; j < (int)t.size(); j++) pos[t[j] - 'a'].push_back(j);
    int prev = -1;
    for (char c : s) {
        auto& p = pos[c - 'a'];
        auto it = upper_bound(p.begin(), p.end(), prev);        // first index strictly after prev
        if (it == p.end()) return false;
        prev = *it;
    }
    return true;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {{"abc", "ahbgdc"}, {"axc", "ahbgdc"}, {"", "abc"}, {"aa", "a"}};
    cout << boolalpha;
    for (auto& [s, t] : tests) {
        cout << "pointers: " << isSubsequence(s, t) << "\n";
        cout << "indexed : " << isSubsequenceIndexed(s, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - upper_bound returns the first element > value; lower_bound the first >= value.
 * - array<vector<int>, 26> holds 26 empty vectors.
 * - auto& p binds a reference, avoiding a vector copy.
 */
