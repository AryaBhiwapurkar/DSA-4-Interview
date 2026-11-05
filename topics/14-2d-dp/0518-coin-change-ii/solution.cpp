/*
 * 0518. Coin Change II  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/coin-change-ii/
 *
 * Problem: Count the combinations (order doesn't matter) of coins, unlimited
 *          supply each, that sum to amount.
 *
 * Examples:
 *   5, [1,2,5]   -> 4
 *   3, [2]       -> 0
 *   10, [10]     -> 1
 *   0, [7]       -> 1  (the empty combination)
 *   4, [1,2,3]   -> 4
 *
 * Approaches:
 *   1. Memoized recursion (coin index, amount)   O(n * amount) time, O(n * amount) space
 *   2. 2-D table                                O(n * amount) time, O(n * amount) space
 *   3. 1-D, coins outer / amounts inner  ⭐      O(n * amount) time, O(amount) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;   // intermediates can pass 2^31; unsigned wraparound is defined

// ---------- Approach 1: Memoized Recursion ----------
ull ways(const vector<int>& coins, int i, int a, vector<vector<ull>>& memo, vector<vector<bool>>& done) {
    if (a == 0) return 1;
    if (i == (int)coins.size() || a < 0) return 0;
    if (done[i][a]) return memo[i][a];
    done[i][a] = true;
    return memo[i][a] = ways(coins, i, a - coins[i], memo, done) + ways(coins, i + 1, a, memo, done);
}

int changeMemo(int amount, const vector<int>& coins) {
    int n = coins.size();
    vector<vector<ull>> memo(n, vector<ull>(amount + 1));
    vector<vector<bool>> done(n, vector<bool>(amount + 1, false));
    return (int)ways(coins, 0, amount, memo, done);
}

// ---------- Approach 2: 2-D Table ----------
int changeTable(int amount, const vector<int>& coins) {
    int n = coins.size();
    vector<vector<ull>> dp(n + 1, vector<ull>(amount + 1, 0));   // dp[i][a]: first i coins
    for (int i = 0; i <= n; i++) dp[i][0] = 1;
    for (int i = 1; i <= n; i++) {
        int c = coins[i - 1];
        for (int a = 1; a <= amount; a++)
            dp[i][a] = dp[i - 1][a] + (a >= c ? dp[i][a - c] : 0);   // skip c / use c again
    }
    return (int)dp[n][amount];
}

// ---------- Approach 3: 1-D ⭐ ----------
int change(int amount, const vector<int>& coins) {
    vector<ull> dp(amount + 1, 0);
    dp[0] = 1;
    for (int c : coins)                            // coins outside: combinations, not orderings
        for (int a = c; a <= amount; a++)          // ascending: coin c reusable
            dp[a] += dp[a - c];
    return (int)dp[amount];
}

// ---------- Driver ----------
int main() {
    vector<pair<int, vector<int>>> tests = {{5, {1, 2, 5}}, {3, {2}}, {10, {10}}, {0, {7}}, {4, {1, 2, 3}}};
    for (auto& [amount, coins] : tests) {
        cout << "memo : " << changeMemo(amount, coins) << "\n";
        cout << "table: " << changeTable(amount, coins) << "\n";
        cout << "1-D  : " << change(amount, coins) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Signed overflow is undefined behaviour; unsigned overflow wraps, and the final
 *   answer (< 2^31) is still exact because only additions are involved.
 * - `using ull = unsigned long long;` is a type alias.
 * - `for (int a = c; ...)` starts at the coin value, so a - c >= 0.
 */
