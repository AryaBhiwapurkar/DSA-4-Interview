/*
 * 0027. Remove Element  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/remove-element/
 *
 * Problem: Remove all occurrences of val in place; return k, the count
 *          of remaining elements, which must fill the first k slots
 *          (any order).
 *
 * Examples (k, then first k elements sorted):
 *   [3,2,2,3], val=3            -> 2, [2,2]
 *   [0,1,2,2,3,0,4,2], val=2    -> 5, [0,0,1,3,4]
 *   [], val=1                   -> 0, []
 *   [4,4], val=4                -> 0, []
 *
 * Approaches:
 *   1. Read/write pointers  ⭐   O(n) time, O(1) space   <- go-to
 *   2. Swap with end            O(n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Read/Write Pointers ⭐ ----------
int removeElement(vector<int>& nums, int val) {
    int k = 0;
    for (int x : nums)
        if (x != val) nums[k++] = x;
    return k;
}

// ---------- Approach 2: Swap With End ----------
int removeElementSwap(vector<int>& nums, int val) {
    int i = 0, n = nums.size();
    while (i < n) {
        if (nums[i] == val) nums[i] = nums[--n];   // don't advance i: the moved-in value is unchecked
        else i++;
    }
    return n;
}

// ---------- Driver ----------
void show(const string& label, vector<int> nums, int val, int (*fn)(vector<int>&, int)) {
    int k = fn(nums, val);
    sort(nums.begin(), nums.begin() + k);        // normalize: any order is accepted
    cout << label << ": " << k << ", [";
    for (int i = 0; i < k; i++) cout << (i ? "," : "") << nums[i];
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{3, 2, 2, 3}, 3}, {{0, 1, 2, 2, 3, 0, 4, 2}, 2}, {{}, 1}, {{4, 4}, 4}
    };
    for (auto& [nums, val] : tests) {
        show("read/write", nums, val, removeElement);
        show("swap end  ", nums, val, removeElementSwap);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - nums[--n] decrements n first, then indexes: the current last element.
 * - Erase-remove idiom: v.erase(remove(v.begin(), v.end(), val), v.end()).
 * - Range-for reading x while writing nums[k] is safe since k <= current index.
 */
