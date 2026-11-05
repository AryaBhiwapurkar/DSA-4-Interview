/*
 * 0007. Reverse Integer  |  Medium  |  Bit Manipulation
 * Link: https://leetcode.com/problems/reverse-integer/
 *
 * Problem: Reverse the decimal digits of a 32-bit signed int. Return 0 if the
 *          result doesn't fit in 32 bits. Assume no 64-bit integers are available.
 *
 * Examples:
 *   123           -> 321
 *   -123          -> -321
 *   120           -> 21
 *   1534236469    -> 0   (9646324351 overflows)
 *   -2147483648   -> 0
 *   -2147483412   -> -2143847412
 *
 * Approaches:
 *   1. String reverse + range check           O(d) time, O(d) space
 *   2. Pop digits, check before pushing  ⭐    O(d) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: String Reverse ----------
int reverseStr(int x) {
    string s = to_string(x);
    bool neg = s[0] == '-';
    if (neg) s = s.substr(1);
    reverse(s.begin(), s.end());
    long long r = stoll(s);                        // uses 64 bits: breaks the "no 64-bit" rule
    if (neg) r = -r;
    return (r < INT_MIN || r > INT_MAX) ? 0 : (int)r;
}

// ---------- Approach 2: Pop and Check ⭐ ----------
int reverse(int x) {
    int r = 0;
    while (x != 0) {
        int d = x % 10;                            // C++ %: same sign as x, so d is negative for negative x
        x /= 10;
        if (r > INT_MAX / 10 || (r == INT_MAX / 10 && d > 7)) return 0;   // r*10 + d > INT_MAX
        if (r < INT_MIN / 10 || (r == INT_MIN / 10 && d < -8)) return 0;  // r*10 + d < INT_MIN
        r = r * 10 + d;
    }
    return r;
}

// ---------- Driver ----------
int main() {
    for (int x : {123, -123, 120, 1534236469, INT_MIN, -2147483412}) {
        cout << "string: " << reverseStr(x) << "\n";
        cout << "pop   : " << reverse(x) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - C++ truncates toward zero: -123 % 10 == -3 and -123 / 10 == -12, so negatives need no abs().
 * - abs(INT_MIN) overflows; that's why the go-to never negates x.
 * - INT_MAX / 10 == 214748364, and INT_MAX ends in 7, INT_MIN in 8.
 */
