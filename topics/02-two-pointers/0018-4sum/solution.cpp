/*
 * 0018. 4Sum  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/4sum/
 *
 * Problem: All unique quadruplets (by value, distinct indices) summing to target.
 *
 * Examples:
 *   [1,0,-1,0,-2,2],  target = 0   -> [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 *   [2,2,2,2,2],      target = 8   -> [[2,2,2,2]]
 *   [1000000000,1000000000,1000000000,1000000000], target = -294967296 -> []   (int overflow trap)
 *   [1,2,3],          target = 6   -> []   (fewer than 4 numbers)
 *
 * Approaches:
 *   1. Four loops + set                          O(n^4) time
 *   2. Sort + two loops + two pointers  ⭐       O(n^3) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Four Loops + Set ----------
vector<vector<int>> fourSumBrute(vector<int> nums, int target) {
    sort(nums.begin(), nums.end());                // sorted picks -> canonical tuples
    int n = nums.size();
    set<vector<int>> found;
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++)
            for (int c = b + 1; c < n; c++)
                for (int d = c + 1; d < n; d++)
                    if ((long long)nums[a] + nums[b] + nums[c] + nums[d] == target)
                        found.insert({nums[a], nums[b], nums[c], nums[d]});
    return vector<vector<int>>(found.begin(), found.end());
}

// ---------- Approach 2: Sort + Two Pointers ⭐ ----------
vector<vector<int>> fourSum(vector<int> nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> res;
    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;   // dedupe j relative to its own start
            int lo = j + 1, hi = n - 1;
            while (lo < hi) {
                long long s = (long long)nums[i] + nums[j] + nums[lo] + nums[hi];   // 4e9 overflows int
                if (s < target) lo++;
                else if (s > target) hi--;
                else {
                    res.push_back({nums[i], nums[j], nums[lo], nums[hi]});
                    while (lo < hi && nums[lo] == nums[lo + 1]) lo++;
                    while (lo < hi && nums[hi] == nums[hi - 1]) hi--;
                    lo++, hi--;
                }
            }
        }
    }
    return res;
}

// ---------- Driver ----------
void print(vector<vector<int>> v) {
    sort(v.begin(), v.end());
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < v[i].size(); j++) cout << (j ? "," : "") << v[i][j];
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 0, -1, 0, -2, 2}, 0}, {{2, 2, 2, 2, 2}, 8},
        {{1000000000, 1000000000, 1000000000, 1000000000}, -294967296}, {{1, 2, 3}, 6}};
    for (auto& [nums, t] : tests) {
        cout << "brute   : "; print(fourSumBrute(nums, t));
        cout << "pointers: "; print(fourSum(nums, t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Cast the first operand: (long long)a + b + c + d promotes the whole sum to 64-bit.
 * - set<vector<int>> de-duplicates whole tuples (vectors compare lexicographically).
 * - n - 3 with int n is safe when n < 4 (negative bound, loop doesn't run); with size_t it would wrap.
 */
