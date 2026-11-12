/*
 * 0448. Find All Numbers Disappeared in an Array  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 *
 * Problem: Values are in 1..n (some repeated). Return every number in 1..n that's absent.
 *
 * Examples:
 *   [4,3,2,7,8,2,3,1]  -> [5,6]
 *   [1,1]              -> [2]
 *   [1,2,3]            -> []
 *   [1,1,1]            -> [2,3]
 *   [2,2]              -> [1]
 *
 * Approaches:
 *   1. Boolean "seen" array       O(n) time, O(n) space
 *   2. Negation marking  ⭐       O(n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Seen Array ----------
vector<int> findDisappearedNumbersSeen(const vector<int>& nums) {
    int n = nums.size();
    vector<bool> seen(n + 1, false);
    for (int x : nums) seen[x] = true;
    vector<int> out;
    for (int v = 1; v <= n; v++)
        if (!seen[v]) out.push_back(v);
    return out;
}

// ---------- Approach 2: Negation Marking ⭐ ----------
vector<int> findDisappearedNumbers(vector<int> nums) {
    for (int x : nums) {
        int j = abs(x) - 1;                        // x may already be negated
        if (nums[j] > 0) nums[j] = -nums[j];       // mark "j + 1 seen"
    }
    vector<int> out;
    for (int i = 0; i < (int)nums.size(); i++)
        if (nums[i] > 0) out.push_back(i + 1);
    return out;
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{4, 3, 2, 7, 8, 2, 3, 1}, {1, 1}, {1, 2, 3}, {1, 1, 1}, {2, 2}};
    for (auto& t : tests) {
        cout << "seen  : "; print(findDisappearedNumbersSeen(t));
        cout << "negate: "; print(findDisappearedNumbers(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Range-for over nums while writing nums[j]: the loop reads each element when it gets there,
 *   so values may already be negated; abs() recovers them.
 * - vector<bool> seen(n + 1) gives 1-based flags without index shifting.
 * - Taking nums by value leaves the caller's vector untouched.
 */
