/*
 * 0274. H-Index  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/h-index/
 *
 * Problem: Return the largest h such that at least h papers have at least
 *          h citations each.
 *
 * Examples:
 *   [3,0,6,1,5]  -> 3
 *   [1,3,1]      -> 1
 *   [0,0]        -> 0
 *   [100]        -> 1
 *
 * Approaches:
 *   1. Try every h          O(n^2) time, O(1) space
 *   2. Sort descending      O(n log n) time, O(1) extra space
 *   3. Counting buckets  ⭐  O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Try Every h ----------
int hIndexBrute(const vector<int>& c) {
    int n = c.size();
    for (int h = n; h >= 0; h--) {
        int cnt = count_if(c.begin(), c.end(), [h](int x) { return x >= h; });
        if (cnt >= h) return h;
    }
    return 0;
}

// ---------- Approach 2: Sort Descending ----------
int hIndexSorted(vector<int> c) {
    sort(c.rbegin(), c.rend());
    int h = 0;
    while (h < (int)c.size() && c[h] >= h + 1) h++;          // (h+1)-th best paper has >= h+1 citations
    return h;
}

// ---------- Approach 3: Counting Buckets ⭐ ----------
int hIndex(const vector<int>& c) {
    int n = c.size();
    vector<int> bucket(n + 1, 0);
    for (int x : c) bucket[min(x, n)]++;                       // h <= n, so cap at n
    int total = 0;                                             // papers with >= h citations
    for (int h = n; h >= 0; h--) {
        total += bucket[h];
        if (total >= h) return h;
    }
    return 0;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{3, 0, 6, 1, 5}, {1, 3, 1}, {0, 0}, {100}};
    for (auto& c : tests) {
        cout << "brute : " << hIndexBrute(c) << "\n";
        cout << "sorted: " << hIndexSorted(c) << "\n";
        cout << "bucket: " << hIndex(c) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - sort(v.rbegin(), v.rend()) sorts descending via reverse iterators.
 * - count_if(begin, end, pred) counts matching elements.
 * - Lambda capture [h] copies h into the lambda.
 */
