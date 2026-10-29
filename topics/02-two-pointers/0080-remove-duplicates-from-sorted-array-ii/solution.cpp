/*
 * 0080. Remove Duplicates from Sorted Array II  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
 *
 * Problem: In a sorted array, keep each value at most twice (in order),
 *          in place. Return k = length of the result.
 *
 * Examples (k, then first k elements):
 *   [1,1,1,2,2,3]          -> 5, [1,1,2,2,3]
 *   [0,0,1,1,1,1,2,3,3]    -> 7, [0,0,1,1,2,3,3]
 *   [1,1,1,2,2,2]          -> 4, [1,1,2,2]
 *   [5]                    -> 1, [5]
 *
 * Approaches:
 *   1. Run counter               O(n) time, O(1) space
 *   2. Compare with nums[k-2] ⭐  O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Run Counter ----------
int removeDuplicatesCounter(vector<int>& nums) {
    int k = 0, run = 0;
    for (size_t i = 0; i < nums.size(); i++) {
        run = (i > 0 && nums[i] == nums[i - 1]) ? run + 1 : 1;   // reads input order; writes trail behind
        if (run <= 2) nums[k++] = nums[i];
    }
    return k;
}

// ---------- Approach 2: Compare With nums[k-2] ⭐ ----------
int removeDuplicates(vector<int>& nums) {
    int n = nums.size(), k = min(n, 2);                // first two always stay
    for (int i = 2; i < n; i++)
        if (nums[i] != nums[k - 2]) nums[k++] = nums[i];  // output already has two copies if equal
    return k;
}

// ---------- Driver ----------
void show(const string& label, vector<int> nums, int (*fn)(vector<int>&)) {
    int k = fn(nums);
    cout << label << ": " << k << ", [";
    for (int i = 0; i < k; i++) cout << (i ? "," : "") << nums[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 1, 1, 2, 2, 3}, {0, 0, 1, 1, 1, 1, 2, 3, 3}, {1, 1, 1, 2, 2, 2}, {5}};
    for (auto& nums : tests) {
        show("counter", nums, removeDuplicatesCounter);
        show("k-2    ", nums, removeDuplicates);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - min(n, 2) needs both args of the same type (int here).
 * - Ternary for the run length keeps the update on one line.
 * - Note: the counter version compares nums[i] with nums[i-1] BEFORE that
 *   slot could be overwritten (k <= i always, and k-1 < i), so it stays correct.
 */
