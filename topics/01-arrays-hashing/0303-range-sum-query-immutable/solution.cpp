/*
 * 0303. Range Sum Query - Immutable  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/range-sum-query-immutable/
 *
 * Problem: Fixed array, many queries: sum of nums[left..right] inclusive.
 *
 * Examples:
 *   NumArray([-2,0,3,-5,2,-1])
 *   sumRange(0,2) -> 1
 *   sumRange(2,5) -> -1
 *   sumRange(0,5) -> -3
 *   sumRange(3,3) -> -5   (single element)
 *
 * Approaches:
 *   1. Loop on every query        O(1) build, O(n) per query
 *   2. Prefix sums  ⭐            O(n) build, O(1) per query, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Loop per Query ----------
class NumArrayBrute {
    vector<int> a;

public:
    NumArrayBrute(const vector<int>& nums) : a(nums) {}
    int sumRange(int l, int r) { return accumulate(a.begin() + l, a.begin() + r + 1, 0); }
};

// ---------- Approach 2: Prefix Sums ⭐ ----------
class NumArray {
    vector<int> P;                                 // P[i] = sum of the first i elements

public:
    NumArray(const vector<int>& nums) : P(nums.size() + 1, 0) {
        for (size_t i = 0; i < nums.size(); i++) P[i + 1] = P[i] + nums[i];
    }
    int sumRange(int l, int r) { return P[r + 1] - P[l]; }
};

// ---------- Driver ----------
int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArrayBrute b(nums);
    NumArray p(nums);
    for (auto [l, r] : vector<pair<int, int>>{{0, 2}, {2, 5}, {0, 5}, {3, 3}}) {
        cout << "brute : " << b.sumRange(l, r) << "\n";
        cout << "prefix: " << p.sumRange(l, r) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Member initializer list: NumArray(...) : P(n + 1, 0) { ... } sizes the vector before the body.
 * - accumulate(first, last, 0) sums a half-open range [first, last).
 * - std::partial_sum(nums.begin(), nums.end(), P.begin() + 1) fills prefixes in one call.
 */
