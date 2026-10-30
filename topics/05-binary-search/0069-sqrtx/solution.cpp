/*
 * 0069. Sqrt(x)  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/sqrtx/
 *
 * Problem: Return floor(sqrt(x)) for 0 <= x <= 2^31 - 1 without sqrt/pow.
 *
 * Examples:
 *   4           -> 2
 *   8           -> 2
 *   0           -> 0
 *   1           -> 1
 *   2147395599  -> 46339
 *   2147483647  -> 46340
 *
 * Approaches:
 *   1. Linear scan                O(sqrt x) time, O(1) space
 *   2. Binary search on answer ⭐  O(log x) time, O(1) space   <- go-to
 *   3. Newton's method            O(log x) iterations, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int mySqrtLinear(int x) {
    long long k = 0;
    while ((k + 1) * (k + 1) <= x) k++;    // long long: (k+1)^2 can exceed INT_MAX
    return k;
}

// ---------- Approach 2: Binary Search on Answer ⭐ ----------
int mySqrt(int x) {
    long long lo = 0, hi = x, ans = 0;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (mid * mid <= x) {              // 64-bit square: no overflow
            ans = mid;                     // mid works; try bigger
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

// ---------- Approach 3: Newton's Method ----------
int mySqrtNewton(int x) {
    long long r = x;
    while (r * r > x) r = (r + x / r) / 2; // integer Newton step, decreases to the floor
    return r;
}

// ---------- Driver ----------
int main() {
    vector<int> tests = {4, 8, 0, 1, 2147395599, 2147483647};
    for (int x : tests) {
        cout << "linear: " << mySqrtLinear(x) << "\n";
        cout << "binary: " << mySqrt(x) << "\n";
        cout << "newton: " << mySqrtNewton(x) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Promote before multiplying: long long mid; mid * mid is 64-bit.
 *   (int)mid * (int)mid would overflow first, then widen.
 * - Comparing long long with int promotes the int; no cast needed.
 * - Overflow-free alternative: `mid <= x / mid` for mid > 0.
 */
