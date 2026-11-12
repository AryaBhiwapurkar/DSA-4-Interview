/*
 * 0031. Next Permutation  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/next-permutation/
 *
 * Problem: Rearrange nums in place into the next lexicographically greater
 *          permutation; wrap to ascending order after the largest one.
 *
 * Examples:
 *   [1,2,3]      -> [1,3,2]
 *   [3,2,1]      -> [1,2,3]
 *   [1,1,5]      -> [1,5,1]
 *   [1,3,5,4,2]  -> [1,4,2,3,5]
 *   [2,2,2]      -> [2,2,2]
 *   [1]          -> [1]
 *
 * Approaches:
 *   1. Generate all permutations           O(n! * n) time and space
 *   2. Pivot + swap + reverse suffix  ⭐   O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Generate All ----------
void nextPermutationBrute(vector<int>& nums) {
    vector<int> sorted_ = nums;
    sort(sorted_.begin(), sorted_.end());
    vector<vector<int>> perms;
    do perms.push_back(sorted_);                   // distinct permutations in order
    while (next_permutation(sorted_.begin(), sorted_.end()));
    size_t i = find(perms.begin(), perms.end(), nums) - perms.begin();
    nums = perms[(i + 1) % perms.size()];          // wrap after the last one
}

// ---------- Approach 2: Pivot + Swap + Reverse ⭐ ----------
void nextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) i--;  // skip the non-increasing suffix
    if (i >= 0) {
        int j = n - 1;
        while (nums[j] <= nums[i]) j--;            // rightmost value > pivot
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());     // suffix ascending = smallest
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3}, {3, 2, 1}, {1, 1, 5}, {1, 3, 5, 4, 2}, {2, 2, 2}, {1}};
    for (auto& t : tests) {
        auto a = t, b = t;
        nextPermutationBrute(a);
        nextPermutation(b);
        cout << "brute: "; print(a);
        cout << "pivot: "; print(b);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::next_permutation(first, last) does this in place and returns false after wrapping.
 * - do ... while (next_permutation(...)) enumerates every distinct permutation from sorted order.
 * - reverse(nums.begin() + i + 1, nums.end()) works for i = -1 too (reverses everything).
 */
