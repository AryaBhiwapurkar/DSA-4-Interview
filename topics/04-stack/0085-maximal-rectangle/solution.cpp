/*
 * 0085. Maximal Rectangle  |  Hard  |  Stack
 * Link: https://leetcode.com/problems/maximal-rectangle/
 *
 * Problem: Largest all-'1' rectangle area in a binary character matrix.
 *
 * Examples:
 *   [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]  -> 6
 *   [["0"]]                    -> 0
 *   [["1"]]                    -> 1
 *   [["1","1"],["1","1"]]      -> 4
 *   [["0","1"],["1","0"]]      -> 1
 *
 * Approaches:
 *   1. Every rectangle (prefix-sum check)        O(r^2 * c^2) time
 *   2. Row widths, extend upwards                O(r^2 * c) time, O(r * c) space
 *   3. Histogram + monotonic stack  ⭐           O(r * c) time, O(c) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Every Rectangle ----------
int maximalRectangleBrute(const vector<vector<char>>& m) {
    int R = m.size(), C = m[0].size(), best = 0;
    vector<vector<int>> P(R + 1, vector<int>(C + 1, 0));   // 2-D prefix count of ones
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) P[r + 1][c + 1] = (m[r][c] == '1') + P[r][c + 1] + P[r + 1][c] - P[r][c];
    for (int r1 = 0; r1 < R; r1++)
        for (int c1 = 0; c1 < C; c1++)
            for (int r2 = r1; r2 < R; r2++)
                for (int c2 = c1; c2 < C; c2++) {
                    int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                    int ones = P[r2 + 1][c2 + 1] - P[r1][c2 + 1] - P[r2 + 1][c1] + P[r1][c1];
                    if (ones == area) best = max(best, area);
                }
    return best;
}

// ---------- Approach 2: Row Widths ----------
int maximalRectangleWidths(const vector<vector<char>>& m) {
    int R = m.size(), C = m[0].size(), best = 0;
    vector<vector<int>> w(R, vector<int>(C, 0));   // run of ones ending here, going left
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (m[r][c] != '1') continue;
            w[r][c] = (c ? w[r][c - 1] : 0) + 1;
            int width = w[r][c];
            for (int k = r; k >= 0 && w[k][c] > 0; k--) {   // extend upwards
                width = min(width, w[k][c]);
                best = max(best, width * (r - k + 1));
            }
        }
    return best;
}

// ---------- Approach 3: Histogram + Stack ⭐ ----------
int largestRectangle(const vector<int>& h) {
    vector<int> st;
    int best = 0, n = h.size();
    for (int i = 0; i <= n; i++) {
        int cur = i < n ? h[i] : 0;                // sentinel 0 flushes the stack
        while (!st.empty() && h[st.back()] > cur) {
            int height = h[st.back()];
            st.pop_back();
            int left = st.empty() ? -1 : st.back();
            best = max(best, height * (i - left - 1));
        }
        st.push_back(i);
    }
    return best;
}

int maximalRectangle(const vector<vector<char>>& m) {
    vector<int> h(m[0].size(), 0);
    int best = 0;
    for (auto& row : m) {
        for (size_t c = 0; c < row.size(); c++) h[c] = row[c] == '1' ? h[c] + 1 : 0;   // reset on '0'
        best = max(best, largestRectangle(h));
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<char>>> tests = {
        {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}},
        {{'0'}}, {{'1'}}, {{'1', '1'}, {'1', '1'}}, {{'0', '1'}, {'1', '0'}}};
    for (auto& t : tests) {
        cout << "brute    : " << maximalRectangleBrute(t) << "\n";
        cout << "widths   : " << maximalRectangleWidths(t) << "\n";
        cout << "histogram: " << maximalRectangle(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (m[r][c] == '1') is a bool that adds as 0/1 in arithmetic.
 * - Pushing index n with a sentinel height 0 flushes every bar without a cleanup loop.
 * - Compare chars with '1', not the int 1.
 */
