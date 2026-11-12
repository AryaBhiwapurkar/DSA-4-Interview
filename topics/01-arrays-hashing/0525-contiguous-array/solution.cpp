/*
 * 0525. Contiguous Array  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/contiguous-array/
 *
 * Problem: Longest contiguous subarray of a binary array with equally many 0s and 1s.
 *
 * Examples:
 *   [0,1]                -> 2
 *   [0,1,0]              -> 2
 *   [0,1,1,1,1,1,0,0,0]  -> 6
 *   [0,0,1,0,1,1]        -> 6
 *   [0,0,0]              -> 0
 *
 * Approaches:
 *   1. All subarrays with running counts   O(n^2) time, O(1) space
 *   2. Balance + first-index map  ⭐       O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Subarrays ----------
int findMaxLengthBrute(const vector<int>& nums) {
    int n = nums.size(), best = 0;
    for (int i = 0; i < n; i++) {
        int bal = 0;
        for (int j = i; j < n; j++) {
            bal += nums[j] ? 1 : -1;
            if (bal == 0) best = max(best, j - i + 1);
        }
    }
    return best;
}

// ---------- Approach 2: Balance + First-Index Map ⭐ ----------
int findMaxLength(const vector<int>& nums) {
    unordered_map<int, int> first{{0, -1}};        // balance 0 before index 0
    int bal = 0, best = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        bal += nums[i] ? 1 : -1;                   // a 0 counts as -1
        auto it = first.find(bal);
        if (it != first.end()) best = max(best, i - it->second);
        else first[bal] = i;                       // keep only the earliest index
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{0, 1}, {0, 1, 0}, {0, 1, 1, 1, 1, 1, 0, 0, 0}, {0, 0, 1, 0, 1, 1}, {0, 0, 0}};
    for (auto& t : tests) {
        cout << "brute  : " << findMaxLengthBrute(t) << "\n";
        cout << "balance: " << findMaxLength(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - x ? 1 : -1 maps the binary value to +1 / -1 inline.
 * - find + else-insert keeps the first occurrence (m.emplace(k, v) would also skip existing keys).
 * - Array alternative: vector<int> first(2 * n + 1, -2) indexed by bal + n.
 */
