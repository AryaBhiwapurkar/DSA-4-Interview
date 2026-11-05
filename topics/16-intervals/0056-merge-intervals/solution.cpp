/*
 * 0056. Merge Intervals  |  Medium  |  Intervals
 * Link: https://leetcode.com/problems/merge-intervals/
 *
 * Problem: Merge all overlapping intervals and return the result.
 *
 * Examples:
 *   [[1,3],[2,6],[8,10],[15,18]]   -> [[1,6],[8,10],[15,18]]
 *   [[1,4],[4,5]]                  -> [[1,5]]
 *   [[4,7],[1,4]]                  -> [[1,7]]
 *   [[1,4],[2,3]]                  -> [[1,4]]   (one inside another)
 *   [[5,6]]                        -> [[5,6]]
 *
 * Approaches:
 *   1. Repeatedly merge any overlapping pair   O(n^3) time, O(n) space
 *   2. Sort by start + one merge pass  ⭐       O(n log n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Repeated Pair Merging ----------
vector<vector<int>> mergeBrute(vector<vector<int>> res) {
    bool merged = true;
    while (merged) {                               // until no pair overlaps
        merged = false;
        for (size_t i = 0; i < res.size() && !merged; i++)
            for (size_t j = i + 1; j < res.size() && !merged; j++)
                if (res[i][0] <= res[j][1] && res[j][0] <= res[i][1]) {   // overlap (touching counts)
                    res[i] = {min(res[i][0], res[j][0]), max(res[i][1], res[j][1])};
                    res.erase(res.begin() + j);
                    merged = true;
                }
    }
    sort(res.begin(), res.end());
    return res;
}

// ---------- Approach 2: Sort + Merge ⭐ ----------
vector<vector<int>> merge(vector<vector<int>> intervals) {
    sort(intervals.begin(), intervals.end());      // by start
    vector<vector<int>> res;
    for (auto& iv : intervals) {
        if (!res.empty() && iv[0] <= res.back()[1])
            res.back()[1] = max(res.back()[1], iv[1]);   // max: iv may sit inside
        else
            res.push_back(iv);
    }
    return res;
}

void print(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << "[" << v[i][0] << ", " << v[i][1] << "]";
    cout << "]\n";
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 3}, {2, 6}, {8, 10}, {15, 18}}, {{1, 4}, {4, 5}}, {{4, 7}, {1, 4}}, {{1, 4}, {2, 3}}, {{5, 6}}
    };
    for (auto& t : tests) {
        cout << "brute: "; print(mergeBrute(t));
        cout << "sort : "; print(merge(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - sort on vector<vector<int>> is lexicographic, so it orders by start.
 * - res.back()[1] edits the last merged interval in place.
 * - Taking the parameter by value lets the function sort its own copy.
 */
