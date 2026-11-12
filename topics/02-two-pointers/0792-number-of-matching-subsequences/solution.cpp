/*
 * 0792. Number of Matching Subsequences  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/number-of-matching-subsequences/
 *
 * Problem: Count the words that are subsequences of s.
 *
 * Examples:
 *   s = "abcde",      words = ["a","bb","acd","ace"]                          -> 3
 *   s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]      -> 2
 *   s = "aaa",        words = ["a","aa","aaa","aaaa","a"]                     -> 4
 *
 * Approaches:
 *   1. Two pointers per word           O(W * |s|) time, O(1) space
 *   2. Binary search on positions      O(|s| + sum L * log|s|) time, O(|s|) space
 *   3. Waiting buckets  ⭐             O(|s| + sum L) time, O(W) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Two Pointers per Word ----------
int numMatchingSubseqTwoPtr(const string& s, const vector<string>& words) {
    int count = 0;
    for (auto& w : words) {
        size_t j = 0;
        for (size_t i = 0; i < s.size() && j < w.size(); i++)
            if (s[i] == w[j]) j++;
        count += j == w.size();
    }
    return count;
}

// ---------- Approach 2: Binary Search on Positions ----------
int numMatchingSubseqBinary(const string& s, const vector<string>& words) {
    vector<vector<int>> pos(26);
    for (int i = 0; i < (int)s.size(); i++) pos[s[i] - 'a'].push_back(i);
    int count = 0;
    for (auto& w : words) {
        int cur = -1;
        bool ok = true;
        for (char c : w) {
            auto& p = pos[c - 'a'];
            auto it = upper_bound(p.begin(), p.end(), cur);   // strictly after cur
            if (it == p.end()) { ok = false; break; }
            cur = *it;
        }
        count += ok;
    }
    return count;
}

// ---------- Approach 3: Waiting Buckets ⭐ ----------
int numMatchingSubseq(const string& s, const vector<string>& words) {
    vector<vector<pair<int, int>>> waiting(26);    // (word index, next position in word)
    for (int i = 0; i < (int)words.size(); i++) waiting[words[i][0] - 'a'].push_back({i, 0});
    int count = 0;
    for (char c : s) {
        auto bucket = move(waiting[c - 'a']);      // take it out: re-adds go to a fresh bucket
        waiting[c - 'a'].clear();
        for (auto [wi, j] : bucket) {
            if (++j == (int)words[wi].size()) count++;
            else waiting[words[wi][j] - 'a'].push_back({wi, j});
        }
    }
    return count;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, vector<string>>> tests = {
        {"abcde", {"a", "bb", "acd", "ace"}},
        {"dsahjpjauf", {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"}},
        {"aaa", {"a", "aa", "aaa", "aaaa", "a"}}};
    for (auto& [s, words] : tests) {
        cout << "two ptr: " << numMatchingSubseqTwoPtr(s, words) << "\n";
        cout << "binary : " << numMatchingSubseqBinary(s, words) << "\n";
        cout << "buckets: " << numMatchingSubseq(s, words) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - auto b = move(v[k]); then v[k].clear(); empties the slot (a moved-from vector is valid but unspecified).
 * - upper_bound returns the first element > value: the next unused position.
 * - count += boolean adds 1 for true.
 */
