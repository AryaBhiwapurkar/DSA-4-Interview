/*
 * 0188. Best Time to Buy and Sell Stock IV  |  Hard  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
 *
 * Problem: Max profit with at most k non-overlapping buy/sell transactions.
 *
 * Examples:
 *   k=2, [2,4,1]          -> 2
 *   k=2, [3,2,6,5,0,3]    -> 7
 *   k=1, [7,1,5,3,6,4]    -> 5
 *   k=100, [1,2,3,4,5]    -> 4   (k >= n/2: unlimited)
 *   k=3, [1,3,2,5,4,8,0,1] -> 9    (4 rises, keep the best 3)
 *
 * Approaches:
 *   1. Memoized recursion (day, trades left, holding)   O(n*k) time, O(n*k) space
 *   2. buy[j] / sell[j] state arrays  ⭐                 O(n*k) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
int f(const vector<int>& p, int i, int left, int holding, vector<vector<array<int, 2>>>& memo) {
    if (i == (int)p.size() || left == 0) return 0;
    int& m = memo[i][left][holding];
    if (m != -1) return m;
    if (holding) m = max(f(p, i + 1, left, 1, memo), p[i] + f(p, i + 1, left - 1, 0, memo));  // keep / sell
    else m = max(f(p, i + 1, left, 0, memo), -p[i] + f(p, i + 1, left, 1, memo));            // wait / buy
    return m;
}

int maxProfitMemo(int k, const vector<int>& prices) {
    vector<vector<array<int, 2>>> memo(prices.size(), vector<array<int, 2>>(k + 1, {-1, -1}));
    return f(prices, 0, k, 0, memo);
}

// ---------- Approach 2: State Arrays ⭐ ----------
int maxProfit(int k, const vector<int>& prices) {
    int n = prices.size();
    if (2 * k >= n) {                              // enough trades to take every rise
        int total = 0;
        for (int i = 1; i < n; i++) total += max(0, prices[i] - prices[i - 1]);
        return total;
    }
    vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);   // buy[j]: holding the j-th share
    for (int p : prices)
        for (int j = 1; j <= k; j++) {
            buy[j] = max(buy[j], sell[j - 1] - p);  // j-th buy uses the (j-1)-th sale's money
            sell[j] = max(sell[j], buy[j] + p);     // buy[j] >= -p now, no overflow
        }
    return sell[k];
}

// ---------- Driver ----------
int main() {
    vector<pair<int, vector<int>>> tests = {
        {2, {2, 4, 1}}, {2, {3, 2, 6, 5, 0, 3}}, {1, {7, 1, 5, 3, 6, 4}}, {100, {1, 2, 3, 4, 5}}, {3, {1, 3, 2, 5, 4, 8, 0, 1}}
    };
    for (auto& [k, t] : tests) {
        cout << "memo  : " << maxProfitMemo(k, t) << "\n";
        cout << "states: " << maxProfit(k, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<vector<array<int, 2>>> is a 3-D memo with a fixed last dimension.
 * - `int& m = memo[...]` writes the cache slot through a reference.
 * - INT_MIN is safe for buy[] because each buy[j] is raised to >= -p before buy[j] + p.
 */
