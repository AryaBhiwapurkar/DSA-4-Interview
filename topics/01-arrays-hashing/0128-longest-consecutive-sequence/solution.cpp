/*
 * 0128. Longest Consecutive Sequence  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/longest-consecutive-sequence/
 *
 * Problem: Return the length of the longest run of consecutive integers
 *          that can be formed from the array's values. O(n) required.
 *
 * Examples:
 *   [100,4,200,1,3,2]        -> 4
 *   [0,3,7,2,5,8,4,6,0,1]    -> 9
 *   [1,0,1,2]                -> 3
 *   []                       -> 0
 *
 * Approaches:
 *   1. Sort + scan                 O(n log n) time, O(1) extra space
 *   2. Hash set, start-of-run  ⭐   O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort + Scan ----------
int longestConsecutiveSorted(vector<int> nums) {
    if (nums.empty()) return 0;
    sort(nums.begin(), nums.end());
    int best = 1, cur = 1;
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) continue;            // duplicate: neither breaks nor extends
        if (nums[i] == nums[i - 1] + 1) cur++;
        else cur = 1;
        best = max(best, cur);
    }
    return best;
}

// ---------- Approach 2: Hash Set, Start-of-Run ⭐ ----------
int longestConsecutive(const vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int best = 0;
    for (int x : s) {                                   // iterate the set: each value once
        if (s.count(x - 1)) continue;                   // not a run start
        int len = 1;
        while (s.count(x + len)) len++;
        best = max(best, len);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{100, 4, 200, 1, 3, 2}, {0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, {1, 0, 1, 2}, {}};
    for (auto& nums : tests) {
        cout << "sorted: " << longestConsecutiveSorted(nums) << "\n";
        cout << "set   : " << longestConsecutive(nums) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_set<int> s(v.begin(), v.end()) builds a set from a range.
 * - s.count(x) returns 0 or 1: a lookup that never inserts.
 * - x - 1 / x + len stay within int for values in [-1e9, 1e9].
 */
