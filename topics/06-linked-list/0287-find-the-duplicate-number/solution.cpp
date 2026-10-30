/*
 * 0287. Find the Duplicate Number  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/find-the-duplicate-number/
 *
 * Problem: n + 1 ints in [1, n]; exactly one value repeats. Find it
 *          without modifying the array, in O(1) extra space.
 *
 * Examples:
 *   [1,3,4,2,2]  -> 2
 *   [3,1,3,4,2]  -> 3
 *   [3,3,3,3,3]  -> 3
 *   [1,1]        -> 1
 *   [2,2,2]      -> 2
 *
 * Approaches:
 *   1. Hash set                     O(n) time, O(n) space
 *   2. Binary search on value       O(n log n) time, O(1) space
 *   3. Floyd cycle detection  ⭐     O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Hash Set ----------
int findDuplicateSet(const vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums)
        if (!seen.insert(x).second) return x;
    return -1;
}

// ---------- Approach 2: Binary Search on Value ----------
int findDuplicateBinary(const vector<int>& nums) {
    int lo = 1, hi = nums.size() - 1;      // values live in [1, n]
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int cnt = count_if(nums.begin(), nums.end(), [&](int x) { return x <= mid; });
        if (cnt > mid) hi = mid;           // pigeonhole: too many values <= mid
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Approach 3: Floyd Cycle Detection ⭐ ----------
int findDuplicate(const vector<int>& nums) {
    int slow = 0, fast = 0;                // index 0 is the head: no value points to it
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);                // phase 1: meet inside the cycle
    slow = 0;
    while (slow != fast) {                 // phase 2: meet at the cycle entry
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;                           // entry has two incoming edges = duplicate
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 3, 4, 2, 2}, {3, 1, 3, 4, 2}, {3, 3, 3, 3, 3}, {1, 1}, {2, 2, 2}};
    for (auto& nums : tests) {
        cout << "hashSet: " << findDuplicateSet(nums) << "\n";
        cout << "binary : " << findDuplicateBinary(nums) << "\n";
        cout << "floyd  : " << findDuplicate(nums) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - do { ... } while (cond); runs the body once before testing: needed
 *   because slow and fast start equal.
 * - count_if with a capturing lambda [&] counts matches in one line.
 * - insert(x).second is false when x was already present.
 */
