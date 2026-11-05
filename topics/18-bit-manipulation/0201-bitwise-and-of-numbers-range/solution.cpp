/*
 * 0201. Bitwise AND of Numbers Range  |  Medium  |  Bit Manipulation
 * Link: https://leetcode.com/problems/bitwise-and-of-numbers-range/
 *
 * Problem: Return left & (left+1) & ... & right.
 *
 * Examples:
 *   5, 7              -> 4
 *   0, 0              -> 0
 *   1, 2147483647     -> 0
 *   12, 15            -> 12
 *   6, 6              -> 6
 *
 * Approaches:
 *   1. AND every number (stop early at 0)       O(right - left) time, O(1) space
 *   2. Shift both down to the common prefix  ⭐  O(32) time, O(1) space   <- go-to
 *   3. Clear right's low bits: right &= right - 1 while right > left   O(32) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int rangeBitwiseAndBrute(int left, int right) {
    int res = left;
    for (long long x = (long long)left + 1; x <= right && res; x++)   // long long: x++ past INT_MAX
        res &= x;
    return res;
}

// ---------- Approach 2: Common Prefix ⭐ ----------
int rangeBitwiseAnd(int left, int right) {
    int shift = 0;
    while (left != right) {                        // differing low bits all hit 0 in the range
        left >>= 1;
        right >>= 1;
        shift++;
    }
    return left << shift;                          // non-negative inputs: no sign issues
}

// ---------- Approach 3: Clear Lowest Bits ----------
int rangeBitwiseAndKernighan(int left, int right) {
    while (right > left) right &= right - 1;       // drop right's lowest 1 bit
    return right;
}

// ---------- Driver ----------
int main() {
    vector<pair<int, int>> tests = {{5, 7}, {0, 0}, {1, INT_MAX}, {12, 15}, {6, 6}};
    for (auto [l, r] : tests) {
        cout << "brute    : " << rangeBitwiseAndBrute(l, r) << "\n";
        cout << "prefix   : " << rangeBitwiseAnd(l, r) << "\n";
        cout << "kernighan: " << rangeBitwiseAndKernighan(l, r) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - A long long loop counter avoids `x++` overflowing when right == INT_MAX.
 * - `&& res` in the loop condition stops as soon as the AND hits 0.
 * - Inputs are 0..2^31-1, so shifting left by up to 31 never touches the sign bit.
 */
