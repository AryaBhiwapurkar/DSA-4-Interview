/*
 * 0268. Missing Number  |  Easy  |  Bit Manipulation
 * Link: https://leetcode.com/problems/missing-number/
 *
 * Problem: nums holds n distinct numbers from 0..n. Return the one missing.
 *
 * Examples:
 *   [3,0,1]               -> 2
 *   [0,1]                 -> 2
 *   [9,6,4,2,3,5,7,0,1]   -> 8
 *   [1]                   -> 0
 *   [0]                   -> 1
 *
 * Approaches:
 *   1. Sort, find the first index != value   O(n log n) time, O(1) extra
 *   2. Hash set of values                    O(n) time, O(n) space
 *   3. Gauss sum: n(n+1)/2 - sum             O(n) time, O(1) space
 *   4. XOR indices and values  ⭐             O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort ----------
int missingNumberSort(vector<int> a) {
    sort(a.begin(), a.end());
    for (int i = 0; i < (int)a.size(); i++)
        if (a[i] != i) return i;
    return a.size();                               // 0..n-1 all present
}

// ---------- Approach 2: Hash Set ----------
int missingNumberSet(const vector<int>& nums) {
    unordered_set<int> seen(nums.begin(), nums.end());
    for (int i = 0;; i++)
        if (!seen.count(i)) return i;
}

// ---------- Approach 3: Gauss Sum ----------
int missingNumberSum(const vector<int>& nums) {
    long long n = nums.size();
    return n * (n + 1) / 2 - accumulate(nums.begin(), nums.end(), 0LL);   // long long: safe for big n
}

// ---------- Approach 4: XOR ⭐ ----------
int missingNumber(const vector<int>& nums) {
    int x = nums.size();                           // n has no index to pair with
    for (int i = 0; i < (int)nums.size(); i++) x ^= i ^ nums[i];
    return x;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{3, 0, 1}, {0, 1}, {9, 6, 4, 2, 3, 5, 7, 0, 1}, {1}, {0}};
    for (auto& t : tests) {
        cout << "sort: " << missingNumberSort(t) << "\n";
        cout << "set : " << missingNumberSet(t) << "\n";
        cout << "sum : " << missingNumberSum(t) << "\n";
        cout << "xor : " << missingNumber(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - accumulate(..., 0LL) sums in long long; with 0 it would sum in int.
 * - `for (int i = 0;; i++)` has no condition: the answer always exists, so it returns.
 * - XOR is safe from overflow, unlike the sum formula with int.
 */
