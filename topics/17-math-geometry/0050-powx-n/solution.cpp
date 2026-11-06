/*
 * 0050. Pow(x, n)  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/powx-n/
 *
 * Problem: Compute x^n for a double x and an int n (possibly negative).
 *
 * Examples:
 *   x = 2.0, n = 10           -> 1024.00000
 *   x = 2.1, n = 3            -> 9.26100
 *   x = 2.0, n = -2           -> 0.25000
 *   x = 5.0, n = 0            -> 1.00000
 *   x = -1.0, n = -2147483648 -> 1.00000   (INT_MIN: -n overflows int)
 *   x = -2.0, n = 5           -> -32.00000
 *
 * Approaches:
 *   1. Multiply |n| times        O(|n|) time, O(1) space      (too slow for big n; demoed on small n only)
 *   2. Recursive halving         O(log n) time, O(log n) space
 *   3. Iterative squaring  ⭐    O(log n) time, O(1) space    <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Multiply n Times ----------
double myPowLinear(double x, int n) {
    long long N = n;
    if (N < 0) x = 1 / x, N = -N;
    double r = 1;
    while (N--) r *= x;
    return r;
}

// ---------- Approach 2: Recursive Halving ----------
double powPos(double x, long long N) {
    if (N == 0) return 1;
    double half = powPos(x, N / 2);                // compute once, use twice
    return N % 2 ? half * half * x : half * half;
}

double myPowRecursive(double x, int n) {
    long long N = n;                               // -INT_MIN fits in long long
    return N < 0 ? powPos(1 / x, -N) : powPos(x, N);
}

// ---------- Approach 3: Iterative Squaring ⭐ ----------
double myPow(double x, int n) {
    long long N = n;
    if (N < 0) x = 1 / x, N = -N;
    double result = 1;
    while (N > 0) {
        if (N & 1) result *= x;                    // this bit of N is set
        x *= x;                                    // x, x^2, x^4, x^8, ...
        N >>= 1;
    }
    return result;
}

// ---------- Driver ----------
int main() {
    vector<pair<double, int>> tests = {{2.0, 10}, {2.1, 3}, {2.0, -2}, {5.0, 0},
                                       {-1.0, INT_MIN}, {-2.0, 5}};
    cout << fixed << setprecision(5);
    for (auto [x, n] : tests) {
        if (abs((long long)n) <= 1000) cout << "linear   : " << myPowLinear(x, n) << "\n";
        else cout << "linear   : skipped (|n| too big)\n";
        cout << "recursive: " << myPowRecursive(x, n) << "\n";
        cout << "squaring : " << myPow(x, n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - long long N = n before negating: -INT_MIN is undefined behaviour in int.
 * - N & 1 tests odd, N >>= 1 halves (N is non-negative here).
 * - cout << fixed << setprecision(5) prints exactly 5 decimals.
 */
