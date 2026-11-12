/*
 * 0719. Find K-th Smallest Pair Distance  |  Hard  |  Binary Search
 * Link: https://leetcode.com/problems/find-k-th-smallest-pair-distance/
 *
 * Problem: Over all pairs i < j, return the k-th smallest |nums[i] - nums[j]|.
 *
 * Examples:
 *   [1,3,1],    k = 1   -> 0
 *   [1,1,1],    k = 2   -> 0
 *   [1,6,1],    k = 3   -> 5
 *   [1,3,5,9],  k = 4   -> 4
 *   [62,100,4], k = 2   -> 58
 *   [9,10,7,10,6,1,5,4,9,8], k = 18   -> 2
 *
 * Approaches:
 *   1. All pairs + sort                               O(n^2 log n) time, O(n^2) space
 *   2. Binary search on distance + two-pointer count ⭐ O(n log n + n log W), O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: All Pairs + Sort ----------
int smallestDistancePairBrute(vector<int> nums, int k) {
    vector<int> d;
    for (size_t i = 0; i < nums.size(); i++)
        for (size_t j = i + 1; j < nums.size(); j++) d.push_back(abs(nums[i] - nums[j]));
    nth_element(d.begin(), d.begin() + (k - 1), d.end());   // only need the k-th
    return d[k - 1];
}

// ---------- Approach 2: Binary Search + Two-pointer Count ⭐ ----------
long long countAtMost(const vector<int>& a, int d) {
    long long cnt = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        while (a[r] - a[l] > d) l++;         // l only moves forward
        cnt += r - l;                         // pairs (l..r-1, r)
    }
    return cnt;
}

int smallestDistancePair(vector<int> nums, int k) {
    sort(nums.begin(), nums.end());
    int lo = 0, hi = nums.back() - nums.front();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (countAtMost(nums, mid) >= k) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 3, 1}, 1}, {{1, 1, 1}, 2}, {{1, 6, 1}, 3}, {{1, 3, 5, 9}, 4}, {{62, 100, 4}, 2},
        {{9, 10, 7, 10, 6, 1, 5, 4, 9, 8}, 18}};
    for (auto& [nums, k] : tests) {
        cout << "brute : " << smallestDistancePairBrute(nums, k) << "\n";
        cout << "binary: " << smallestDistancePair(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - nth_element puts the k-th smallest at position k-1 in O(n) average.
 * - Two loop variables in one for: for (int l = 0, r = 0; ...; r++).
 * - Taking vector<int> by value lets the function sort its own copy.
 */
