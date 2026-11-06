/*
 * 0048. Rotate Image  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/rotate-image/
 *
 * Problem: Rotate an n x n matrix 90 degrees clockwise, in place.
 *
 * Examples:
 *   [[1,2,3],[4,5,6],[7,8,9]]  -> [[7,4,1],[8,5,2],[9,6,3]]
 *   [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
 *       -> [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 *   [[1]]                      -> [[1]]
 *   [[1,2],[3,4]]              -> [[3,1],[4,2]]
 *
 * Approaches:
 *   1. Copy into a new matrix       O(n^2) time, O(n^2) space
 *   2. Transpose + reverse rows  ⭐  O(n^2) time, O(1) space   <- go-to
 *   3. Rotate four cells at a time  O(n^2) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Copy ----------
void rotateCopy(vector<vector<int>>& m) {
    int n = m.size();
    vector<vector<int>> out(n, vector<int>(n));
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) out[c][n - 1 - r] = m[r][c];
    m = out;
}

// ---------- Approach 2: Transpose + Reverse ⭐ ----------
void rotate(vector<vector<int>>& m) {
    int n = m.size();
    for (int r = 0; r < n; r++)
        for (int c = r + 1; c < n; c++) swap(m[r][c], m[c][r]);   // above the diagonal only
    for (auto& row : m) reverse(row.begin(), row.end());
}

// ---------- Approach 3: Four-way Swap ----------
void rotateFour(vector<vector<int>>& m) {
    int n = m.size();
    for (int r = 0; r < n / 2; r++)                // rings
        for (int c = r; c < n - 1 - r; c++) {      // each cell on the ring's top edge
            int tmp = m[r][c];
            m[r][c] = m[n - 1 - c][r];             // left -> top
            m[n - 1 - c][r] = m[n - 1 - r][n - 1 - c];   // bottom -> left
            m[n - 1 - r][n - 1 - c] = m[c][n - 1 - r];   // right -> bottom
            m[c][n - 1 - r] = tmp;                 // top -> right
        }
}

// ---------- Driver ----------
void print(const vector<vector<int>>& m) {
    cout << "[";
    for (size_t r = 0; r < m.size(); r++) {
        cout << (r ? "," : "") << "[";
        for (size_t c = 0; c < m[r].size(); c++) cout << (c ? "," : "") << m[r][c];
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
        {{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}},
        {{1}},
        {{1, 2}, {3, 4}}};
    for (auto& t : tests) {
        auto a = t, b = t, c = t;
        rotateCopy(a); rotate(b); rotateFour(c);
        cout << "copy     : "; print(a);
        cout << "transpose: "; print(b);
        cout << "four-way : "; print(c);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - swap(a, b) swaps two lvalues, including matrix cells.
 * - reverse(row.begin(), row.end()) reverses one row in place.
 * - auto a = t copies a vector<vector<int>> (deep copy).
 */
