/*
 * 0123. Best Time to Buy and Sell Stock III  |  Hard  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
 *
 * Problem: Max profit with at most two non-overlapping buy/sell transactions.
 *
 * Examples:
 *   [3,3,5,0,0,3,1,4]   -> 6
 *   [1,2,3,4,5]         -> 4
 *   [7,6,4,3,1]         -> 0
 *   [1]                 -> 0
 *   [1,2,4,2,5,7,2,4,9,0] -> 13
 *
 * Approaches:
 *   1. Brute split point                  O(n^2) time, O(1) space
 *   2. Prefix / suffix best single trade  O(n) time, O(n) space
 *   3. Four states b1, s1, b2, s2  ⭐      O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

int oneTrade(const vector<int>& p, int lo, int hi) {   // best single trade in p[lo, hi)
    int best = 0, low = INT_MAX;
    for (int i = lo; i < hi; i++) {
        low = min(low, p[i]);
        best = max(best, p[i] - low);
    }
    return best;
}

// ---------- Approach 1: Brute Split Point ----------
int maxProfitBrute(const vector<int>& p) {
    int n = p.size(), best = 0;
    for (int k = 0; k <= n; k++) best = max(best, oneTrade(p, 0, k) + oneTrade(p, k, n));
    return best;
}

// ---------- Approach 2: Prefix / Suffix ----------
int maxProfitPrefix(const vector<int>& p) {
    int n = p.size();
    vector<int> left(n, 0);                        // left[i]: best trade within days 0..i
    int low = p[0];
    for (int i = 1; i < n; i++) {
        low = min(low, p[i]);
        left[i] = max(left[i - 1], p[i] - low);
    }
    int best = left[n - 1], high = p[n - 1], right = 0;   // right: best trade within days i+1..n-1
    for (int i = n - 2; i >= 0; i--) {
        best = max(best, left[i] + right);
        high = max(high, p[i]);
        right = max(right, high - p[i]);
    }
    return best;
}

// ---------- Approach 3: Four States ⭐ ----------
int maxProfit(const vector<int>& prices) {
    int b1 = INT_MIN, b2 = INT_MIN, s1 = 0, s2 = 0;   // best balance after each step
    for (int p : prices) {
        b1 = max(b1, -p);
        s1 = max(s1, b1 + p);                      // b1 >= -p here, so no overflow
        b2 = max(b2, s1 - p);                      // 2nd buy is funded by the 1st sale
        s2 = max(s2, b2 + p);
    }
    return s2;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{3, 3, 5, 0, 0, 3, 1, 4}, {1, 2, 3, 4, 5}, {7, 6, 4, 3, 1}, {1}, {1, 2, 4, 2, 5, 7, 2, 4, 9, 0}};
    for (auto& t : tests) {
        cout << "brute : " << maxProfitBrute(t) << "\n";
        cout << "prefix: " << maxProfitPrefix(t) << "\n";
        cout << "states: " << maxProfit(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - INT_MIN as "not bought yet" is safe only because b1 is raised to >= -p before b1 + p.
 * - Updating the four states in order, in place, works: a same-day buy and sell nets 0.
 * - A helper taking [lo, hi) bounds avoids copying sub-vectors.
 */
