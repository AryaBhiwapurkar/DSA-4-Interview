/*
 * 0322. Coin Change  |  Medium  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/coin-change/
 *
 * Problem: Fewest coins (unlimited supply of each denomination) that sum to
 *          amount, or -1 if impossible.
 *
 * Examples:
 *   [1,2,5], 11              -> 3
 *   [2], 3                   -> -1
 *   [1], 0                   -> 0
 *   [1,3,4], 6               -> 2 (greedy picks 4+1+1 = 3 coins)
 *   [186,419,83,408], 6249   -> 20
 *
 * Approaches:
 *   1. Memoized recursion        O(amount * coins) time, O(amount) space
 *   2. BFS over amounts          O(amount * coins) time, O(amount) space
 *   3. Bottom-up DP  ⭐           O(amount * coins) time, O(amount) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
int fewest(const vector<int>& coins, int a, vector<int>& memo) {   // INT_MAX = impossible
    if (a == 0) return 0;
    if (memo[a] != -2) return memo[a];
    int best = INT_MAX;
    for (int c : coins)
        if (c <= a) {
            int sub = fewest(coins, a - c, memo);
            if (sub != INT_MAX) best = min(best, sub + 1);
        }
    return memo[a] = best;
}

int coinChangeMemo(const vector<int>& coins, int amount) {
    vector<int> memo(amount + 1, -2);             // -2 = not computed
    int r = fewest(coins, amount, memo);
    return r == INT_MAX ? -1 : r;
}

// ---------- Approach 2: BFS over Amounts ----------
int coinChangeBFS(const vector<int>& coins, int amount) {
    vector<bool> seen(amount + 1, false);
    queue<int> q;
    q.push(0);
    seen[0] = true;
    for (int steps = 0; !q.empty(); steps++) {    // level = number of coins used
        for (int sz = q.size(); sz > 0; sz--) {
            int a = q.front(); q.pop();
            if (a == amount) return steps;
            for (int c : coins)
                if (c <= amount - a && !seen[a + c]) { seen[a + c] = true; q.push(a + c); }   // not a + c <= amount: c can be 2^31-1
        }
    }
    return -1;
}

// ---------- Approach 3: Bottom-up DP ⭐ ----------
int coinChange(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);       // amount+1 acts as infinity (can't need more coins)
    dp[0] = 0;
    for (int a = 1; a <= amount; a++)
        for (int c : coins)
            if (c <= a) dp[a] = min(dp[a], dp[a - c] + 1);   // last coin is c
    return dp[amount] > amount ? -1 : dp[amount];
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 2, 5}, 11}, {{2}, 3}, {{1}, 0}, {{1, 3, 4}, 6}, {{186, 419, 83, 408}, 6249}
    };
    for (auto& [coins, amount] : tests) {
        cout << "memo: " << coinChangeMemo(coins, amount) << "\n";
        cout << "bfs : " << coinChangeBFS(coins, amount) << "\n";
        cout << "dp  : " << coinChange(coins, amount) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Using amount+1 as "infinity" keeps dp[a - c] + 1 overflow-free (INT_MAX + 1 would wrap).
 * - A sentinel like -2 separates "not computed" from the -1 / INT_MAX results.
 * - `for (int sz = q.size(); sz > 0; sz--)` processes one BFS level.
 */
