/*
 * 0367. Valid Perfect Square  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/valid-perfect-square/
 *
 * Problem: Return whether a positive integer is a perfect square,
 *          without a built-in sqrt.
 *
 * Examples:
 *   16          -> true
 *   14          -> false
 *   1           -> true
 *   808201      -> true    (899^2)
 *   2147395600  -> true    (46340^2, largest square in int)
 *   2147483647  -> false   (mid*mid overflows int)
 *
 * Approaches:
 *   1. Linear root scan               O(sqrt n) time, O(1) space
 *   2. Binary search on the root ⭐   O(log n) time, O(1) space   <- go-to
 *   3. Newton's method                O(log n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Root Scan ----------
bool isPerfectSquareLinear(int num) {
    long long r = 1;
    while (r * r < num) r++;
    return r * r == num;
}

// ---------- Approach 2: Binary Search on the Root ⭐ ----------
bool isPerfectSquare(int num) {
    long long lo = 1, hi = num;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        long long sq = mid * mid;              // 64-bit: mid can be ~10^9
        if (sq == num) return true;
        if (sq < num) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

// ---------- Approach 3: Newton's Method ----------
bool isPerfectSquareNewton(int num) {
    long long x = num;
    while (x * x > num) x = (x + num / x) / 2;  // decreases to floor(sqrt(num))
    return x * x == num;
}

// ---------- Driver ----------
int main() {
    cout << boolalpha;
    for (int num : {16, 14, 1, 808201, 2147395600, 2147483647}) {
        cout << "linear: " << isPerfectSquareLinear(num) << "\n";
        cout << "binary: " << isPerfectSquare(num) << "\n";
        cout << "newton: " << isPerfectSquareNewton(num) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Declare lo/hi/mid as long long so mid * mid is computed in 64-bit.
 * - cout << boolalpha prints true/false instead of 1/0.
 * - Comparing long long with int promotes the int; no cast needed.
 */
