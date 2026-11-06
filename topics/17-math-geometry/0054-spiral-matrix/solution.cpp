/*
 * 0054. Spiral Matrix  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/spiral-matrix/
 *
 * Problem: Return all elements of an m x n matrix in clockwise spiral order.
 *
 * Examples:
 *   [[1,2,3],[4,5,6],[7,8,9]]             -> [1,2,3,6,9,8,7,4,5]
 *   [[1,2,3,4],[5,6,7,8],[9,10,11,12]]    -> [1,2,3,4,8,12,11,10,9,5,6,7]
 *   [[1,2,3]]                             -> [1,2,3]
 *   [[1],[2],[3]]                         -> [1,2,3]
 *   [[7]]                                 -> [7]
 *
 * Approaches:
 *   1. Direction vectors + visited grid   O(m*n) time, O(m*n) space
 *   2. Shrinking boundaries  ⭐            O(m*n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Direction Vectors ----------
vector<int> spiralOrderVisited(const vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<vector<bool>> seen(m, vector<bool>(n, false));
    int dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};    // right, down, left, up
    vector<int> out;
    int r = 0, c = 0, d = 0;
    for (int k = 0; k < m * n; k++) {
        out.push_back(mat[r][c]);
        seen[r][c] = true;
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= m || nc < 0 || nc >= n || seen[nr][nc]) {
            d = (d + 1) % 4;                           // turn right
            nr = r + dr[d], nc = c + dc[d];
        }
        r = nr, c = nc;
    }
    return out;
}

// ---------- Approach 2: Shrinking Boundaries ⭐ ----------
vector<int> spiralOrder(const vector<vector<int>>& mat) {
    int top = 0, bottom = mat.size() - 1, left = 0, right = mat[0].size() - 1;
    vector<int> out;
    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; c++) out.push_back(mat[top][c]);
        top++;
        for (int r = top; r <= bottom; r++) out.push_back(mat[r][right]);
        right--;
        if (top <= bottom) {                           // a row is still left
            for (int c = right; c >= left; c--) out.push_back(mat[bottom][c]);
            bottom--;
        }
        if (left <= right) {                           // a column is still left
            for (int r = bottom; r >= top; r--) out.push_back(mat[r][left]);
            left++;
        }
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
    vector<vector<vector<int>>> tests = {
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
        {{1, 2, 3}},
        {{1}, {2}, {3}},
        {{7}}};
    for (auto& t : tests) {
        cout << "visited : "; print(spiralOrderVisited(t));
        cout << "boundary: "; print(spiralOrder(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Parallel dr[]/dc[] arrays plus d = (d + 1) % 4 encode "turn right".
 * - vector<vector<bool>> grid(m, vector<bool>(n, false)) builds a 2-D flag grid.
 * - Keep boundaries as int: mat.size() - 1 is size_t and can't go below 0.
 */
