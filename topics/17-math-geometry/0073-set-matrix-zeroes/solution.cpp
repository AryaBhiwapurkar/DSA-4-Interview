/*
 * 0073. Set Matrix Zeroes  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/set-matrix-zeroes/
 *
 * Problem: For every 0 in an m x n matrix, set its whole row and column to 0, in place.
 *
 * Examples:
 *   [[1,1,1],[1,0,1],[1,1,1]]         -> [[1,0,1],[0,0,0],[1,0,1]]
 *   [[0,1,2,0],[3,4,5,2],[1,3,1,5]]   -> [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 *   [[1,0],[1,1]]                     -> [[0,0],[1,0]]
 *   [[1],[0]]                         -> [[0],[0]]
 *   [[5]]                             -> [[5]]
 *
 * Approaches:
 *   1. Copy the matrix                O(m*n) time, O(m*n) space
 *   2. Row and column sets            O(m*n) time, O(m+n) space
 *   3. First row/col markers  ⭐      O(m*n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Copy ----------
void setZeroesCopy(vector<vector<int>>& mat) {
    auto orig = mat;
    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (orig[i][j] == 0) {                 // read the copy, write the real one
                for (int c = 0; c < n; c++) mat[i][c] = 0;
                for (int r = 0; r < m; r++) mat[r][j] = 0;
            }
}

// ---------- Approach 2: Row and Column Sets ----------
void setZeroesSets(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<bool> zeroRow(m, false), zeroCol(n, false);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j] == 0) zeroRow[i] = zeroCol[j] = true;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (zeroRow[i] || zeroCol[j]) mat[i][j] = 0;
}

// ---------- Approach 3: First Row/Col Markers ⭐ ----------
void setZeroes(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    bool col0 = false;                             // m[0][0] already flags row 0
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j] == 0) {
                mat[i][0] = 0;                     // row i flag
                if (j == 0) col0 = true;
                else mat[0][j] = 0;                // column j flag
            }
    for (int i = 1; i < m; i++)                    // inner cells first: flags still intact
        for (int j = 1; j < n; j++)
            if (mat[i][0] == 0 || mat[0][j] == 0) mat[i][j] = 0;
    if (mat[0][0] == 0)
        for (int j = 0; j < n; j++) mat[0][j] = 0;
    if (col0)
        for (int i = 0; i < m; i++) mat[i][0] = 0;
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
        {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
        {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}},
        {{1, 0}, {1, 1}},
        {{1}, {0}},
        {{5}}};
    for (auto& t : tests) {
        auto a = t, b = t, c = t;
        setZeroesCopy(a); setZeroesSets(b); setZeroes(c);
        cout << "copy   : "; print(a);
        cout << "sets   : "; print(b);
        cout << "markers: "; print(c);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - zeroRow[i] = zeroCol[j] = true chains assignment (right to left).
 * - auto orig = mat makes a full copy of a nested vector.
 * - vector<bool> is bit-packed: fine for flags, but you can't take &v[i].
 */
