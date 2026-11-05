/*
 * 0190. Reverse Bits  |  Easy  |  Bit Manipulation
 * Link: https://leetcode.com/problems/reverse-bits/
 *
 * Problem: Reverse the 32 bits of an integer (bit 0 swaps with bit 31, and so
 *          on) and return the resulting unsigned value.
 *
 * Examples:
 *   43261596     -> 964176192
 *   2147483644   -> 1073741822
 *   0            -> 0
 *   1            -> 2147483648
 *   4294967293   -> 3221225471   (0xFFFFFFFD)
 *
 * Approaches:
 *   1. Bit by bit: shift out of n, into result  ⭐   O(32) time, O(1) space   <- go-to
 *   2. Divide and conquer swaps (masks)            O(log 32) = O(5) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Bit by Bit ⭐ ----------
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {                 // exactly 32 iterations
        res = (res << 1) | (n & 1);
        n >>= 1;
    }
    return res;
}

// ---------- Approach 2: Divide and Conquer ----------
uint32_t reverseBitsSwap(uint32_t n) {
    n = (n >> 16) | (n << 16);                                  // halves
    n = ((n & 0xFF00FF00u) >> 8) | ((n & 0x00FF00FFu) << 8);    // bytes
    n = ((n & 0xF0F0F0F0u) >> 4) | ((n & 0x0F0F0F0Fu) << 4);    // nibbles
    n = ((n & 0xCCCCCCCCu) >> 2) | ((n & 0x33333333u) << 2);    // pairs
    n = ((n & 0xAAAAAAAAu) >> 1) | ((n & 0x55555555u) << 1);    // single bits
    return n;
}

// ---------- Driver ----------
int main() {
    for (uint32_t n : {43261596u, 2147483644u, 0u, 1u, 4294967293u}) {
        cout << "loop: " << reverseBits(n) << "\n";
        cout << "swap: " << reverseBitsSwap(n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - uint32_t (from <cstdint>) wraps at 32 bits, so left shifts drop overflow bits for free.
 * - The u suffix keeps hex masks unsigned.
 * - Shifting a signed negative int left is undefined before C++20; stay unsigned.
 */
