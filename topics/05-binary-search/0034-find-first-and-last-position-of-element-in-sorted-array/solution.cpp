/*
 * 0034. Find First and Last Position of Element in Sorted Array  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 *
 * Problem: Sorted array with duplicates. Return [first, last] index of
 *          target, or [-1,-1]. O(log n).
 *
 * Examples:
 *   [5,7,7,8,8,10], target 8  -> [3,4]
 *   [5,7,7,8,8,10], target 6  -> [-1,-1]
 *   [],             target 0  -> [-1,-1]
 *   [1],            target 1  -> [0,0]
 *   [2,2,2],        target 2  -> [0,2]
 *   [1,2,3],        target 4  -> [-1,-1]
 *
 * Approaches:
 *   1. Linear scan           O(n) time, O(1) space
 *   2. Two lower bounds  ⭐   O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
vector<int> searchRangeLinear(const vector<int>& nums, int target) {
    int first = -1, last = -1;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] != target) continue;
        if (first == -1) first = i;
        last = i;
    }
    return {first, last};
}

// ---------- Approach 2: Two Lower Bounds ⭐ ----------
int lowerBound(const vector<int>& nums, int x) {   // first index with nums[i] >= x
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < x) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

vector<int> searchRange(const vector<int>& nums, int target) {
    int first = lowerBound(nums, target);
    if (first == (int)nums.size() || nums[first] != target) return {-1, -1};   // bounds check first
    int last = lowerBound(nums, target + 1) - 1;   // target <= 1e9: +1 can't overflow
    return {first, last};
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [" << v[0] << "," << v[1] << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{5, 7, 7, 8, 8, 10}, 8}, {{5, 7, 7, 8, 8, 10}, 6}, {{}, 0}, {{1}, 1}, {{2, 2, 2}, 2}, {{1, 2, 3}, 4}
    };
    for (auto& [nums, target] : tests) {
        print("linear", searchRangeLinear(nums, target));
        print("bounds", searchRange(nums, target));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - equal_range(b, e, x) returns {lower_bound, upper_bound} as a pair of iterators.
 * - Iterator to index: it - nums.begin().
 * - Compare nums.size() as int: (int)nums.size() avoids signed/unsigned warnings.
 */
