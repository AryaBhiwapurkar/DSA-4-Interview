/*
 * 0070. Climbing Stairs  |  Easy  |  1-D Dynamic Programming
 * Link: https://leetcode.com/problems/climbing-stairs/
 *
 * Problem: Climb n steps taking 1 or 2 at a time. Count the distinct ways.
 *
 * Examples:
 *   n = 2   -> 2
 *   n = 3   -> 3
 *   n = 1   -> 1
 *   n = 5   -> 8
 *   n = 10  -> 89
 *
 * Approaches:
 *   1. Plain recursion            O(2^n) time, O(n) space
 *   2. Memoized recursion         O(n) time, O(n) space
 *   3. Two variables (bottom-up)  ⭐  O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Plain Recursion ----------
int climbStairsBrute(int n) {
    if (n <= 2) return n;                         // 1 way for 1 step, 2 ways for 2
    return climbStairsBrute(n - 1) + climbStairsBrute(n - 2);
}

// ---------- Approach 2: Memoized Recursion ----------
int ways(int n, vector<int>& memo) {
    if (n <= 2) return n;
    if (memo[n]) return memo[n];
    return memo[n] = ways(n - 1, memo) + ways(n - 2, memo);
}

int climbStairsMemo(int n) {
    vector<int> memo(n + 1, 0);
    return ways(n, memo);
}

// ---------- Approach 3: Two Variables ⭐ ----------
int climbStairs(int n) {
    int prev = 1, cur = 1;                        // ways(0), ways(1)
    for (int i = 2; i <= n; i++) {
        int next = prev + cur;                    // last move was a 2-step or a 1-step
        prev = cur;
        cur = next;
    }
    return cur;
}

// ---------- Driver ----------
int main() {
    for (int n : {2, 3, 1, 5, 10}) {
        cout << "brute: " << climbStairsBrute(n) << "\n";
        cout << "memo : " << climbStairsMemo(n) << "\n";
        cout << "dp   : " << climbStairs(n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `return memo[n] = ...;` stores and returns in one expression.
 * - `for (int n : {2, 3, 1, 5})` loops over an initializer_list.
 * - ways(45) = 1,836,311,903 still fits in int (LC caps n at 45).
 */
