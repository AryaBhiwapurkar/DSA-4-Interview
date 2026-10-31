/*
 * 0152. Maximum Product Subarray  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/maximum-product-subarray/
 *
 * Problem: Return the largest product of any non-empty contiguous subarray.
 *
 * Examples:
 *   [2,3,-2,4]       -> 6
 *   [-2,0,-1]        -> 0
 *   [-2,3,-4]        -> 24
 *   [-2]             -> -2
 *   [2,-5,-2,-4,3]   -> 24
 *
 * Approaches:
 *   1. Brute force (every start, running product)   O(n^2) time, O(1) space
 *   2. Track max and min ending here  ⭐              O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int maxProductBrute(const vector<int>& nums) {
    int best = nums[0];
    for (size_t i = 0; i < nums.size(); i++) {
        int prod = 1;
        for (size_t j = i; j < nums.size(); j++) {
            prod *= nums[j];
            best = max(best, prod);
        }
    }
    return best;
}

// ---------- Approach 2: Track Max and Min ⭐ ----------
int maxProduct(const vector<int>& nums) {
    int hi = nums[0], lo = nums[0], best = nums[0];   // max / min product ending here
    for (size_t i = 1; i < nums.size(); i++) {
        int x = nums[i];
        int a = x * hi, b = x * lo;               // a negative x swaps the roles of hi and lo
        hi = max({x, a, b});                      // x alone restarts the subarray (e.g. after a 0)
        lo = min({x, a, b});
        best = max(best, hi);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 3, -2, 4}, {-2, 0, -1}, {-2, 3, -4}, {-2}, {2, -5, -2, -4, 3}};
    for (auto& t : tests) {
        cout << "brute : " << maxProductBrute(t) << "\n";
        cout << "minmax: " << maxProduct(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - max({a, b, c}) / min({...}) take an initializer_list for 3+ values.
 * - Compute a and b before overwriting hi, or lo would use the new hi.
 * - LC guarantees every subarray product fits in a 32-bit int.
 */
