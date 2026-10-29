/*
 * 0049. Group Anagrams  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/group-anagrams/
 *
 * Problem: Group the strings that are anagrams of each other.
 *          Any order of groups / words is accepted.
 *
 * Examples (printed with groups sorted for stable output):
 *   ["eat","tea","tan","ate","nat","bat"] -> [["ate","eat","tea"],["bat"],["nat","tan"]]
 *   [""]                                  -> [[""]]
 *   ["a"]                                 -> [["a"]]
 *
 * Approaches:
 *   1. Pairwise compare        O(n^2 * k) time, O(n) space
 *   2. Sorted-string key  ⭐    O(n * k log k) time, O(n * k) space   <- go-to
 *   3. Letter-count key        O(n * k) time, O(n * k) space
 */

#include <bits/stdc++.h>
using namespace std;

bool sameLetters(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    array<int, 26> cnt{};
    for (size_t i = 0; i < a.size(); i++) cnt[a[i] - 'a']++, cnt[b[i] - 'a']--;
    for (int c : cnt) if (c) return false;
    return true;
}

// ---------- Approach 1: Pairwise Compare ----------
vector<vector<string>> groupAnagramsBrute(const vector<string>& strs) {
    vector<vector<string>> res;
    vector<bool> used(strs.size(), false);
    for (size_t i = 0; i < strs.size(); i++) {
        if (used[i]) continue;
        res.push_back({strs[i]});
        for (size_t j = i + 1; j < strs.size(); j++)
            if (!used[j] && sameLetters(strs[i], strs[j])) {
                used[j] = true;
                res.back().push_back(strs[j]);
            }
    }
    return res;
}

// ---------- Approach 2: Sorted-String Key ⭐ ----------
vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());        // all anagrams share this key
        groups[key].push_back(s);            // [] creates the empty vector on first use (wanted here)
    }
    vector<vector<string>> res;
    for (auto& [key, words] : groups) res.push_back(move(words));
    return res;
}

// ---------- Approach 3: Letter-Count Key ----------
vector<vector<string>> groupAnagramsCount(const vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (const string& s : strs) {
        array<int, 26> cnt{};
        for (char c : s) cnt[c - 'a']++;
        string key;
        for (int c : cnt) key += to_string(c) + '#';   // '#' keeps [1,11] and [11,1] distinct
        groups[key].push_back(s);
    }
    vector<vector<string>> res;
    for (auto& [key, words] : groups) res.push_back(move(words));
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<string>> g) {
    for (auto& grp : g) sort(grp.begin(), grp.end());   // normalize: order is unspecified
    sort(g.begin(), g.end());
    cout << label << ": [";
    for (size_t i = 0; i < g.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < g[i].size(); j++) cout << (j ? "," : "") << "\"" << g[i][j] << "\"";
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<string>> tests = {{"eat", "tea", "tan", "ate", "nat", "bat"}, {""}, {"a"}};
    for (auto& strs : tests) {
        print("brute ", groupAnagramsBrute(strs));
        print("sorted", groupAnagrams(strs));
        print("count ", groupAnagramsCount(strs));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - map[key].push_back(x) default-constructs an empty vector on first access.
 * - move(words) transfers the vector instead of copying it.
 * - unordered_map can't hash array<int,26> out of the box; build a string key.
 * - vector<vector<string>> sorts lexicographically with sort().
 */
