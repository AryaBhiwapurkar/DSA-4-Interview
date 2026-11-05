/*
 * 1851. Minimum Interval to Include Each Query  |  Hard  |  Intervals
 * Link: https://leetcode.com/problems/minimum-interval-to-include-each-query/
 *
 * Problem: For each query q, return the size (right - left + 1) of the smallest
 *          interval with left <= q <= right, or -1 if none contains q.
 *
 * Examples:
 *   [[1,4],[2,4],[3,6],[4,4]], [2,3,4,5]       -> [3,3,1,4]
 *   [[2,3],[2,5],[1,8],[20,25]], [2,19,5,22]   -> [2,-1,4,6]
 *   [[1,1]], [1,2]                             -> [1,-1]
 *   [[5,10]], [1,5,10,11]                      -> [-1,6,6,-1]
 *
 * Approaches:
 *   1. Brute force: scan all intervals per query        O(n*q) time, O(1) extra
 *   2. Offline: sorted queries + min-heap by size  ⭐    O((n+q) log(n+q)) time, O(n+q) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
vector<int> minIntervalBrute(const vector<vector<int>>& intervals, const vector<int>& queries) {
    vector<int> res;
    for (int q : queries) {
        int best = INT_MAX;
        for (auto& iv : intervals)
            if (iv[0] <= q && q <= iv[1]) best = min(best, iv[1] - iv[0] + 1);
        res.push_back(best == INT_MAX ? -1 : best);
    }
    return res;
}

// ---------- Approach 2: Sorted Queries + Min-heap ⭐ ----------
vector<int> minInterval(vector<vector<int>> intervals, const vector<int>& queries) {
    sort(intervals.begin(), intervals.end());      // by left end
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return queries[a] < queries[b]; });
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> heap;   // (size, right end)
    vector<int> res(queries.size(), -1);
    size_t i = 0;
    for (int idx : order) {
        int q = queries[idx];
        while (i < intervals.size() && intervals[i][0] <= q) {   // every interval starting by q
            heap.push({intervals[i][1] - intervals[i][0] + 1, intervals[i][1]});
            i++;
        }
        while (!heap.empty() && heap.top().second < q) heap.pop();   // ended before q: useless later too
        if (!heap.empty()) res[idx] = heap.top().first;
    }
    return res;
}

void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << v[i];
    cout << "]\n";
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<vector<int>>, vector<int>>> tests = {
        {{{1, 4}, {2, 4}, {3, 6}, {4, 4}}, {2, 3, 4, 5}},
        {{{2, 3}, {2, 5}, {1, 8}, {20, 25}}, {2, 19, 5, 22}},
        {{{1, 1}}, {1, 2}},
        {{{5, 10}}, {1, 5, 10, 11}},
    };
    for (auto& [intervals, queries] : tests) {
        cout << "brute: "; print(minIntervalBrute(intervals, queries));
        cout << "heap : "; print(minInterval(intervals, queries));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Sort an index array (iota + lambda) to process queries in order but answer in place.
 * - greater<> (transparent) turns priority_queue into a min-heap over pairs.
 * - [&] captures queries by reference inside the comparator.
 */
