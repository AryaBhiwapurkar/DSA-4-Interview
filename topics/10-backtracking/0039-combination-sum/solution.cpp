/*
 * 0039. Combination Sum  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/combination-sum/
 *
 * Problem: Distinct positive candidates, a target. Return every unique
 *          multiset of candidates (unlimited reuse) summing to target.
 *
 * Examples:
 *   [2,3,6,7], 7  -> [[2,2,3],[7]]
 *   [2,3,5],   8  -> [[2,2,2,2],[2,3,3],[3,5]]
 *   [2],       1  -> []
 *   [7,3,2],  18  -> 7 combinations (unsorted input)
 *
 * Approaches:
 *   1. Include / exclude                O(2^(n+T/m)) time, O(n+T/m) space
 *   2. Sorted loop from start  ⭐        O(n^(T/m+1)) time, O(T/m) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Include / Exclude ----------
void pickOrSkip(const vector<int>& c, int i, int rem, vector<int>& path, vector<vector<int>>& res) {
    if (rem == 0) { res.push_back(path); return; }
    if (i == (int)c.size() || rem < 0) return;
    path.push_back(c[i]);
    pickOrSkip(c, i, rem - c[i], path, res);   // use c[i] again
    path.pop_back();
    pickOrSkip(c, i + 1, rem, path, res);      // never use c[i] again
}

vector<vector<int>> combinationSumBinary(const vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> path;
    pickOrSkip(candidates, 0, target, path, res);
    return res;
}

// ---------- Approach 2: Sorted Loop from Start Index ⭐ ----------
void dfs(const vector<int>& c, int start, int rem, vector<int>& path, vector<vector<int>>& res) {
    if (rem == 0) { res.push_back(path); return; }
    for (int i = start; i < (int)c.size(); i++) {
        if (c[i] > rem) break;             // sorted: everything after is bigger too
        path.push_back(c[i]);
        dfs(c, i, rem - c[i], path, res);  // i, not i + 1: reuse allowed
        path.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int> candidates, int target) {
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
    vector<pair<vector<int>, int>> tests = {{{2, 3, 6, 7}, 7}, {{2, 3, 5}, 8}, {{2}, 1}, {{7, 3, 2}, 18}};
    for (auto& [c, t] : tests) {
        print("binary", combinationSumBinary(c, t));
        print("loop  ", combinationSum(c, t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - res.push_back(path) copies the vector, so later pops don't affect it.
 * - Taking `candidates` by value lets the go-to sort its own copy.
 * - sort() on vector<vector<int>> compares lexicographically.
 */
