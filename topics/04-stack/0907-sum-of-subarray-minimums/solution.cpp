/*
 * 0907. Sum of Subarray Minimums  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/sum-of-subarray-minimums/
 *
 * Problem: Sum of min(sub) over all contiguous subarrays, modulo 1e9+7.
 *
 * Examples:
 *   [3,1,2,4]         -> 17
 *   [11,81,94,43,3]   -> 444
 *   [2,2,2]           -> 12
 *   [5]               -> 5
 *
 * Approaches:
 *   1. All subarrays, running min                O(n^2) time, O(1) space
 *   2. Contribution via monotonic stacks  ⭐     O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;

// ---------- Approach 1: All Subarrays ----------
int sumSubarrayMinsBrute(const vector<int>& arr) {
    long long total = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        int mn = INT_MAX;
        for (size_t j = i; j < arr.size(); j++) {
            mn = min(mn, arr[j]);
            total = (total + mn) % MOD;
        }
    }
    return total;
}

// ---------- Approach 2: Contribution ⭐ ----------
int sumSubarrayMins(const vector<int>& arr) {
    int n = arr.size();
    vector<int> prevLess(n), nextLessEq(n), st;
    for (int i = 0; i < n; i++) {                  // previous strictly smaller
        while (!st.empty() && arr[st.back()] >= arr[i]) st.pop_back();
        prevLess[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {             // next smaller-or-equal (tie-break)
        while (!st.empty() && arr[st.back()] > arr[i]) st.pop_back();
        nextLessEq[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long cnt = (long long)(i - prevLess[i]) * (nextLessEq[i] - i);   // subarrays where arr[i] is the min
        total = (total + arr[i] * cnt) % MOD;
    }
    return total;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{3, 1, 2, 4}, {11, 81, 94, 43, 3}, {2, 2, 2}, {5}};
    for (auto& t : tests) {
        cout << "brute       : " << sumSubarrayMinsBrute(t) << "\n";
        cout << "contribution: " << sumSubarrayMins(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - 1'000'000'007 uses digit separators (C++14).
 * - Promote to long long before multiplying counts: (long long)a * b.
 * - Two stack passes with opposite strictness (>= vs >) split ties between duplicates.
 */
