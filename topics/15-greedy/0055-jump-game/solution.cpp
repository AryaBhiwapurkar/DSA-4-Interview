/*
 * 0055. Jump Game  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/jump-game/
 *
 * Problem: nums[i] is the max jump length from i. Starting at index 0, can you
 *          reach the last index?
 *
 * Examples:
 *   [2,3,1,1,4]   -> true
 *   [3,2,1,0,4]   -> false
 *   [0]           -> true
 *   [2,0,0]       -> true
 *   [1,0,1]       -> false
 *
 * Approaches:
 *   1. DP from the right (can reach end?)   O(n^2) time, O(n) space
 *   2. Farthest reach, forward  ⭐           O(n) time, O(1) space   <- go-to
 *   3. Shrinking goal, backward             O(n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: DP from the Right ----------
bool canJumpDP(const vector<int>& nums) {
    int n = nums.size();
    vector<bool> good(n, false);
    good[n - 1] = true;
    for (int i = n - 2; i >= 0; i--)
        for (int j = i + 1; j <= min(n - 1, i + nums[i]) && !good[i]; j++)
            if (good[j]) good[i] = true;
    return good[0];
}

// ---------- Approach 2: Farthest Reach ⭐ ----------
bool canJump(const vector<int>& nums) {
    int reach = 0;                                 // farthest index reachable so far
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > reach) return false;               // stuck: i can't be reached
        reach = max(reach, i + nums[i]);
    }
    return true;
}

// ---------- Approach 3: Shrinking Goal ----------
bool canJumpGoal(const vector<int>& nums) {
    int goal = nums.size() - 1;
    for (int i = goal - 1; i >= 0; i--)
        if (i + nums[i] >= goal) goal = i;         // reaching i is now enough
    return goal == 0;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 3, 1, 1, 4}, {3, 2, 1, 0, 4}, {0}, {2, 0, 0}, {1, 0, 1}};
    cout << boolalpha;
    for (auto& t : tests) {
        cout << "dp   : " << canJumpDP(t) << "\n";
        cout << "reach: " << canJump(t) << "\n";
        cout << "goal : " << canJumpGoal(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `&& !good[i]` in the loop condition stops scanning once a good jump is found.
 * - i + nums[i] ≤ 10^4 + 10^5 here, so int is safe.
 * - cout << boolalpha prints true/false.
 */
