/*
 * 0136. Single Number  |  Easy  |  Bit Manipulation
 * Link: https://leetcode.com/problems/single-number/
 *
 * Problem: Every number appears twice except one. Find it in O(n) time and
 *          O(1) extra space.
 *
 * Examples:
 *   [2,2,1]         -> 1
 *   [4,1,2,1,2]     -> 4
 *   [1]             -> 1
 *   [-3,7,7]        -> -3
 *
 * Approaches:
 *   1. Hash set: add, remove on second sighting   O(n) time, O(n) space
 *   2. Sort, check pairs                          O(n log n) time, O(1) extra
 *   3. XOR everything  ⭐                          O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Hash Set ----------
int singleNumberSet(const vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums)
        if (!seen.erase(x)) seen.insert(x);       // erase returns 0 if x wasn't there
    return *seen.begin();
}

// ---------- Approach 2: Sort ----------
int singleNumberSort(vector<int> a) {
    sort(a.begin(), a.end());
    for (size_t i = 0; i + 1 < a.size(); i += 2)   // pairs at (0,1), (2,3), ...
        if (a[i] != a[i + 1]) return a[i];
    return a.back();                               // the single one is last
}

// ---------- Approach 3: XOR ⭐ ----------
int singleNumber(const vector<int>& nums) {
    int x = 0;
    for (int v : nums) x ^= v;                     // pairs cancel: v ^ v = 0
    return x;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{2, 2, 1}, {4, 1, 2, 1, 2}, {1}, {-3, 7, 7}};
    for (auto& t : tests) {
        cout << "set : " << singleNumberSet(t) << "\n";
        cout << "sort: " << singleNumberSort(t) << "\n";
        cout << "xor : " << singleNumber(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_set::erase(key) returns how many were removed (0 or 1).
 * - XOR works on negative ints too: it's purely bitwise.
 * - i + 1 < a.size() avoids size_t underflow from a.size() - 1.
 */
