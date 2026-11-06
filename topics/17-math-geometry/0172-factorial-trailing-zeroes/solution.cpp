/*
 * 0172. Factorial Trailing Zeroes  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/factorial-trailing-zeroes/
 *
 * Problem: Count the trailing zeros of n! without computing n!.
 *
 * Examples:
 *   3      -> 0
 *   5      -> 1
 *   0      -> 0
 *   25     -> 6
 *   100    -> 24
 *   10000  -> 2499
 *
 * Approaches:
 *   1. Count 5s in each multiple of 5   O(n log n) time, O(1) space
 *   2. n/5 + n/25 + n/125 + ...  ⭐      O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Count 5s in Each Number ----------
int trailingZeroesLinear(int n) {
    int count = 0;
    for (int k = 5; k <= n; k += 5)
        for (int x = k; x % 5 == 0; x /= 5) count++;
    return count;
}

// ---------- Approach 2: Divide by Powers of 5 ⭐ ----------
int trailingZeroes(int n) {
    int count = 0;
    while (n > 0) {
        n /= 5;                                    // numbers with at least one more factor of 5
        count += n;
    }
    return count;
}

// ---------- Driver ----------
int main() {
    for (int n : {3, 5, 0, 25, 100, 10000}) {
        cout << "linear: " << trailingZeroesLinear(n) << "\n";
        cout << "log   : " << trailingZeroes(n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Integer / truncates, which is exactly floor for non-negative n.
 * - Dividing n (not multiplying a power of 5 up) can't overflow.
 * - for (int x = k; x % 5 == 0; x /= 5) strips one factor per iteration.
 */
