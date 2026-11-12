/*
 * 0702. Search in a Sorted Array of Unknown Size  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/
 *
 * Problem: A sorted array of distinct ints is readable only via reader.get(i),
 *          which returns 2^31 - 1 past the end. Return target's index or -1.
 *
 * Examples:
 *   [-1,0,3,5,9,12], target = 9    -> 4
 *   [-1,0,3,5,9,12], target = 2    -> -1
 *   [5],             target = 5    -> 0
 *   [-1,0,3,5,9,12], target = 13   -> -1   (past the end)
 *   [1,3],           target = -5   -> -1   (before the start)
 *   [-1,0,3,5,9,12], target = -1   -> 0
 *
 * Approaches:
 *   1. Linear scan                          O(k) time, O(1) space
 *   2. Exponential bound + binary search ⭐ O(log k) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

class ArrayReader {                            // stand-in for the LeetCode interface
    vector<int> a;
public:
    explicit ArrayReader(vector<int> v) : a(move(v)) {}
    int get(int i) const { return i < (int)a.size() ? a[i] : INT_MAX; }
};

// ---------- Approach 1: Linear Scan ----------
int searchLinear(const ArrayReader& r, int target) {
    for (int i = 0; r.get(i) <= target; i++)   // the sentinel ends the loop
        if (r.get(i) == target) return i;
    return -1;
}

// ---------- Approach 2: Exponential Bound + Binary Search ⭐ ----------
int search(const ArrayReader& r, int target) {
    int lo = 0, hi = 1;
    while (r.get(hi) < target) { lo = hi; hi *= 2; }   // past-end reads act as +inf
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int v = r.get(mid);
        if (v == target) return mid;
        if (v < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{-1, 0, 3, 5, 9, 12}, 9}, {{-1, 0, 3, 5, 9, 12}, 2}, {{5}, 5},
        {{-1, 0, 3, 5, 9, 12}, 13}, {{1, 3}, -5}, {{-1, 0, 3, 5, 9, 12}, -1}};
    for (auto& [v, t] : tests) {
        ArrayReader r(v);
        cout << "linear     : " << searchLinear(r, t) << "\n";
        cout << "exponential: " << search(r, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - explicit on a one-argument constructor blocks accidental implicit conversion.
 * - a(move(v)) takes ownership of the by-value parameter without a copy.
 * - INT_MAX (from <climits>) is the 2^31 - 1 sentinel.
 */
