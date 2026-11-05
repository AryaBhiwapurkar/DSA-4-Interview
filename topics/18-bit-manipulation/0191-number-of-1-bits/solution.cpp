/*
 * 0191. Number of 1 Bits  |  Easy  |  Bit Manipulation
 * Link: https://leetcode.com/problems/number-of-1-bits/
 *
 * Problem: Count the set bits (Hamming weight) of a positive integer.
 *
 * Examples:
 *   11           -> 3   (1011)
 *   128          -> 1   (10000000)
 *   2147483645   -> 30  (thirty 1s and one 0)
 *   1            -> 1
 *   2147483647   -> 31
 *
 * Approaches:
 *   1. Check every bit with a shift      O(32) time, O(1) space
 *   2. n & (n - 1) drops the lowest 1  ⭐  O(#set bits) time, O(1) space   <- go-to
 *   3. Built-in popcount                 O(1) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Shift and Check ----------
int hammingWeightShift(uint32_t n) {
    int count = 0;
    for (; n; n >>= 1) count += n & 1;            // unsigned: >> shifts in zeros
    return count;
}

// ---------- Approach 2: n & (n - 1) ⭐ ----------
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        n &= n - 1;                                // clears the lowest set bit
        count++;
    }
    return count;
}

// ---------- Approach 3: Built-in ----------
int hammingWeightBuiltin(uint32_t n) { return __builtin_popcount(n); }   // or bitset<32>(n).count()

// ---------- Driver ----------
int main() {
    for (uint32_t n : {11u, 128u, 2147483645u, 1u, 2147483647u}) {
        cout << "shift  : " << hammingWeightShift(n) << "\n";
        cout << "n&(n-1): " << hammingWeight(n) << "\n";
        cout << "builtin: " << hammingWeightBuiltin(n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Use unsigned types for bit loops: >> on a negative signed int keeps the sign bit.
 * - __builtin_popcount (GCC/Clang) or bitset<32>(n).count() count set bits;
 *   C++20 adds std::popcount.
 * - The 11u suffix makes the literal unsigned.
 */
