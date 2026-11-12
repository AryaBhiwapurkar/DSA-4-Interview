/*
 * 0862. Shortest Subarray with Sum at Least K  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
 *
 * Problem: Length of the shortest subarray with sum >= k (negatives allowed), or -1.
 *
 * Examples:
 *   [1],          k = 1   -> 1
 *   [1,2],        k = 4   -> -1
 *   [2,-1,2],     k = 3   -> 3
 *   [84,-37,32,40,95], k = 167 -> 3
 *   [-28,81,-20,28,-29], k = 89 -> 3
 *
 * Approaches:
 *   1. All pairs of prefixes             O(n^2) time, O(n) space
 *   2. Monotonic deque on prefixes  ⭐   O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Pairs ----------
int shortestSubarrayBrute(const vector<int>& nums, int k) {
    int n = nums.size(), best = INT_MAX;
    for (int i = 0; i < n; i++) {
        long long s = 0;
        for (int j = i; j < n; j++) {
            s += nums[j];
            if (s >= k) { best = min(best, j - i + 1); break; }
        }
    }
    return best == INT_MAX ? -1 : best;
}

// ---------- Approach 2: Monotonic Deque ⭐ ----------
int shortestSubarray(const vector<int>& nums, int k) {
    int n = nums.size(), best = INT_MAX;
    vector<long long> P(n + 1, 0);                 // up to 1e10: needs 64-bit
    for (int i = 0; i < n; i++) P[i + 1] = P[i] + nums[i];
    deque<int> dq;                                 // start indices, P increasing
    for (int j = 0; j <= n; j++) {
        while (!dq.empty() && P[j] - P[dq.front()] >= k) {
            best = min(best, j - dq.front());      // later j can't beat this start
            dq.pop_front();
        }
        while (!dq.empty() && P[dq.back()] >= P[j]) dq.pop_back();   // j dominates
        dq.push_back(j);
    }
    return best == INT_MAX ? -1 : best;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1}, 1}, {{1, 2}, 4}, {{2, -1, 2}, 3}, {{84, -37, 32, 40, 95}, 167}, {{-28, 81, -20, 28, -29}, 89}};
    for (auto& [nums, k] : tests) {
        cout << "brute: " << shortestSubarrayBrute(nums, k) << "\n";
        cout << "deque: " << shortestSubarray(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::deque supports push/pop at both ends in O(1): front(), back(), pop_front(), pop_back().
 * - vector<long long> for prefix sums that can exceed 2^31.
 * - INT_MAX as "no answer yet", mapped to -1 at the end.
 */
