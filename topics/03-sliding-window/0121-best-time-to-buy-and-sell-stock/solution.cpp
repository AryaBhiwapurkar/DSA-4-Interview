/*
 * 0121. Best Time to Buy and Sell Stock  |  Easy  |  Sliding Window
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 *
 * Problem: Buy on one day and sell on a later day; return the max profit
 *          (0 if no profit is possible).
 *
 * Examples:
 *   [7,1,5,3,6,4]  -> 5
 *   [7,6,4,3,1]    -> 0
 *   [2,4,1]        -> 2
 *   [5]            -> 0
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Running min  ⭐     O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int maxProfitBrute(const vector<int>& prices) {
    int best = 0, n = prices.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            best = max(best, prices[j] - prices[i]);
    return best;
}

// ---------- Approach 2: Running Min ⭐ ----------
int maxProfit(const vector<int>& prices) {
    int minPrice = INT_MAX, best = 0;
    for (int p : prices) {
        if (minPrice != INT_MAX) best = max(best, p - minPrice);   // sell today, bought at the cheapest earlier day
        minPrice = min(minPrice, p);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{7, 1, 5, 3, 6, 4}, {7, 6, 4, 3, 1}, {2, 4, 1}, {5}};
    for (auto& p : tests) {
        cout << "brute  : " << maxProfitBrute(p) << "\n";
        cout << "run min: " << maxProfit(p) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - INT_MAX (from <climits>) as an "infinity" start value; guard before
 *   subtracting from it so p - INT_MAX can't overflow.
 * - best starts at 0, which enforces "no trade" as the floor.
 */
