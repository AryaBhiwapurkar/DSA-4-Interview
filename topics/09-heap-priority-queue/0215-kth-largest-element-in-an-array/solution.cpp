/*
 * 0215. Kth Largest Element in an Array  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/kth-largest-element-in-an-array/
 *
 * Problem: Return the k-th largest element (duplicates count).
 *
 * Examples:
 *   [3,2,1,5,6,4],         k 2  -> 5
 *   [3,2,3,1,2,4,5,5,6],   k 4  -> 4
 *   [1],                   k 1  -> 1
 *   [2,1],                 k 2  -> 1
 *   [7,7,7,7],             k 3  -> 7
 *
 * Approaches:
 *   1. Sort                        O(n log n) time, O(1) extra
 *   2. Min-heap of size k  ⭐       O(n log k) time, O(k) space   <- go-to
 *   3. Quickselect (3-way)         O(n) average, O(n^2) worst, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort ----------
int findKthLargestSort(vector<int> a, int k) {
    sort(a.begin(), a.end());
    return a[a.size() - k];
}

// ---------- Approach 2: Min-Heap of Size k ⭐ ----------
int findKthLargest(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : nums) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();  // keep only the k largest
    }
    return pq.top();
}

// ---------- Approach 3: Quickselect (3-Way Partition) ----------
int findKthLargestSelect(vector<int> a, int k) {
    int lo = 0, hi = a.size() - 1, target = a.size() - k;   // index in ascending order
    while (true) {
        int pivot = a[lo + (hi - lo) / 2];
        int lt = lo, i = lo, gt = hi;      // [lo,lt) < pivot, [lt,i) == pivot, (gt,hi] > pivot
        while (i <= gt) {
            if (a[i] < pivot) swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else i++;
        }
        if (target < lt) hi = lt - 1;
        else if (target > gt) lo = gt + 1;
        else return pivot;                 // target inside the == block
    }
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{3, 2, 1, 5, 6, 4}, 2}, {{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4}, {{1}, 1}, {{2, 1}, 2}, {{7, 7, 7, 7}, 3}
    };
    for (auto& [nums, k] : tests) {
        cout << "sort  : " << findKthLargestSort(nums, k) << "\n";
        cout << "heap  : " << findKthLargest(nums, k) << "\n";
        cout << "select: " << findKthLargestSelect(nums, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - swap(a[lt++], a[i++]) swaps, then advances both indices.
 * - Library one-liner: nth_element(a.begin(), a.begin() + n - k, a.end()).
 * - Taking the vector by value (vector<int> a) gives quickselect its own copy.
 */
