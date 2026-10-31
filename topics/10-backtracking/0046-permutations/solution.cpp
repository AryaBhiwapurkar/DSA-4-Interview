/*
 * 0046. Permutations  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/permutations/
 *
 * Problem: Return all orderings of an array of distinct integers.
 *
 * Examples:
 *   [1,2,3]  -> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *   [0,1]    -> [[0,1],[1,0]]
 *   [1]      -> [[1]]
 *   [-1,5]   -> [[-1,5],[5,-1]]
 *
 * Approaches:
 *   1. Backtracking with used[]  ⭐  O(n * n!) time, O(n) extra space   <- go-to
 *   2. In-place swapping            O(n * n!) time, O(n) recursion
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Backtracking with used[] ⭐ ----------
void dfs(const vector<int>& nums, vector<bool>& used, vector<int>& path, vector<vector<int>>& res) {
    if (path.size() == nums.size()) { res.push_back(path); return; }
    for (int i = 0; i < (int)nums.size(); i++) {   // from 0: order matters
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        dfs(nums, used, path, res);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permute(const vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    dfs(nums, used, path, res);
    return res;
}

// ---------- Approach 2: In-Place Swapping ----------
void swapPerm(vector<int>& a, int i, vector<vector<int>>& res) {
    if (i == (int)a.size()) { res.push_back(a); return; }
    for (int j = i; j < (int)a.size(); j++) {
        swap(a[i], a[j]);                  // put a[j] in slot i
        swapPerm(a, i + 1, res);
        swap(a[i], a[j]);                  // restore for the next j
    }
}

vector<vector<int>> permuteSwap(vector<int> nums) {
    vector<vector<int>> res;
    swapPerm(nums, 0, res);
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<int>> v) {
    sort(v.begin(), v.end());              // any order of permutations is accepted
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < v[i].size(); j++) cout << (j ? "," : "") << v[i][j];
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3}, {0, 1}, {1}, {-1, 5}};
    for (auto& nums : tests) {
        print("used", permute(nums));
        print("swap", permuteSwap(nums));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<bool> is bit-packed; fine for flags, but `auto& b = used[i]` is a proxy.
 * - std::swap(a[i], a[j]) swaps two elements in place.
 * - Library alternative: sort, then do { ... } while (next_permutation(a.begin(), a.end())).
 */
