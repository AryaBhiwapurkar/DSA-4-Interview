/*
 * 0304. Range Sum Query 2D - Immutable  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/range-sum-query-2d-immutable/
 *
 * Problem: Fixed matrix, many queries: sum of the rectangle (r1,c1)..(r2,c2) inclusive.
 *
 * Examples:
 *   matrix = [[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]
 *   sumRegion(2,1,4,3) -> 8
 *   sumRegion(1,1,2,2) -> 11
 *   sumRegion(1,2,2,4) -> 12
 *   sumRegion(0,0,0,0) -> 3    (single cell)
 *   sumRegion(0,0,4,4) -> 58   (whole matrix)
 *
 * Approaches:
 *   1. Loop over the rectangle   O(1) build, O(m*n) per query
 *   2. Row prefix sums           O(m*n) build, O(m) per query
 *   3. 2-D prefix sums  ⭐       O(m*n) build, O(1) per query   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Loop ----------
class NumMatrixBrute {
    vector<vector<int>> a;

public:
    NumMatrixBrute(const vector<vector<int>>& m) : a(m) {}
    int sumRegion(int r1, int c1, int r2, int c2) {
        int s = 0;
        for (int r = r1; r <= r2; r++)
            for (int c = c1; c <= c2; c++) s += a[r][c];
        return s;
    }
};

// ---------- Approach 2: Row Prefix Sums ----------
class NumMatrixRows {
    vector<vector<int>> P;                         // P[r][c] = sum of row r, cols 0..c-1

public:
    NumMatrixRows(const vector<vector<int>>& m) {
        for (auto& row : m) {
            vector<int> p(row.size() + 1, 0);
            for (size_t c = 0; c < row.size(); c++) p[c + 1] = p[c] + row[c];
            P.push_back(p);
        }
    }
    int sumRegion(int r1, int c1, int r2, int c2) {
        int s = 0;
        for (int r = r1; r <= r2; r++) s += P[r][c2 + 1] - P[r][c1];
        return s;
    }
};

// ---------- Approach 3: 2-D Prefix Sums ⭐ ----------
class NumMatrix {
    vector<vector<int>> P;                         // P[r][c] = sum of top-left r x c block

public:
    NumMatrix(const vector<vector<int>>& m) {
        int R = m.size(), C = m[0].size();
        P.assign(R + 1, vector<int>(C + 1, 0));    // zero row/col padding
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                P[r + 1][c + 1] = m[r][c] + P[r][c + 1] + P[r + 1][c] - P[r][c];
    }
    int sumRegion(int r1, int c1, int r2, int c2) {
        return P[r2 + 1][c2 + 1] - P[r1][c2 + 1] - P[r2 + 1][c1] + P[r1][c1];   // add back the corner
    }
};

// ---------- Driver ----------
int main() {
    vector<vector<int>> m = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5},
                             {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    NumMatrixBrute b(m);
    NumMatrixRows rw(m);
    NumMatrix p(m);
    vector<array<int, 4>> qs = {{2, 1, 4, 3}, {1, 1, 2, 2}, {1, 2, 2, 4}, {0, 0, 0, 0}, {0, 0, 4, 4}};
    for (auto [r1, c1, r2, c2] : qs) {
        cout << "brute: " << b.sumRegion(r1, c1, r2, c2) << "\n";
        cout << "rows : " << rw.sumRegion(r1, c1, r2, c2) << "\n";
        cout << "2-D  : " << p.sumRegion(r1, c1, r2, c2) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - v.assign(n, value) resizes and fills in one call (handy inside a constructor body).
 * - Structured bindings work on std::array: auto [a, b, c, d] = arr.
 * - Padding with a zero row/col avoids every "r - 1 < 0" branch.
 */
