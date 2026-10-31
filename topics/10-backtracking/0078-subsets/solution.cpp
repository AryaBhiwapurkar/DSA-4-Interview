/*
 * 0078. Subsets  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/subsets/
 *
 * Problem: Return the power set of an array of distinct integers.
 *
 * Examples:
 *   [1,2,3]  -> [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *   [0]      -> [[],[0]]
 *   [5,-1]   -> [[],[5],[-1],[5,-1]]
 *
 * Approaches:
 *   1. Iterative doubling    O(n * 2^n) time, O(n * 2^n) space
 *   2. Bitmask               O(n * 2^n) time, O(n) extra
 *   3. Backtracking  ⭐       O(n * 2^n) time, O(n) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Iterative Doubling ----------
vector<vector<int>> subsetsIter(const vector<int>& nums) {
    vector<vector<int>> res = {{}};
    for (int x : nums) {
        int sz = res.size();               // snapshot: res grows inside the loop
        for (int i = 0; i < sz; i++) {
            auto s = res[i];
            s.push_back(x);
            res.push_back(s);
        }
    }
    return res;
}

// ---------- Approach 2: Bitmask ----------
vector<vector<int>> subsetsBitmask(const vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> res;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> s;
        for (int j = 0; j < n; j++)
            if (mask >> j & 1) s.push_back(nums[j]);
        res.push_back(s);
    }
    return res;
}

// ---------- Approach 3: Backtracking ⭐ ----------
void dfs(const vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {
    res.push_back(path);                   // every node is a subset
    for (int i = start; i < (int)nums.size(); i++) {
        path.push_back(nums[i]);
        dfs(nums, i + 1, path, res);
        path.pop_back();
    }
}

vector<vector<int>> subsets(const vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    dfs(nums, 0, path, res);
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<int>> v) {
    sort(v.begin(), v.end());              // normalize: any order is accepted
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < v[i].size(); j++) cout << (j ? "," : "") << v[i][j];
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3}, {0}, {5, -1}};
    for (auto& nums : tests) {
        print("iter     ", subsetsIter(nums));
        print("bitmask  ", subsetsBitmask(nums));
        print("backtrack", subsets(nums));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `mask >> j & 1` tests bit j (>> binds tighter than &).
 * - `1 << n` is int: fine for n <= 30; use 1LL << n beyond that.
 * - vector<vector<int>> res = {{}} starts with one empty subset.
 */
