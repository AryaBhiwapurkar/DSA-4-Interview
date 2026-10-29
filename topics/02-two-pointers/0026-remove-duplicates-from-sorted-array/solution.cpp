/*
 * 0026. Remove Duplicates from Sorted Array  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 *
 * Problem: In a sorted array, keep one copy of each value at the front
 *          (in order), in place. Return k = number of unique values.
 *
 * Examples (k, then first k elements):
 *   [1,1,2]                 -> 2, [1,2]
 *   [0,0,1,1,1,2,2,3,3,4]   -> 5, [0,1,2,3,4]
 *   [7]                     -> 1, [7]
 *
 * Approaches:
 *   1. Collect uniques, copy back   O(n) time, O(n) space
 *   2. Read/write pointers  ⭐       O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Collect Uniques, Copy Back ----------
int removeDuplicatesCopy(vector<int>& nums) {
    vector<int> uniq;
    for (int x : nums)
        if (uniq.empty() || uniq.back() != x) uniq.push_back(x);
    copy(uniq.begin(), uniq.end(), nums.begin());
    return uniq.size();
}

// ---------- Approach 2: Read/Write Pointers ⭐ ----------
int removeDuplicates(vector<int>& nums) {
    int k = 1;                                    // nums[0] is always kept
    for (size_t i = 1; i < nums.size(); i++)
        if (nums[i] != nums[k - 1]) nums[k++] = nums[i];   // compare with last WRITTEN value
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
    vector<vector<int>> tests = {{1, 1, 2}, {0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, {7}};
    for (auto& nums : tests) {
        show("copy      ", nums, removeDuplicatesCopy);
        show("read/write", nums, removeDuplicates);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - nums[k++] = x writes at k, then increments k.
 * - std::copy(src_begin, src_end, dst_begin) overwrites the destination range.
 * - int (*fn)(vector<int>&) is a function-pointer parameter.
 */
