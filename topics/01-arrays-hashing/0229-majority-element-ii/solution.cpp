/*
 * 0229. Majority Element II  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/majority-element-ii/
 *
 * Problem: Return all values appearing more than floor(n/3) times.
 *
 * Examples:
 *   [3,2,3]          -> [3]
 *   [1]              -> [1]
 *   [1,2]            -> [1,2]
 *   [1,2,3,1,2,1]    -> [1]
 *   [1,2,3]          -> []
 *   [0]              -> [0]     (sentinel trap: must not print [0,0])
 *   [2,2,1,1,1,2,2]  -> [1,2]
 *
 * Approaches:
 *   1. Hashmap counts                         O(n) time, O(n) space
 *   2. Sort + runs                            O(n log n) time, O(1) extra
 *   3. Two-candidate Boyer-Moore  ⭐          O(n) time, O(1) space   <- go-to
 *   (Output order: approaches print values in ascending order to compare easily.)
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Hashmap Counts ----------
vector<int> majorityElementMap(const vector<int>& nums) {
    unordered_map<int, int> cnt;
    for (int x : nums) cnt[x]++;
    vector<int> out;
    for (auto& [v, c] : cnt)
        if (c > (int)nums.size() / 3) out.push_back(v);
    return out;
}

// ---------- Approach 2: Sort + Runs ----------
vector<int> majorityElementSort(vector<int> nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<int> out;
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && nums[j] == nums[i]) j++;   // run [i, j)
        if (j - i > n / 3) out.push_back(nums[i]);
        i = j;
    }
    return out;
}

// ---------- Approach 3: Boyer-Moore, Two Candidates ⭐ ----------
vector<int> majorityElement(const vector<int>& nums) {
    int c1 = 0, c2 = 1, k1 = 0, k2 = 0;            // distinct starting candidates
    for (int x : nums) {
        if (x == c1) k1++;                         // matches first...
        else if (x == c2) k2++;
        else if (k1 == 0) c1 = x, k1 = 1;          // ...then empty slots
        else if (k2 == 0) c2 = x, k2 = 1;
        else k1--, k2--;                           // cancel three distinct values
    }
    vector<int> out;
    for (int c : {c1, c2})                         // candidates are only possible answers
        if (count(nums.begin(), nums.end(), c) > (int)nums.size() / 3) out.push_back(c);
    return out;
}

// ---------- Driver ----------
void print(vector<int> v) {
    sort(v.begin(), v.end());
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{3, 2, 3}, {1}, {1, 2}, {1, 2, 3, 1, 2, 1}, {1, 2, 3}, {0}, {2, 2, 1, 1, 1, 2, 2}};
    for (auto& t : tests) {
        cout << "map  : "; print(majorityElementMap(t));
        cout << "sort : "; print(majorityElementSort(t));
        cout << "voting: "; print(majorityElement(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Comma operator in a branch: c1 = x, k1 = 1 runs both assignments as one statement.
 * - std::count(first, last, value) counts occurrences in O(n).
 * - for (int c : {c1, c2}) iterates an initializer_list.
 */
