/*
 * 0209. Minimum Size Subarray Sum  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/minimum-size-subarray-sum/
 *
 * Problem: Positive integers; return the length of the shortest contiguous
 *          subarray with sum >= target, or 0 if none.
 *
 * Examples:
 *   target=7,  [2,3,1,2,4,3]       -> 2
 *   target=4,  [1,4,4]             -> 1
 *   target=11, [1,1,1,1,1,1,1,1]   -> 0
 *   target=15, [1,2,3,4,5]         -> 5
 *
 * Approaches:
 *   1. Brute force                    O(n^2) time, O(1) space
 *   2. Prefix sums + binary search    O(n log n) time, O(n) space
 *   3. Sliding window  ⭐              O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int minSubArrayLenBrute(int target, const vector<int>& nums) {
    int n = nums.size(), best = INT_MAX;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum >= target) {
                best = min(best, j - i + 1);
                break;                                    // longer windows from i can't be shorter
            }
        }
    }
    return best == INT_MAX ? 0 : best;
}

// ---------- Approach 2: Prefix Sums + Binary Search ----------
int minSubArrayLenBinary(int target, const vector<int>& nums) {
    int n = nums.size(), best = INT_MAX;
    vector<int> P(n + 1, 0);                              // P[i] = sum of nums[0..i-1], strictly increasing
    for (int i = 0; i < n; i++) P[i + 1] = P[i] + nums[i];
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(P.begin() + i + 1, P.end(), P[i] + target);   // first j with P[j] - P[i] >= target
        if (it != P.end()) best = min(best, int(it - P.begin()) - i);
    }
    return best == INT_MAX ? 0 : best;
}

// ---------- Approach 3: Sliding Window ⭐ ----------
int minSubArrayLen(int target, const vector<int>& nums) {
    int l = 0, sum = 0, best = INT_MAX;
    for (int r = 0; r < (int)nums.size(); r++) {
        sum += nums[r];
        while (sum >= target) {                           // valid: record, then try to shrink
            best = min(best, r - l + 1);
            sum -= nums[l++];
        }
    }
    return best == INT_MAX ? 0 : best;
}

// ---------- Driver ----------
int main() {
    vector<pair<int, vector<int>>> tests = {
        {7, {2, 3, 1, 2, 4, 3}}, {4, {1, 4, 4}}, {11, {1, 1, 1, 1, 1, 1, 1, 1}}, {15, {1, 2, 3, 4, 5}}
    };
    for (auto& [target, nums] : tests) {
        cout << "brute : " << minSubArrayLenBrute(target, nums) << "\n";
        cout << "binary: " << minSubArrayLenBinary(target, nums) << "\n";
        cout << "window: " << minSubArrayLen(target, nums) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - INT_MAX as a "not found" sentinel; convert to 0 before returning.
 * - lower_bound on a sub-range: lower_bound(P.begin() + i + 1, P.end(), x).
 * - sum -= nums[l++] subtracts nums[l], then advances l.
 */
