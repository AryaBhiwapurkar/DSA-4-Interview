/*
 * 0169. Majority Element  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/majority-element/
 *
 * Problem: Return the element that appears more than n/2 times.
 *          It is guaranteed to exist.
 *
 * Examples:
 *   [3,2,3]           -> 3
 *   [2,2,1,1,1,2,2]   -> 2
 *   [1,2,2]           -> 2
 *
 * Approaches:
 *   1. Hashmap count      O(n) time, O(n) space
 *   2. Sort, take middle  O(n log n) time, O(1) extra space
 *   3. Boyer-Moore  ⭐     O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Hashmap Count ----------
int majorityElementHash(const vector<int>& nums) {
    unordered_map<int, int> cnt;
    for (int x : nums)
        if (++cnt[x] > (int)nums.size() / 2) return x;   // can stop as soon as it passes n/2
    return -1;                                           // unreachable when a majority exists
}

// ---------- Approach 2: Sort, Take Middle ----------
int majorityElementSorted(vector<int> nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];                        // majority covers more than half, so it spans the middle
}

// ---------- Approach 3: Boyer-Moore Voting ⭐ ----------
int majorityElement(const vector<int>& nums) {
    int candidate = 0, count = 0;
    for (int x : nums) {
        if (count == 0) candidate = x;                   // previous votes fully cancelled
        count += (x == candidate) ? 1 : -1;
    }
    return candidate;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{3, 2, 3}, {2, 2, 1, 1, 1, 2, 2}, {1, 2, 2}};
    for (auto& nums : tests) {
        cout << "hash  : " << majorityElementHash(nums) << "\n";
        cout << "sorted: " << majorityElementSorted(nums) << "\n";
        cout << "voting: " << majorityElement(nums) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - ++cnt[x] on unordered_map inserts 0 first if x is missing, then increments
 *   (intended here; avoid it for pure lookups).
 * - Compare int with size() via a cast to avoid -Wsign-compare.
 * - Ternary inside += keeps the vote update on one line.
 */
