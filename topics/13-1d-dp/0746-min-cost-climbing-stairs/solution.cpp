/*
 * 0746. Min Cost Climbing Stairs  |  Easy  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/min-cost-climbing-stairs/
 *
 * Problem: cost[i] is paid when you step on stair i; then you climb 1 or 2.
 *          Start at index 0 or 1. Min cost to get past the last stair.
 *
 * Examples:
 *   [10,15,20]                       -> 15
 *   [1,100,1,1,1,100,1,1,100,1]      -> 6
 *   [0,0]                            -> 0
 *   [5,3]                            -> 3
 *
 * Approaches:
 *   1. Memoized recursion            O(n) time, O(n) space
 *   2. Two variables (bottom-up)  ⭐  O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
// reach(i) = min cost to stand on i (before paying cost[i]).
int reach(int i, const vector<int>& cost, vector<int>& memo) {
    if (i <= 1) return 0;                         // starting on 0 or 1 is free
    if (memo[i] != -1) return memo[i];
    return memo[i] = min(reach(i - 1, cost, memo) + cost[i - 1],
                         reach(i - 2, cost, memo) + cost[i - 2]);
}

int minCostClimbingStairsMemo(const vector<int>& cost) {
    int n = cost.size();
    vector<int> memo(n + 1, -1);
    return reach(n, cost, memo);                  // the top is index n
}

// ---------- Approach 2: Two Variables ⭐ ----------
int minCostClimbingStairs(const vector<int>& cost) {
    int a = 0, b = 0;                             // reach(i-2), reach(i-1)
    for (int i = 2; i <= (int)cost.size(); i++) {
        int c = min(b + cost[i - 1], a + cost[i - 2]);
        a = b;
        b = c;
    }
    return b;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{10, 15, 20}, {1, 100, 1, 1, 1, 100, 1, 1, 100, 1}, {0, 0}, {5, 3}};
    for (auto& c : tests) {
        cout << "memo: " << minCostClimbingStairsMemo(c) << "\n";
        cout << "dp  : " << minCostClimbingStairs(c) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - memo filled with -1 marks "not computed" (0 is a valid cost here).
 * - `min(x, y)` needs both arguments of the same type (both int here).
 * - Rolling variables a, b, c replace a dp array of size n+1.
 */
