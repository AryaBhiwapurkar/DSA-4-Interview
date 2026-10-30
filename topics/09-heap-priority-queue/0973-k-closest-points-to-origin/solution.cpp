/*
 * 0973. K Closest Points to Origin  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/k-closest-points-to-origin/
 *
 * Problem: Return the k points closest to (0,0). Any order.
 *
 * Examples (printed sorted):
 *   [[1,3],[-2,2]],          k 1  -> [[-2,2]]
 *   [[3,3],[5,-1],[-2,4]],   k 2  -> [[-2,4],[3,3]]
 *   [[0,1],[1,0]],           k 2  -> [[0,1],[1,0]]
 *
 * Approaches:
 *   1. Sort by distance         O(n log n) time, O(n) space
 *   2. Max-heap of size k  ⭐    O(n log k) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

int d2(const vector<int>& p) { return p[0] * p[0] + p[1] * p[1]; }   // <= 2e8: fits int

// ---------- Approach 1: Sort by Distance ----------
vector<vector<int>> kClosestSort(vector<vector<int>> pts, int k) {
    sort(pts.begin(), pts.end(), [](auto& a, auto& b) { return d2(a) < d2(b); });
    return vector<vector<int>>(pts.begin(), pts.begin() + k);
}

// ---------- Approach 2: Max-Heap of Size k ⭐ ----------
vector<vector<int>> kClosest(const vector<vector<int>>& points, int k) {
    priority_queue<pair<int, int>> pq;     // (distance^2, index), max on top
    for (int i = 0; i < (int)points.size(); i++) {
        pq.push({d2(points[i]), i});
        if ((int)pq.size() > k) pq.pop();  // evict the farthest of the current k
    }
    vector<vector<int>> res;
    for (; !pq.empty(); pq.pop()) res.push_back(points[pq.top().second]);
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<int>> v) {
    sort(v.begin(), v.end());              // normalize: any order is accepted
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << "[" << v[i][0] << "," << v[i][1] << "]";
    cout << "]\n";
}

int main() {
    vector<pair<vector<vector<int>>, int>> tests = {
        {{{1, 3}, {-2, 2}}, 1}, {{{3, 3}, {5, -1}, {-2, 4}}, 2}, {{{0, 1}, {1, 0}}, 2}
    };
    for (auto& [pts, k] : tests) {
        print("sort", kClosestSort(pts, k));
        print("heap", kClosest(pts, k));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - priority_queue<pair<int,int>> is a max-heap ordered by .first.
 * - Generic lambda `[](auto& a, auto& b)` as a sort comparator.
 * - `for (; !pq.empty(); pq.pop())` drains a heap.
 */
