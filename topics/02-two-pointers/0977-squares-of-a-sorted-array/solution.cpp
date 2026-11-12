/*
 * 0977. Squares of a Sorted Array  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/squares-of-a-sorted-array/
 *
 * Problem: Sorted array (may include negatives) -> sorted array of squares.
 *
 * Examples:
 *   [-4,-1,0,3,10]  -> [0,1,9,16,100]
 *   [-7,-3,2,3,11]  -> [4,9,9,49,121]
 *   [-5,-3,-1]      -> [1,9,25]
 *   [2]             -> [4]
 *
 * Approaches:
 *   1. Square and sort                   O(n log n) time, O(n) space
 *   2. Two pointers, fill from back  ⭐  O(n) time, O(n) output   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Square and Sort ----------
vector<int> sortedSquaresSort(vector<int> nums) {
    for (int& x : nums) x *= x;
    sort(nums.begin(), nums.end());
    return nums;
}

// ---------- Approach 2: Two Pointers ⭐ ----------
vector<int> sortedSquares(const vector<int>& nums) {
    int n = nums.size(), lo = 0, hi = n - 1;
    vector<int> res(n);
    for (int k = n - 1; k >= 0; k--) {             // largest square is at an end
        if (abs(nums[lo]) > abs(nums[hi])) res[k] = nums[lo] * nums[lo], lo++;
        else res[k] = nums[hi] * nums[hi], hi--;
    }
    return res;
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{-4, -1, 0, 3, 10}, {-7, -3, 2, 3, 11}, {-5, -3, -1}, {2}};
    for (auto& t : tests) {
        cout << "sort    : "; print(sortedSquaresSort(t));
        cout << "pointers: "; print(sortedSquares(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - for (int& x : nums) x *= x; squares in place through a reference.
 * - Looping k from n-1 down to 0 runs exactly n times, so lo <= hi holds throughout.
 * - abs() on int comes from <cstdlib> (included by bits/stdc++.h).
 */
