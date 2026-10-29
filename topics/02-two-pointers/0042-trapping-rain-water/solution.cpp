/*
 * 0042. Trapping Rain Water  |  Hard  |  Two Pointers
 * Link: https://leetcode.com/problems/trapping-rain-water/
 *
 * Problem: Given bar heights (width 1), return the total water trapped.
 *
 * Examples:
 *   [0,1,0,2,1,0,1,3,2,1,2,1]  -> 6
 *   [4,2,0,3,2,5]              -> 9
 *   [3,0,3]                    -> 3
 *   [1,2,3]                    -> 0
 *
 * Approaches:
 *   1. Brute force                O(n^2) time, O(1) space
 *   2. Prefix/suffix max arrays   O(n) time, O(n) space
 *   3. Monotonic stack            O(n) time, O(n) space
 *   4. Two pointers  ⭐            O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
int trapBrute(const vector<int>& h) {
    int n = h.size(), total = 0;
    for (int i = 0; i < n; i++) {
        int L = *max_element(h.begin(), h.begin() + i + 1);
        int R = *max_element(h.begin() + i, h.end());
        total += min(L, R) - h[i];
    }
    return total;
}

// ---------- Approach 2: Prefix/Suffix Max Arrays ----------
int trapArrays(const vector<int>& h) {
    int n = h.size(), total = 0;
    vector<int> L(n), R(n);
    for (int i = 0; i < n; i++) L[i] = max(h[i], i ? L[i - 1] : 0);          // includes h[i]
    for (int i = n - 1; i >= 0; i--) R[i] = max(h[i], i < n - 1 ? R[i + 1] : 0);
    for (int i = 0; i < n; i++) total += min(L[i], R[i]) - h[i];
    return total;
}

// ---------- Approach 3: Monotonic Stack ----------
int trapStack(const vector<int>& h) {
    stack<int> st;                                       // indices with decreasing heights
    int total = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        while (!st.empty() && h[i] > h[st.top()]) {
            int bottom = st.top();
            st.pop();
            if (st.empty()) break;                       // no left wall
            int left = st.top();
            int width = i - left - 1;
            int depth = min(h[left], h[i]) - h[bottom];  // fill one horizontal layer
            total += width * depth;
        }
        st.push(i);
    }
    return total;
}

// ---------- Approach 4: Two Pointers ⭐ ----------
int trap(const vector<int>& h) {
    int l = 0, r = h.size() - 1, leftMax = 0, rightMax = 0, total = 0;
    while (l < r) {
        if (h[l] < h[r]) {                               // right side has a wall >= h[l]: left is the bottleneck
            leftMax = max(leftMax, h[l]);
            total += leftMax - h[l];
            l++;
        } else {
            rightMax = max(rightMax, h[r]);
            total += rightMax - h[r];
            r--;
        }
    }
    return total;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, {4, 2, 0, 3, 2, 5}, {3, 0, 3}, {1, 2, 3}};
    for (auto& h : tests) {
        cout << "brute   : " << trapBrute(h) << "\n";
        cout << "arrays  : " << trapArrays(h) << "\n";
        cout << "stack   : " << trapStack(h) << "\n";
        cout << "pointers: " << trap(h) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - *max_element(first, last) dereferences the iterator to the max.
 * - std::stack: push/top/pop; pop() returns void, read top() first.
 * - Ternaries guard the first/last index when filling prefix arrays.
 */
