/*
 * 0309. Best Time to Buy and Sell Stock with Cooldown  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
 *
 * Problem: Max profit with unlimited transactions, one share at a time, and a
 *          one-day cooldown after every sale.
 *
 * Examples:
 *   [1,2,3,0,2]     -> 3
 *   [1]             -> 0
 *   [2,1]           -> 0
 *   [1,2,4]         -> 3
 *   [6,1,3,2,4,7]   -> 6
 *
 * Approaches:
 *   1. Memoized recursion (day, holding)       O(n) time, O(n) space
 *   2. State machine: hold / sold / rest  ⭐    O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
int f(const vector<int>& p, int i, int holding, vector<array<int, 2>>& memo) {
    if (i >= (int)p.size()) return 0;
    int& m = memo[i][holding];
    if (m != -1) return m;
    if (holding) m = max(f(p, i + 1, 1, memo), p[i] + f(p, i + 2, 0, memo));   // keep / sell + cooldown
    else m = max(f(p, i + 1, 0, memo), -p[i] + f(p, i + 1, 1, memo));         // wait / buy
    return m;
}

int maxProfitMemo(const vector<int>& prices) {
    vector<array<int, 2>> memo(prices.size(), {-1, -1});
    return f(prices, 0, 0, memo);
}

// ---------- Approach 2: State Machine ⭐ ----------
int maxProfit(const vector<int>& prices) {
    int hold = -prices[0], sold = 0, rest = 0;     // best profit ending today in each state
    for (size_t i = 1; i < prices.size(); i++) {
        int p = prices[i];
        int newHold = max(hold, rest - p);         // can't buy straight from "sold"
        int newSold = hold + p;
        int newRest = max(rest, sold);             // yesterday's sale finishes its cooldown
        hold = newHold, sold = newSold, rest = newRest;
    }
    return max(sold, rest);
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 2, 3, 0, 2}, {1}, {2, 1}, {1, 2, 4}, {6, 1, 3, 2, 4, 7}};
    for (auto& t : tests) {
        cout << "memo : " << maxProfitMemo(t) << "\n";
        cout << "state: " << maxProfit(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `int& m = memo[i][holding];` aliases the cache slot so it's written once.
 * - vector<array<int, 2>> memo(n, {-1, -1}) gives a fixed pair per day.
 * - Compute all new states into temporaries before assigning: the updates read old values.
 */
