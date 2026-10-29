/*
 * 0217. Contains Duplicate  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/contains-duplicate/
 *
 * Problem: Return true if any value appears at least twice in the
 *          array, false if all elements are distinct.
 *
 * Examples:
 *   [1,2,3,1]               -> true
 *   [1,2,3,4]               -> false
 *   [1,1,1,3,3,4,3,2,4,2]   -> true
 *   [7]                     -> false
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Sort + adjacent    O(n log n) time, O(1) extra space
 *   3. Hash set  ⭐        O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
bool containsDuplicateBrute(const vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (nums[i] == nums[j]) return true;
    return false;
}

// ---------- Approach 2: Sort + Adjacent Check ----------
bool containsDuplicateSorted(vector<int> nums) {   // by value: don't mutate caller's array
    sort(nums.begin(), nums.end());
    for (size_t i = 1; i < nums.size(); i++)
        if (nums[i] == nums[i - 1]) return true;   // equal values end up adjacent
    return false;
}

// ---------- Approach 3: Hash Set ⭐ ----------
bool containsDuplicate(const vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums)
        if (!seen.insert(x).second) return true;   // .second == false: already present
    return false;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {
        {1, 2, 3, 1}, {1, 2, 3, 4}, {1, 1, 1, 3, 3, 4, 3, 2, 4, 2}, {7}
    };
    cout << boolalpha;
    for (auto& nums : tests) {
        cout << "brute : " << containsDuplicateBrute(nums) << "\n";
        cout << "sorted: " << containsDuplicateSorted(nums) << "\n";
        cout << "hash  : " << containsDuplicate(nums) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_set::insert returns pair<iterator, bool>; .second is true
 *   only if the element was newly inserted.
 * - Passing vector<int> by value gives the function its own copy to sort.
 * - cout << boolalpha prints true/false instead of 1/0.
 * - Use size_t for loop indices compared with .size() to avoid -Wsign-compare.
 */
