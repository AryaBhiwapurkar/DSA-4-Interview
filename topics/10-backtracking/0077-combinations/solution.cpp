/*
 * 0077. Combinations  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/combinations/
 *
 * Problem: Return all ways to choose k numbers from 1..n.
 *
 * Examples:
 *   n 4, k 2  -> [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *   n 1, k 1  -> [[1]]
 *   n 3, k 3  -> [[1,2,3]]
 *   n 5, k 3  -> 10 combinations
 *
 * Approaches:
 *   1. Include / exclude                 O(2^n) time, O(n) space
 *   2. Start-index loop + prune  ⭐       O(k * C(n,k)) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Include / Exclude ----------
void pickOrSkip(int x, int n, int k, vector<int>& path, vector<vector<int>>& res) {
    if ((int)path.size() == k) { res.push_back(path); return; }
    if (x > n) return;
    path.push_back(x);
    pickOrSkip(x + 1, n, k, path, res);
    path.pop_back();
    pickOrSkip(x + 1, n, k, path, res);
}

vector<vector<int>> combineBinary(int n, int k) {
    vector<vector<int>> res;
    vector<int> path;
    pickOrSkip(1, n, k, path, res);
    return res;
}

// ---------- Approach 2: Start-Index Loop + Prune ⭐ ----------
void dfs(int start, int n, int k, vector<int>& path, vector<vector<int>>& res) {
    if ((int)path.size() == k) { res.push_back(path); return; }
    int need = k - path.size();
    for (int i = start; i <= n - need + 1; i++) {   // enough numbers must remain
        path.push_back(i);
        dfs(i + 1, n, k, path, res);
        path.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> path;
    dfs(1, n, k, path, res);
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
    vector<pair<int, int>> tests = {{4, 2}, {1, 1}, {3, 3}, {5, 3}};
    for (auto [n, k] : tests) {
        print("binary", combineBinary(n, k));
        print("prune ", combine(n, k));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `int need = k - path.size();` converts size_t to int implicitly; fine for small sizes.
 * - `for (auto [n, k] : tests)` copies each pair (cheap for two ints).
 */
