/*
 * 0014. Longest Common Prefix  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/longest-common-prefix/
 *
 * Problem: Return the longest prefix shared by all strings, or "" if none.
 *
 * Examples:
 *   ["flower","flow","flight"]  -> "fl"
 *   ["dog","racecar","car"]     -> ""
 *   ["ab","a"]                  -> "a"
 *   ["alone"]                   -> "alone"
 *
 * Approaches:
 *   1. Horizontal scan         O(S) time, O(1) extra space
 *   2. Sort, first vs last     O(S log n) time, O(1) extra space
 *   3. Vertical scan  ⭐        O(S) time, O(1) extra space   <- go-to
 *   (S = total number of characters)
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Horizontal Scan ----------
string longestCommonPrefixHorizontal(const vector<string>& strs) {
    string prefix = strs[0];
    for (size_t k = 1; k < strs.size(); k++)
        while (strs[k].compare(0, prefix.size(), prefix) != 0)   // does strs[k] start with prefix?
            prefix.pop_back();
    return prefix;
}

// ---------- Approach 2: Sort, Compare First and Last ----------
string longestCommonPrefixSorted(vector<string> strs) {
    sort(strs.begin(), strs.end());
    const string &a = strs.front(), &b = strs.back();             // most different pair after sorting
    size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) i++;
    return a.substr(0, i);
}

// ---------- Approach 3: Vertical Scan ⭐ ----------
string longestCommonPrefix(const vector<string>& strs) {
    const string& first = strs[0];
    for (size_t i = 0; i < first.size(); i++)
        for (size_t k = 1; k < strs.size(); k++)
            if (i >= strs[k].size() || strs[k][i] != first[i])
                return first.substr(0, i);
    return first;
}

// ---------- Driver ----------
int main() {
    vector<vector<string>> tests = {
        {"flower", "flow", "flight"}, {"dog", "racecar", "car"}, {"ab", "a"}, {"alone"}
    };
    for (auto& strs : tests) {
        cout << "horizontal: \"" << longestCommonPrefixHorizontal(strs) << "\"\n";
        cout << "sorted    : \"" << longestCommonPrefixSorted(strs) << "\"\n";
        cout << "vertical  : \"" << longestCommonPrefix(strs) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - s.compare(pos, len, t) == 0 tests whether s[pos..pos+len) equals t
 *   (C++20 adds s.starts_with(t)).
 * - pop_back() removes the last char of a string.
 * - substr(0, i) is the first i chars.
 * - Strings sort lexicographically with operator<.
 */
