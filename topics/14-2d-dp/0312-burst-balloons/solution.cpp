/*
 * 0312. Burst Balloons  |  Hard  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/burst-balloons/
 *
 * Problem: Bursting balloon i earns left * nums[i] * right, where left/right are
 *          its current neighbours (1 past either end). Maximise the total.
 *
 * Examples:
 *   [3,1,5,8]      -> 167
 *   [1,5]          -> 10
 *   [7]            -> 7
 *   [9,76,64,21]   -> 116718
 *
 * Approaches:
 *   1. Brute force over burst orders              O(n!) time, O(n) space
 *   2. Interval memo, k = LAST balloon burst  ⭐   O(n^3) time, O(n^2) space   <- go-to
 *   3. Bottom-up by interval length               O(n^3) time, O(n^2) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int maxCoinsBrute(vector<int> arr) {
    int best = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
        int left = i > 0 ? arr[i - 1] : 1, right = i + 1 < (int)arr.size() ? arr[i + 1] : 1;
        vector<int> rest = arr;
        rest.erase(rest.begin() + i);
        best = max(best, left * arr[i] * right + maxCoinsBrute(rest));
    }
    return best;
}

// ---------- Approach 2: Interval Memo ⭐ ----------
int best(const vector<int>& a, int l, int r, vector<vector<int>>& memo) {   // open interval (l, r)
    if (memo[l][r] != -1) return memo[l][r];
    int res = 0;
    for (int k = l + 1; k < r; k++)               // k is the last balloon burst inside (l, r)
        res = max(res, a[l] * a[k] * a[r] + best(a, l, k, memo) + best(a, k, r, memo));
    return memo[l][r] = res;
}

int maxCoins(const vector<int>& nums) {
    vector<int> a = {1};
    a.insert(a.end(), nums.begin(), nums.end());
    a.push_back(1);                                // padded with virtual 1s
    int n = a.size();
    vector<vector<int>> memo(n, vector<int>(n, -1));
    return best(a, 0, n - 1, memo);
}

// ---------- Approach 3: Bottom-up ----------
int maxCoinsTable(const vector<int>& nums) {
    vector<int> a = {1};
    a.insert(a.end(), nums.begin(), nums.end());
    a.push_back(1);
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len < n; len++)              // short intervals first
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            for (int k = l + 1; k < r; k++)
                dp[l][r] = max(dp[l][r], a[l] * a[k] * a[r] + dp[l][k] + dp[k][r]);
        }
    return dp[0][n - 1];
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{3, 1, 5, 8}, {1, 5}, {7}, {9, 76, 64, 21}};
    for (auto& t : tests) {
        cout << "brute: " << maxCoinsBrute(t) << "\n";
        cout << "memo : " << maxCoins(t) << "\n";
        cout << "table: " << maxCoinsTable(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - a.insert(a.end(), b.begin(), b.end()) appends a whole vector.
 * - Passing `vector<int> arr` by value gives the brute force its own copy to erase from.
 * - Values ≤ 100 and n ≤ 300: 100^3 per burst, and totals stay well within int.
 */
