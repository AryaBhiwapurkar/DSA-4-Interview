/*
 * 0189. Rotate Array  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/rotate-array/
 *
 * Problem: Rotate the array to the right by k steps, in place.
 *
 * Examples:
 *   [1,2,3,4,5,6,7], k=3   -> [5,6,7,1,2,3,4]
 *   [-1,-100,3,99], k=2    -> [3,99,-1,-100]
 *   [1,2], k=3             -> [2,1]
 *   [1,2,3], k=0           -> [1,2,3]
 *
 * Approaches:
 *   1. Rotate by one, k times   O(n*k) time, O(1) space
 *   2. Extra array              O(n) time, O(n) space
 *   3. Three reversals  ⭐       O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Rotate by One, k Times ----------
void rotateBrute(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    for (int step = 0; step < k; step++) {
        int last = nums[n - 1];
        for (int i = n - 1; i > 0; i--) nums[i] = nums[i - 1];
        nums[0] = last;
    }
}

// ---------- Approach 2: Extra Array ----------
void rotateExtra(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> out(n);
    for (int i = 0; i < n; i++) out[(i + k) % n] = nums[i];   // (i + k) <= 2e5: no overflow
    nums = out;
}

// ---------- Approach 3: Three Reversals ⭐ ----------
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;                                                    // k may exceed n
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);                   // first k: the old tail, fixed
    reverse(nums.begin() + k, nums.end());                     // rest: the old head, fixed
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 2, 3, 4, 5, 6, 7}, 3}, {{-1, -100, 3, 99}, 2}, {{1, 2}, 3}, {{1, 2, 3}, 0}
    };
    for (auto& [nums, k] : tests) {
        auto a = nums, b = nums, c = nums;                     // each approach mutates its own copy
        rotateBrute(a, k);
        rotateExtra(b, k);
        rotate(c, k);
        print("brute  ", a);
        print("extra  ", b);
        print("reverse", c);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - reverse(first, last) reverses the half-open range [first, last).
 * - Pass vector<int>& to mutate the caller's vector in place.
 * - auto a = nums copies the vector (value semantics).
 */
