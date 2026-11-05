/*
 * 0057. Insert Interval  |  Medium  |  Intervals
 * Link: https://leetcode.com/problems/insert-interval/
 *
 * Problem: Insert newInterval into a sorted, non-overlapping list, merging as
 *          needed so the result stays sorted and non-overlapping.
 *
 * Examples:
 *   [[1,3],[6,9]], [2,5]                        -> [[1,5],[6,9]]
 *   [[1,2],[3,5],[6,7],[8,10],[12,16]], [4,8]   -> [[1,2],[3,10],[12,16]]
 *   [], [5,7]                                   -> [[5,7]]
 *   [[1,5]], [6,8]                              -> [[1,5],[6,8]]
 *   [[3,5]], [1,2]                              -> [[1,2],[3,5]]
 *
 * Approaches:
 *   1. Append + sort + merge (LC 56)       O(n log n) time, O(n) space
 *   2. Three phases: before, overlap, after  ⭐   O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Append + Sort + Merge ----------
vector<vector<int>> insertSort(vector<vector<int>> intervals, const vector<int>& nw) {
    intervals.push_back(nw);
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    for (auto& iv : intervals) {
        if (!res.empty() && iv[0] <= res.back()[1]) res.back()[1] = max(res.back()[1], iv[1]);
        else res.push_back(iv);
    }
    return res;
}

// ---------- Approach 2: Three Phases ⭐ ----------
vector<vector<int>> insert(const vector<vector<int>>& intervals, const vector<int>& nw) {
    vector<vector<int>> res;
    size_t i = 0, n = intervals.size();
    int s = nw[0], e = nw[1];
    while (i < n && intervals[i][1] < s) res.push_back(intervals[i++]);   // entirely before
    while (i < n && intervals[i][0] <= e) {        // overlaps: absorb
        s = min(s, intervals[i][0]);
        e = max(e, intervals[i][1]);
        i++;
    }
    res.push_back({s, e});
    while (i < n) res.push_back(intervals[i++]);   // entirely after
    return res;
}

void print(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << "[" << v[i][0] << ", " << v[i][1] << "]";
    cout << "]\n";
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<vector<int>>, vector<int>>> tests = {
        {{{1, 3}, {6, 9}}, {2, 5}},
        {{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}},
        {{}, {5, 7}},
        {{{1, 5}}, {6, 8}},
        {{{3, 5}}, {1, 2}},
    };
    for (auto& [intervals, nw] : tests) {
        cout << "sort  : "; print(insertSort(intervals, nw));
        cout << "phases: "; print(insert(intervals, nw));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `new` is a keyword, so the parameter is named `nw`.
 * - intervals[i++] uses the current element, then advances i.
 * - Each while loop resumes where the previous one stopped (shared index i).
 */
