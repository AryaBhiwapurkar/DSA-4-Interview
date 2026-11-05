/*
 * 0122. Best Time to Buy and Sell Stock II  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
 *
 * Problem: Max profit with unlimited transactions, holding at most one share
 *          (selling and rebuying on the same day is allowed).
 *
 * Examples:
 *   [7,1,5,3,6,4]   -> 7
 *   [1,2,3,4,5]     -> 4
 *   [7,6,4,3,1]     -> 0
 *   [5]             -> 0
 *   [2,1,2,0,1]     -> 2
 *
 * Approaches:
 *   1. State machine DP (hold / free)   O(n) time, O(1) space
 *   2. Sum of positive day-to-day gains  ⭐   O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: State Machine DP ----------
int maxProfitDP(const vector<int>& prices) {
    int hold = -prices[0], freeCash = 0;           // holding a share / not holding
    for (size_t i = 1; i < prices.size(); i++) {
        int newHold = max(hold, freeCash - prices[i]);
        freeCash = max(freeCash, hold + prices[i]);   // uses the OLD hold
        hold = newHold;
    }
    return freeCash;
}

// ---------- Approach 2: Sum of Gains ⭐ ----------
int maxProfit(const vector<int>& prices) {
    int total = 0;
    for (size_t i = 1; i < prices.size(); i++)
        total += max(0, prices[i] - prices[i - 1]);   // take every rise
    return total;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{7, 1, 5, 3, 6, 4}, {1, 2, 3, 4, 5}, {7, 6, 4, 3, 1}, {5}, {2, 1, 2, 0, 1}};
    for (auto& t : tests) {
        cout << "dp   : " << maxProfitDP(t) << "\n";
        cout << "gains: " << maxProfit(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `free` is a C library function name; `freeCash` avoids shadowing it.
 * - Save newHold before updating freeCash so both read yesterday's values.
 * - size_t loop from 1 is safe because prices is non-empty.
 */
