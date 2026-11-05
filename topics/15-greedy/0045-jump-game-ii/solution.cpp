/*
 * 0045. Jump Game II  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/jump-game-ii/
 *
 * Problem: Minimum number of jumps from index 0 to the last index (always
 *          reachable), where nums[i] is the max jump from i.
 *
 * Examples:
 *   [2,3,1,1,4]   -> 2
 *   [2,3,0,1,4]   -> 2
 *   [0]           -> 0
 *   [1,1,1,1]     -> 3
 *   [5,1,1,1,1]   -> 1
 *
 * Approaches:
 *   1. DP: fewest jumps to each index    O(n^2) time, O(n) space
 *   2. BFS-style levels (greedy)  ⭐      O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DP ----------
int jumpDP(const vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, n);                          // n acts as infinity
    dp[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= min(n - 1, i + nums[i]); j++) dp[j] = min(dp[j], dp[i] + 1);
    return dp[n - 1];
}

// ---------- Approach 2: BFS Levels ⭐ ----------
int jump(const vector<int>& nums) {
    int jumps = 0, end = 0, farthest = 0;          // [.., end] reachable with `jumps` jumps
    for (int i = 0; i + 1 < (int)nums.size(); i++) {   // never jump from the last index
        farthest = max(farthest, i + nums[i]);
        if (i == end) {                            // level done: one more jump opens the next
            jumps++;
            end = farthest;
        }
    }
    return jumps;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 3, 1, 1, 4}, {2, 3, 0, 1, 4}, {0}, {1, 1, 1, 1}, {5, 1, 1, 1, 1}};
    for (auto& t : tests) {
        cout << "dp : " << jumpDP(t) << "\n";
        cout << "bfs: " << jump(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `i + 1 < (int)nums.size()` avoids size_t underflow and skips the last index.
 * - vector<int> dp(n, n) fills with a value larger than any real answer.
 * - The window [start, end] is implicit: start is the previous end + 1.
 */
