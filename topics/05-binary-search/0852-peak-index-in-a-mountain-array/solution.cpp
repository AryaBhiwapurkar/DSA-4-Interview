/*
 * 0852. Peak Index in a Mountain Array  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/peak-index-in-a-mountain-array/
 *
 * Problem: The array strictly rises to one peak then strictly falls.
 *          Return the peak's index in O(log n).
 *
 * Examples:
 *   [0,1,0]                              -> 1
 *   [0,2,1,0]                            -> 1
 *   [0,10,5,2]                           -> 1
 *   [3,4,5,1]                            -> 2
 *   [24,69,100,99,79,78,67,36,26,19]     -> 2
 *
 * Approaches:
 *   1. Linear scan                    O(n) time, O(1) space
 *   2. Binary search on the slope ⭐  O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int peakIndexInMountainArrayLinear(const vector<int>& arr) {
    int i = 0;
    while (arr[i] < arr[i + 1]) i++;          // climb until the next step goes down
    return i;
}

// ---------- Approach 2: Binary Search on the Slope ⭐ ----------
int peakIndexInMountainArray(const vector<int>& arr) {
    int lo = 0, hi = arr.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;          // mid < hi, so mid + 1 is in bounds
        if (arr[mid] < arr[mid + 1]) lo = mid + 1;   // still climbing
        else hi = mid;                               // at or past the peak
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {
        {0, 1, 0}, {0, 2, 1, 0}, {0, 10, 5, 2}, {3, 4, 5, 1}, {24, 69, 100, 99, 79, 78, 67, 36, 26, 19}};
    for (auto& t : tests) {
        cout << "linear: " << peakIndexInMountainArrayLinear(t) << "\n";
        cout << "binary: " << peakIndexInMountainArray(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - int hi = arr.size() - 1 converts size_t to int; safe here since n >= 3.
 * - Floor midpoint keeps mid < hi inside while (lo < hi), so arr[mid + 1] is valid.
 * - while (cond) i++; is a compact scan when the guarantee ensures termination.
 */
