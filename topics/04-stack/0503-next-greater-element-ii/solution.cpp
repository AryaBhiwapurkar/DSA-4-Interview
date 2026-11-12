/*
 * 0503. Next Greater Element II  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/next-greater-element-ii/
 *
 * Problem: Circular array: for each element, the first strictly larger value moving
 *          forward (wrapping once), or -1.
 *
 * Examples:
 *   [1,2,1]        -> [2,-1,2]
 *   [1,2,3,4,3]    -> [2,3,4,-1,4]
 *   [5,5,5]        -> [-1,-1,-1]
 *   [3,1,2]        -> [-1,2,3]
 *
 * Approaches:
 *   1. Scan forward per element          O(n^2) time, O(1) space
 *   2. Two-pass monotonic stack  ⭐      O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Scan per Element ----------
vector<int> nextGreaterElementsBrute(const vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++)
        for (int d = 1; d < n; d++)
            if (nums[(i + d) % n] > nums[i]) { ans[i] = nums[(i + d) % n]; break; }
    return ans;
}

// ---------- Approach 2: Two-pass Stack ⭐ ----------
vector<int> nextGreaterElements(const vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1), st;                    // st holds indices still waiting
    for (int i = 0; i < 2 * n; i++) {
        int x = nums[i % n];                       // second lap simulates the wrap
        while (!st.empty() && nums[st.back()] < x) {
            ans[st.back()] = x;
            st.pop_back();
        }
        if (i < n) st.push_back(i);                // push each index once
    }
    return ans;
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 1}, {1, 2, 3, 4, 3}, {5, 5, 5}, {3, 1, 2}};
    for (auto& t : tests) {
        cout << "brute: "; print(nextGreaterElementsBrute(t));
        cout << "stack: "; print(nextGreaterElements(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<int> ans(n, -1), st; declares two vectors in one statement (st starts empty).
 * - i % n folds the second pass back onto the array.
 * - Store indices so duplicate values are distinguished.
 */
