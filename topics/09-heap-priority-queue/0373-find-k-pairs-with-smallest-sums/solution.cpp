/*
 * 0373. Find K Pairs with Smallest Sums  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
 *
 * Problem: Two ascending arrays; return the k pairs (u, v) with the
 *          smallest sums u + v.
 *
 * Examples:
 *   [1,7,11], [2,4,6], k 3   -> [[1,2],[1,4],[1,6]]
 *   [1,1,2],  [1,2,3], k 2   -> [[1,1],[1,1]]
 *   [1,2],    [3],     k 3   -> [[1,3],[2,3]]   (k > number of pairs)
 *
 * Approaches:
 *   1. All pairs, sort           O(m*n log(m*n)) time, O(m*n) space
 *   2. Min-heap frontier  ⭐      O(k log k) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Pairs, Sort ----------
vector<vector<int>> kSmallestPairsBrute(const vector<int>& a, const vector<int>& b, int k) {
    vector<tuple<int, int, int>> all;      // (sum, i, j): ties broken by index
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++) all.push_back({a[i] + b[j], i, j});
    sort(all.begin(), all.end());
    vector<vector<int>> res;
    for (int t = 0; t < k && t < (int)all.size(); t++) {
        auto [s, i, j] = all[t];
        res.push_back({a[i], b[j]});
    }
    return res;
}

// ---------- Approach 2: Min-Heap Frontier ⭐ ----------
vector<vector<int>> kSmallestPairs(const vector<int>& a, const vector<int>& b, int k) {
    using T = tuple<int, int, int>;        // (sum, i, j)
    priority_queue<T, vector<T>, greater<T>> pq;
    for (int i = 0; i < min(k, (int)a.size()); i++) pq.push({a[i] + b[0], i, 0});   // head of each row
    vector<vector<int>> res;
    while (!pq.empty() && (int)res.size() < k) {
        auto [s, i, j] = pq.top();
        pq.pop();
        res.push_back({a[i], b[j]});
        if (j + 1 < (int)b.size()) pq.push({a[i] + b[j + 1], i, j + 1});   // move right in row i
    }
    return res;
}

// ---------- Driver ----------
void print(const string& label, const vector<vector<int>>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << "[" << v[i][0] << "," << v[i][1] << "]";
    cout << "]\n";
}

int main() {
    vector<tuple<vector<int>, vector<int>, int>> tests = {
        {{1, 7, 11}, {2, 4, 6}, 3}, {{1, 1, 2}, {1, 2, 3}, 2}, {{1, 2}, {3}, 3}
    };
    for (auto& [a, b, k] : tests) {
        print("brute", kSmallestPairsBrute(a, b, k));
        print("heap ", kSmallestPairs(a, b, k));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `using T = tuple<...>` shortens the priority_queue declaration.
 * - greater<T> makes a min-heap over tuples (compares sum, then i, then j).
 */
