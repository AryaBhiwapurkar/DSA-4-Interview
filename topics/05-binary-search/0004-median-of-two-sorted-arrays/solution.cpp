/*
 * 0004. Median of Two Sorted Arrays  |  Hard  |  Binary Search
 * Link: https://leetcode.com/problems/median-of-two-sorted-arrays/
 *
 * Problem: Return the median of two sorted arrays combined, in
 *          O(log(m + n)). One array may be empty.
 *
 * Examples:
 *   [1,3],   [2]       -> 2.00000
 *   [1,2],   [3,4]     -> 2.50000
 *   [],      [1]       -> 1.00000
 *   [2],     []        -> 2.00000
 *   [0,0],   [0,0]     -> 0.00000
 *   [1,3,5], [2,4,6]   -> 3.50000
 *   [1,2],   [-1,3]    -> 1.50000
 *
 * Approaches:
 *   1. Merge, pick middle            O(m+n) time, O(m+n) space
 *   2. Partition binary search  ⭐    O(log min(m,n)) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Merge, Then Pick the Middle ----------
double findMedianSortedArraysMerge(const vector<int>& a, const vector<int>& b) {
    vector<int> m;
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(m));
    int n = m.size();
    if (n % 2) return m[n / 2];
    return (m[n / 2 - 1] + m[n / 2]) / 2.0;
}

// ---------- Approach 2: Partition Binary Search ⭐ ----------
double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
    const vector<int>& A = nums1.size() <= nums2.size() ? nums1 : nums2;   // search the SHORTER one
    const vector<int>& B = nums1.size() <= nums2.size() ? nums2 : nums1;
    int m = A.size(), n = B.size();
    int half = (m + n + 1) / 2;            // left side gets the extra element when odd
    int lo = 0, hi = m;
    while (lo <= hi) {
        int i = lo + (hi - lo) / 2;        // taken from A
        int j = half - i;                  // taken from B
        int aL = i > 0 ? A[i - 1] : INT_MIN, aR = i < m ? A[i] : INT_MAX;
        int bL = j > 0 ? B[j - 1] : INT_MIN, bR = j < n ? B[j] : INT_MAX;
        if (aL > bR) hi = i - 1;           // too many from A
        else if (bL > aR) lo = i + 1;      // too few from A
        else {
            if ((m + n) % 2) return max(aL, bL);
            return (max(aL, bL) + (double)min(aR, bR)) / 2.0;   // double: no int overflow
        }
    }
    return 0;                              // unreachable for sorted input
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, vector<int>>> tests = {
        {{1, 3}, {2}}, {{1, 2}, {3, 4}}, {{}, {1}}, {{2}, {}}, {{0, 0}, {0, 0}}, {{1, 3, 5}, {2, 4, 6}}, {{1, 2}, {-1, 3}}
    };
    for (auto& [a, b] : tests) {
        printf("merge    : %.5f\n", findMedianSortedArraysMerge(a, b));
        printf("partition: %.5f\n", findMedianSortedArrays(a, b));
        printf("---\n");
    }
}

/*
 * Syntax notes (C++):
 * - std::merge(a.., b.., back_inserter(out)) merges two sorted ranges.
 * - A conditional can bind a const reference: const auto& A = c ? x : y;
 * - INT_MIN / INT_MAX as -inf / +inf sentinels (values are only +-1e6).
 * - printf("%.5f") prints a fixed number of decimals.
 */
