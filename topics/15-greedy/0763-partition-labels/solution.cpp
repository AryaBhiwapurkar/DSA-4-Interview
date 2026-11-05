/*
 * 0763. Partition Labels  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/partition-labels/
 *
 * Problem: Cut s into as many pieces as possible so that each letter appears
 *          in only one piece. Return the piece sizes.
 *
 * Examples:
 *   "ababcbacadefegdehijhklij"   -> [9,7,8]
 *   "eccbbbbdec"                 -> [10]
 *   "a"                          -> [1]
 *   "abc"                        -> [1,1,1]
 *   "abac"                       -> [3,1]
 *
 * Approaches:
 *   1. Merge letter intervals [first, last]       O(n) time, O(1) space (26 letters)
 *   2. Last occurrence + running window end  ⭐    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Merge Intervals ----------
vector<int> partitionLabelsIntervals(const string& s) {
    vector<int> first(26, -1), last(26, -1);
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        if (first[c] == -1) first[c] = i;
        last[c] = i;
    }
    vector<pair<int, int>> spans;                  // one interval per letter present
    for (int c = 0; c < 26; c++)
        if (first[c] != -1) spans.push_back({first[c], last[c]});
    sort(spans.begin(), spans.end());
    vector<int> sizes;
    int start = spans[0].first, end = spans[0].second;
    for (size_t k = 1; k < spans.size(); k++) {
        auto [a, b] = spans[k];
        if (a > end) { sizes.push_back(end - start + 1); start = a; end = b; }   // gap: close piece
        else end = max(end, b);
    }
    sizes.push_back(end - start + 1);
    return sizes;
}

// ---------- Approach 2: Last Occurrence ⭐ ----------
vector<int> partitionLabels(const string& s) {
    int last[26];
    for (int i = 0; i < (int)s.size(); i++) last[s[i] - 'a'] = i;
    vector<int> sizes;
    int start = 0, end = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        end = max(end, last[s[i] - 'a']);          // piece must reach this letter's last copy
        if (i == end) {                            // everything inside closes here
            sizes.push_back(end - start + 1);
            start = i + 1;
        }
    }
    return sizes;
}

void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << v[i];
    cout << "]\n";
}

// ---------- Driver ----------
int main() {
    for (string s : {"ababcbacadefegdehijhklij", "eccbbbbdec", "a", "abc", "abac"}) {
        cout << "intervals: "; print(partitionLabelsIntervals(s));
        cout << "last     : "; print(partitionLabels(s));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - int last[26] indexed by s[i] - 'a' replaces a hashmap for lowercase letters.
 * - Only letters present in s are read from `last`, so it needs no initialisation.
 * - sort on vector<pair> orders by first, then second.
 */
