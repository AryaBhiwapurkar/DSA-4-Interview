/*
 * 0001. Two Sum  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/two-sum/
 *
 * Problem: Given an array and a target, return indices of the two
 *          numbers that add up to target. Exactly one answer exists;
 *          the same element can't be used twice.
 *
 * Examples:
 *   [2,7,11,15], target 9  -> [0,1]
 *   [3,2,4],     target 6  -> [1,2]
 *   [3,3],       target 6  -> [0,1]
 *   [-3,4,3,90], target 0  -> [0,2]
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Sort + two ptrs    O(n log n) time, O(n) space
 *   3. Hashmap  ⭐         O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
vector<int> twoSumBrute(const vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)   // j > i: never pair an element with itself
            if (nums[i] + nums[j] == target) return {i, j};
    return {};
}

// ---------- Approach 2: Sort + Two Pointers ----------
vector<int> twoSumSorted(const vector<int>& nums, int target) {
    int n = nums.size();
    vector<pair<int, int>> arr;            // (value, original index): sorting would lose indices otherwise
    for (int i = 0; i < n; i++) arr.push_back({nums[i], i});
    sort(arr.begin(), arr.end());

    int l = 0, r = n - 1;
    while (l < r) {
        int sum = arr[l].first + arr[r].first;   // |sum| <= 2e9 < INT_MAX: safe here
        if (sum == target) {
            int a = arr[l].second, b = arr[r].second;
            return {min(a, b), max(a, b)};
        }
        if (sum < target) l++;             // need bigger -> move left up
        else r--;                          // need smaller -> move right down
    }
    return {};
}

// ---------- Approach 3: One-Pass Hashmap ⭐ ----------
vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> seen;          // value -> index
    for (int i = 0; i < (int)nums.size(); i++) {
        int need = target - nums[i];
        auto it = seen.find(need);         // find(), NOT seen[need] (that would insert)
        if (it != seen.end()) return {it->second, i};
        seen[nums[i]] = i;                 // insert AFTER checking: avoids self-match
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
    vector<pair<vector<int>, int>> tests = {
        {{2, 7, 11, 15}, 9}, {{3, 2, 4}, 6}, {{3, 3}, 6}, {{-3, 4, 3, 90}, 0}
    };
    for (auto& [nums, target] : tests) {
        print("brute ", twoSumBrute(nums, target));
        print("sorted", twoSumSorted(nums, target));
        print("hash  ", twoSum(nums, target));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - unordered_map lookup: find() returns an iterator; compare with end().
 *   count(key) also works (returns 0/1). Avoid map[key] for lookups: it inserts.
 * - Structured bindings: `auto& [nums, target]` unpacks a pair (C++17).
 * - Returning {i, j} from a vector<int> function uses brace initialization.
 * - sort() on vector<pair> sorts by .first, then .second.
 */
