/*
 * 0090. Subsets II  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/subsets-ii/
 *
 * Problem: Return all distinct subsets of an array that may contain duplicates.
 *
 * Examples:
 *   [1,2,2]      -> [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *   [0]          -> [[],[0]]
 *   [4,4,4,1,4]  -> 10 subsets
 *
 * Approaches:
 *   1. Power set + set             O(n^2 * 2^n) time, O(n * 2^n) space
 *   2. Sort + skip duplicates  ⭐   O(n * 2^n) time, O(n) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Power Set + Set ----------
vector<vector<int>> subsetsWithDupSet(vector<int> nums) {
    sort(nums.begin(), nums.end());        // equal subsets then look identical
    int n = nums.size();
    set<vector<int>> seen;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> s;
        for (int j = 0; j < n; j++) if (mask >> j & 1) s.push_back(nums[j]);
        seen.insert(s);
    }
    return vector<vector<int>>(seen.begin(), seen.end());
}

// ---------- Approach 2: Sort + Skip Duplicates ⭐ ----------
void dfs(const vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {
    res.push_back(path);
    for (int i = start; i < (int)nums.size(); i++) {
        if (i > start && nums[i] == nums[i - 1]) continue;   // same value at the same depth
        path.push_back(nums[i]);
        dfs(nums, i + 1, path, res);
        path.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int> nums) {
    sort(nums.begin(), nums.end());
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
    vector<vector<int>> tests = {{1, 2, 2}, {0}, {4, 4, 4, 1, 4}};
    for (auto& nums : tests) {
        print("set ", subsetsWithDupSet(nums));
        print("skip", subsetsWithDup(nums));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - set<vector<int>> keeps unique vectors in lexicographic order.
 * - Pass-by-value + sort gives each function its own sorted copy.
 */
