/*
 * 0496. Next Greater Element I  |  Easy  |  Stack
 * Link: https://leetcode.com/problems/next-greater-element-i/
 *
 * Problem: For each value of nums1 (a subset of nums2, all distinct), return the first
 *          larger value to its right in nums2, or -1.
 *
 * Examples:
 *   nums1 = [4,1,2], nums2 = [1,3,4,2]   -> [-1,3,-1]
 *   nums1 = [2,4],   nums2 = [1,2,3,4]   -> [3,-1]
 *   nums1 = [3,2,1], nums2 = [3,2,1]     -> [-1,-1,-1]
 *
 * Approaches:
 *   1. Scan right per query            O(n1 * n2) time, O(1) space
 *   2. Monotonic stack + map  ⭐       O(n1 + n2) time, O(n2) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Scan per Query ----------
vector<int> nextGreaterElementBrute(const vector<int>& nums1, const vector<int>& nums2) {
    vector<int> out;
    for (int v : nums1) {
        int i = find(nums2.begin(), nums2.end(), v) - nums2.begin(), ans = -1;
        for (int j = i + 1; j < (int)nums2.size(); j++)
            if (nums2[j] > v) { ans = nums2[j]; break; }
        out.push_back(ans);
    }
    return out;
}

// ---------- Approach 2: Monotonic Stack ⭐ ----------
vector<int> nextGreaterElement(const vector<int>& nums1, const vector<int>& nums2) {
    unordered_map<int, int> nxt;
    vector<int> st;                                // decreasing: values still waiting
    for (int x : nums2) {
        while (!st.empty() && st.back() < x) {
            nxt[st.back()] = x;                    // x is the first bigger value
            st.pop_back();
        }
        st.push_back(x);
    }
    vector<int> out;
    for (int v : nums1) {
        auto it = nxt.find(v);
        out.push_back(it == nxt.end() ? -1 : it->second);
    }
    return out;
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<pair<vector<int>, vector<int>>> tests = {
        {{4, 1, 2}, {1, 3, 4, 2}}, {{2, 4}, {1, 2, 3, 4}}, {{3, 2, 1}, {3, 2, 1}}};
    for (auto& [a, b] : tests) {
        cout << "brute: "; print(nextGreaterElementBrute(a, b));
        cout << "stack: "; print(nextGreaterElement(a, b));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - A vector works as a stack: push_back / back / pop_back.
 * - find(first, last, v) - first gives the index of v.
 * - Look up with find() and a default, never operator[] on a read.
 */
