/*
 * 0167. Two Sum II - Input Array Is Sorted  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * Problem: Sorted array, return 1-based indices [i, j] (i < j) of the two
 *          numbers summing to target. Exactly one answer; O(1) extra space.
 *
 * Examples:
 *   [2,7,11,15], target 9  -> [1,2]
 *   [2,3,4],     target 6  -> [1,3]
 *   [-1,0],      target -1 -> [1,2]
 *   [1,1,3],     target 2  -> [1,2]
 *
 * Approaches:
 *   1. Binary search per element   O(n log n) time, O(1) space
 *   2. Hashmap                     O(n) time, O(n) space
 *   3. Two pointers  ⭐             O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Binary Search per Element ----------
vector<int> twoSumBinary(const vector<int>& a, int target) {
    for (int i = 0; i < (int)a.size(); i++) {
        auto it = lower_bound(a.begin() + i + 1, a.end(), target - a[i]);   // search only to the right of i
        if (it != a.end() && *it == target - a[i]) return {i + 1, int(it - a.begin()) + 1};
    }
    return {};
}

// ---------- Approach 2: Hashmap ----------
vector<int> twoSumHash(const vector<int>& a, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < (int)a.size(); i++) {
        auto it = seen.find(target - a[i]);
        if (it != seen.end()) return {it->second + 1, i + 1};
        seen[a[i]] = i;
    }
    return {};
}

// ---------- Approach 3: Two Pointers ⭐ ----------
vector<int> twoSum(const vector<int>& a, int target) {
    int l = 0, r = a.size() - 1;
    while (l < r) {
        int sum = a[l] + a[r];
        if (sum == target) return {l + 1, r + 1};   // 1-based
        if (sum < target) l++;                      // a[l] is too small for every remaining partner
        else r--;                                   // a[r] is too big for every remaining partner
    }
    return {};
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {{{2, 7, 11, 15}, 9}, {{2, 3, 4}, 6}, {{-1, 0}, -1}, {{1, 1, 3}, 2}};
    for (auto& [a, target] : tests) {
        print("binary  ", twoSumBinary(a, target));
        print("hash    ", twoSumHash(a, target));
        print("pointers", twoSum(a, target));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - lower_bound(first, last, x) can search a sub-range like (a.begin()+i+1, a.end()).
 * - Iterator minus begin() gives the index (ptrdiff_t); cast to int.
 * - Returning {} from a vector<int> function gives an empty vector.
 */
