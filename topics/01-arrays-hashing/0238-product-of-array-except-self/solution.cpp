/*
 * 0238. Product of Array Except Self  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/product-of-array-except-self/
 *
 * Problem: Return ans where ans[i] is the product of all elements except
 *          nums[i]. No division, O(n) time.
 *
 * Examples:
 *   [1,2,3,4]        -> [24,12,8,6]
 *   [-1,1,0,-3,3]    -> [0,0,9,0,0]
 *   [0,0,5]          -> [0,0,0]
 *
 * Approaches:
 *   1. Brute force                    O(n^2) time, O(1) extra space
 *   2. Prefix + suffix arrays         O(n) time, O(n) extra space
 *   3. Output + running suffix  ⭐     O(n) time, O(1) extra space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
vector<int> productExceptSelfBrute(const vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (j != i) ans[i] *= nums[j];
    return ans;
}

// ---------- Approach 2: Prefix + Suffix Arrays ----------
vector<int> productExceptSelfArrays(const vector<int>& nums) {
    int n = nums.size();
    vector<int> prefix(n, 1), suffix(n, 1), ans(n);
    for (int i = 1; i < n; i++) prefix[i] = prefix[i - 1] * nums[i - 1];          // product left of i
    for (int i = n - 2; i >= 0; i--) suffix[i] = suffix[i + 1] * nums[i + 1];     // product right of i
    for (int i = 0; i < n; i++) ans[i] = prefix[i] * suffix[i];
    return ans;
}

// ---------- Approach 3: Output Array + Running Suffix ⭐ ----------
vector<int> productExceptSelf(const vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 1);
    for (int i = 1; i < n; i++) ans[i] = ans[i - 1] * nums[i - 1];   // ans holds left products
    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
        ans[i] *= suffix;                                            // left * right
        suffix *= nums[i];                                           // include nums[i] for the next index
    }
    return ans;
}

// ---------- Driver ----------
void print(const string& label, const vector<int>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3, 4}, {-1, 1, 0, -3, 3}, {0, 0, 5}};
    for (auto& nums : tests) {
        print("brute ", productExceptSelfBrute(nums));
        print("arrays", productExceptSelfArrays(nums));
        print("suffix", productExceptSelf(nums));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<int> a(n, 1), b(n, 1) declares several vectors in one statement.
 * - Reverse loops with int i (not size_t) so i >= 0 can become false.
 * - *= updates in place; order of the two lines in the suffix loop matters.
 */
