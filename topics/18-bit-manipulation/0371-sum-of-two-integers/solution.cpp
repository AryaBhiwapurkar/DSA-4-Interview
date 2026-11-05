/*
 * 0371. Sum of Two Integers  |  Medium  |  Bit Manipulation
 * Link: https://leetcode.com/problems/sum-of-two-integers/
 *
 * Problem: Return a + b without using the + or - operators.
 *
 * Examples:
 *   1, 2        -> 3
 *   2, 3        -> 5
 *   -1, 1       -> 0
 *   -12, -8     -> -20
 *   1000, -1000 -> 0
 *
 * Approaches:
 *   1. Bit-by-bit full adder (32 positions)   O(32) time, O(1) space
 *   2. XOR for sum, AND << 1 for carry  ⭐     O(32) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Full Adder ----------
int getSumAdder(int a, int b) {
    uint32_t ua = a, ub = b, res = 0, carry = 0;
    for (int i = 0; i < 32; i++) {
        uint32_t x = (ua >> i) & 1, y = (ub >> i) & 1;
        res |= (x ^ y ^ carry) << i;               // sum bit
        carry = (x & y) | (carry & (x ^ y));       // carry out
    }
    return (int)res;                               // two's complement reinterpretation
}

// ---------- Approach 2: XOR + Carry ⭐ ----------
int getSum(int a, int b) {
    uint32_t x = a, y = b;                         // unsigned: shifting carries into bit 31 is defined
    while (y) {
        uint32_t carry = (x & y) << 1;
        x ^= y;                                    // sum without carries
        y = carry;
    }
    return (int)x;
}

// ---------- Driver ----------
int main() {
    vector<pair<int, int>> tests = {{1, 2}, {2, 3}, {-1, 1}, {-12, -8}, {1000, -1000}};
    for (auto [a, b] : tests) {
        cout << "adder: " << getSumAdder(a, b) << "\n";
        cout << "xor  : " << getSum(a, b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Converting int -> uint32_t keeps the bit pattern (mod 2^32).
 * - Left-shifting a negative signed int is undefined before C++20; do it on unsigned.
 * - (int)x converts back; it's two's complement on every mainstream compiler (guaranteed in C++20).
 */
