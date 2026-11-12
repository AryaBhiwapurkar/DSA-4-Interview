/*
 * 1283. Find the Smallest Divisor Given a Threshold  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
 *
 * Problem: Return the smallest positive d such that the sum of ceil(x / d)
 *          over nums is <= threshold.
 *
 * Examples:
 *   [1,2,5,9],             threshold = 6         -> 5
 *   [44,22,33,11,1],       threshold = 5         -> 44
 *   [21212,10101,12121],   threshold = 1000000   -> 1
 *   [2,3,5,7,11],          threshold = 11        -> 3
 *   [19],                  threshold = 5         -> 4
 *
 * Approaches:
 *   1. Try every divisor                O(n max) time, O(1) space
 *   2. Binary search on the divisor ⭐  O(n log max) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

long long costFor(const vector<int>& nums, int d) {
    long long s = 0;                          // can reach 5e10 at d = 1
    for (int x : nums) s += (x + d - 1) / d;  // integer ceil
    return s;
}

// ---------- Approach 1: Try Every Divisor ----------
int smallestDivisorLinear(const vector<int>& nums, int threshold) {
    int d = 1;
    while (costFor(nums, d) > threshold) d++;
    return d;
}

// ---------- Approach 2: Binary Search on the Divisor ⭐ ----------
int smallestDivisor(const vector<int>& nums, int threshold) {
    int lo = 1, hi = *max_element(nums.begin(), nums.end());   // d = max gives n <= threshold
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (costFor(nums, mid) <= threshold) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 2, 5, 9}, 6}, {{44, 22, 33, 11, 1}, 5}, {{21212, 10101, 12121}, 1000000},
        {{2, 3, 5, 7, 11}, 11}, {{19}, 5}};
    for (auto& [nums, t] : tests) {
        cout << "linear: " << smallestDivisorLinear(nums, t) << "\n";
        cout << "binary: " << smallestDivisor(nums, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (x + d - 1) / d is ceil(x / d) for positive ints, with no floating point.
 * - x / d on ints truncates, so ceil(x / d) on ints would already be floored.
 * - Accumulate into long long when the sum of many terms can pass 2^31.
 */
