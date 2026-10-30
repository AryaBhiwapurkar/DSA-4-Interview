/*
 * 0162. Find Peak Element  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/find-peak-element/
 *
 * Problem: Return the index of any element strictly greater than its
 *          neighbours (outside the array counts as -inf). O(log n).
 *
 * Examples (any peak is accepted; each approach's answer is checked):
 *   [1,2,3,1]        -> 2
 *   [1,2,1,3,5,6,4]  -> 1 or 5   (linear finds 1, binary finds 5)
 *   [1]              -> 0
 *   [3,2,1]          -> 0
 *   [1,2,3]          -> 2
 *
 * Approaches:
 *   1. Linear scan                 O(n) time, O(1) space
 *   2. Binary search on slope  ⭐   O(log n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Linear Scan ----------
int findPeakElementLinear(const vector<int>& nums) {
    for (int i = 0; i + 1 < (int)nums.size(); i++)
        if (nums[i] > nums[i + 1]) return i;   // first downhill step: everything before rose
    return nums.size() - 1;
}

// ---------- Approach 2: Binary Search on Slope ⭐ ----------
int findPeakElement(const vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {                      // lo < hi guarantees mid + 1 <= hi
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[mid + 1]) hi = mid;   // downhill: peak at mid or left
        else lo = mid + 1;                         // uphill: peak strictly right
    }
    return lo;
}

// ---------- Driver ----------
bool isPeak(const vector<int>& a, int i) {
    int n = a.size();
    return (i == 0 || a[i] > a[i - 1]) && (i == n - 1 || a[i] > a[i + 1]);
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3, 1}, {1, 2, 1, 3, 5, 6, 4}, {1}, {3, 2, 1}, {1, 2, 3}};
    cout << boolalpha;
    for (auto& nums : tests) {
        int a = findPeakElementLinear(nums), b = findPeakElement(nums);
        cout << "linear: " << a << " peak=" << isPeak(nums, a) << "\n";
        cout << "binary: " << b << " peak=" << isPeak(nums, b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `i + 1 < (int)nums.size()` avoids size() - 1 underflow on empty vectors.
 * - Boundary checks via short-circuit: (i == 0 || a[i] > a[i-1]).
 * - Binary search works on any monotone decision, not just sorted values.
 */
