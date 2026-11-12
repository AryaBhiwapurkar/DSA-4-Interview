/*
 * 0041. First Missing Positive  |  Hard  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/first-missing-positive/
 *
 * Problem: Smallest positive integer missing from an unsorted array,
 *          in O(n) time and O(1) extra space.
 *
 * Examples:
 *   [1,2,0]         -> 3
 *   [3,4,-1,1]      -> 2
 *   [7,8,9,11,12]   -> 1
 *   [1]             -> 2
 *   [1,1]           -> 2
 *   [2,1]           -> 3
 *
 * Approaches:
 *   1. Sort and scan             O(n log n) time, O(1) extra
 *   2. Hash set                  O(n) time, O(n) space
 *   3. Cyclic placement  ⭐      O(n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort and Scan ----------
int firstMissingPositiveSort(vector<int> nums) {
    sort(nums.begin(), nums.end());
    int want = 1;
    for (int x : nums)
        if (x == want) want++;                     // duplicates and junk just don't match
    return want;
}

// ---------- Approach 2: Hash Set ----------
int firstMissingPositiveSet(const vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int want = 1;
    while (s.count(want)) want++;
    return want;
}

// ---------- Approach 3: Cyclic Placement ⭐ ----------
int firstMissingPositive(vector<int> nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++)
        while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i])   // stops on duplicates
            swap(nums[i], nums[nums[i] - 1]);      // value v goes home to index v - 1
    for (int i = 0; i < n; i++)
        if (nums[i] != i + 1) return i + 1;
    return n + 1;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 2, 0}, {3, 4, -1, 1}, {7, 8, 9, 11, 12}, {1}, {1, 1}, {2, 1}};
    for (auto& t : tests) {
        cout << "sort  : " << firstMissingPositiveSort(t) << "\n";
        cout << "set   : " << firstMissingPositiveSet(t) << "\n";
        cout << "cyclic: " << firstMissingPositive(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - swap(nums[i], nums[nums[i] - 1]) is safe: both references are bound before swapping.
 * - unordered_set<int> s(v.begin(), v.end()) builds a set from a range.
 * - Range checks before indexing (1 <= v && v <= n) prevent out-of-bounds reads.
 */
