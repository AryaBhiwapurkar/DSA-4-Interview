/*
 * 0137. Single Number II  |  Medium  |  Bit Manipulation
 * Link: https://leetcode.com/problems/single-number-ii/
 *
 * Problem: Every number appears three times except one, which appears once.
 *          Find it in O(n) time and O(1) extra space.
 *
 * Examples:
 *   [2,2,3,2]                       -> 3
 *   [0,1,0,1,0,1,99]                -> 99
 *   [-2,-2,1,1,4,1,4,4,-4,-2]       -> -4
 *   [7]                             -> 7
 *
 * Approaches:
 *   1. Hash map of counts                     O(n) time, O(n) space
 *   2. Count each bit position mod 3  ⭐       O(32n) time, O(1) space   <- go-to
 *   3. ones / twos state machine              O(n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Counts ----------
int singleNumberCount(const vector<int>& nums) {
    unordered_map<int, int> cnt;
    for (int x : nums) cnt[x]++;
    for (auto& [x, c] : cnt)
        if (c == 1) return x;
    return 0;                                      // unreachable for valid input
}

// ---------- Approach 2: Bit Counting ⭐ ----------
int singleNumber(const vector<int>& nums) {
    uint32_t res = 0;
    for (int b = 0; b < 32; b++) {
        int total = 0;
        for (int x : nums) total += ((uint32_t)x >> b) & 1;   // unsigned: no sign-extension
        if (total % 3) res |= 1u << b;             // leftover bit belongs to the single
    }
    return (int)res;
}

// ---------- Approach 3: ones / twos ----------
int singleNumberStates(const vector<int>& nums) {
    int ones = 0, twos = 0;                        // bits seen once / twice (mod 3)
    for (int x : nums) {
        ones = (ones ^ x) & ~twos;
        twos = (twos ^ x) & ~ones;
    }
    return ones;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 2, 3, 2}, {0, 1, 0, 1, 0, 1, 99}, {-2, -2, 1, 1, 4, 1, 4, 4, -4, -2}, {7}};
    for (auto& t : tests) {
        cout << "count : " << singleNumberCount(t) << "\n";
        cout << "bits  : " << singleNumber(t) << "\n";
        cout << "states: " << singleNumberStates(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - 1u << 31 is fine on unsigned; 1 << 31 on int overflows (UB before C++20).
 * - (uint32_t)x >> b shifts in zeros, so bit 31 of negatives is read correctly.
 * - Casting the uint32_t result back to int restores the negative value.
 */
