/*
 * 0283. Move Zeroes  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/move-zeroes/
 *
 * Problem: Move all zeros to the end in place, keeping non-zero order.
 *
 * Examples:
 *   [0,1,0,3,12]  -> [1,3,12,0,0]
 *   [0]           -> [0]
 *   [1,2,3]       -> [1,2,3]
 *   [0,0,1]       -> [1,0,0]
 *
 * Approaches:
 *   1. Copy non-zeros, then fill zeros   O(n) time, O(1) space (two passes)
 *   2. Swap read/write pointers  ⭐      O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Copy + Fill ----------
void moveZeroesFill(vector<int>& nums) {
    int w = 0;
    for (int x : nums)
        if (x != 0) nums[w++] = x;
    fill(nums.begin() + w, nums.end(), 0);
}

// ---------- Approach 2: Swap Read/Write ⭐ ----------
void moveZeroes(vector<int>& nums) {
    int w = 0;                                     // next slot for a non-zero
    for (int r = 0; r < (int)nums.size(); r++)
        if (nums[r] != 0) {
            if (r != w) swap(nums[w], nums[r]);    // skip self-swaps
            w++;
        }
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{0, 1, 0, 3, 12}, {0}, {1, 2, 3}, {0, 0, 1}};
    for (auto& t : tests) {
        auto a = t, b = t;
        moveZeroesFill(a);
        moveZeroes(b);
        cout << "fill: "; print(a);
        cout << "swap: "; print(b);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - nums[w++] = x writes, then advances w.
 * - fill(first, last, value) assigns a value to a range.
 * - std::stable_partition(nums.begin(), nums.end(), [](int x){ return x != 0; }) is the library one-liner.
 */
