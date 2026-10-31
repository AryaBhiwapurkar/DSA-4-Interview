/*
 * 0040. Combination Sum II  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/combination-sum-ii/
 *
 * Problem: Positive candidates (with duplicates), a target. Return every
 *          unique combination summing to target, each element used once.
 *
 * Examples:
 *   [10,1,2,7,6,1,5], 8  -> [[1,1,6],[1,2,5],[1,7],[2,6]]
 *   [2,5,2,1,2],      5  -> [[1,2,2],[5]]
 *   [2,2,2],          4  -> [[2,2]]
 *   [3],              1  -> []
 *
 * Approaches:
 *   1. All subsets + set           O(2^n * n log n) time, O(2^n * n) space
 *   2. Sort + skip duplicates  ⭐   O(2^n * n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Subsets + Set ----------
void allSubsets(const vector<int>& c, int i, int rem, vector<int>& path, set<vector<int>>& seen) {
    if (rem == 0) { seen.insert(path); return; }   // path built in sorted order
    if (i == (int)c.size() || rem < 0) return;
    path.push_back(c[i]);
    allSubsets(c, i + 1, rem - c[i], path, seen);
    path.pop_back();
    allSubsets(c, i + 1, rem, path, seen);
}

vector<vector<int>> combinationSum2Set(vector<int> candidates, int target) {
    sort(candidates.begin(), candidates.end());
    set<vector<int>> seen;
    vector<int> path;
    allSubsets(candidates, 0, target, path, seen);
    return vector<vector<int>>(seen.begin(), seen.end());
}

// ---------- Approach 2: Sort + Skip Duplicates ⭐ ----------
void dfs(const vector<int>& c, int start, int rem, vector<int>& path, vector<vector<int>>& res) {
    if (rem == 0) { res.push_back(path); return; }
    for (int i = start; i < (int)c.size(); i++) {
        if (i > start && c[i] == c[i - 1]) continue;   // same value, same depth: already explored
        if (c[i] > rem) break;
        path.push_back(c[i]);
        dfs(c, i + 1, rem - c[i], path, res);          // i + 1: each element once
        path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int> candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int> path;
    dfs(candidates, 0, target, path, res);
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<int>> v) {
    for (auto& x : v) sort(x.begin(), x.end());
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
    vector<pair<vector<int>, int>> tests = {
        {{10, 1, 2, 7, 6, 1, 5}, 8}, {{2, 5, 2, 1, 2}, 5}, {{2, 2, 2}, 4}, {{3}, 1}
    };
    for (auto& [c, t] : tests) {
        print("set ", combinationSum2Set(c, t));
        print("skip", combinationSum2(c, t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - set<vector<int>> dedupes whole vectors (lexicographic <).
 * - vector<vector<int>>(s.begin(), s.end()) converts a set to a vector.
 * - `continue` skips one candidate; `break` abandons the rest (sorted).
 */
