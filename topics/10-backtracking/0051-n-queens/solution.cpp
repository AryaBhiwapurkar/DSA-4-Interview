/*
 * 0051. N-Queens  |  Hard  |  Backtracking
 * Link: https://leetcode.com/problems/n-queens/
 *
 * Problem: Return every placement of n non-attacking queens on an n x n
 *          board, as row strings of 'Q' and '.'.
 *
 * Examples:
 *   n 4  -> [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 *   n 1  -> [["Q"]]
 *   n 2  -> []
 *   n 3  -> []
 *   n 8  -> 92 solutions (count printed)
 *
 * Approaches:
 *   1. Backtracking + board scan      O(n! * n) time, O(n^2) space
 *   2. Backtracking + col/diag sets ⭐ O(n!) time, O(n) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Backtracking + Board Scan ----------
bool safe(const vector<string>& b, int r, int c) {
    int n = b.size();
    for (int i = 0; i < r; i++) if (b[i][c] == 'Q') return false;
    for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--) if (b[i][j] == 'Q') return false;
    for (int i = r - 1, j = c + 1; i >= 0 && j < n; i--, j++) if (b[i][j] == 'Q') return false;
    return true;                           // rows below r are still empty
}

void scan(int r, vector<string>& b, vector<vector<string>>& res) {
    int n = b.size();
    if (r == n) { res.push_back(b); return; }
    for (int c = 0; c < n; c++) {
        if (!safe(b, r, c)) continue;
        b[r][c] = 'Q';
        scan(r + 1, b, res);
        b[r][c] = '.';
    }
}

vector<vector<string>> solveNQueensScan(int n) {
    vector<vector<string>> res;
    vector<string> b(n, string(n, '.'));
    scan(0, b, res);
    return res;
}

// ---------- Approach 2: Backtracking + Column/Diagonal Sets ⭐ ----------
void place(int r, int n, vector<string>& b, vector<bool>& cols, vector<bool>& diag,
           vector<bool>& anti, vector<vector<string>>& res) {
    if (r == n) { res.push_back(b); return; }
    for (int c = 0; c < n; c++) {
        int d = r - c + n - 1, a = r + c;  // "\" diagonal has constant r-c, "/" has r+c
        if (cols[c] || diag[d] || anti[a]) continue;
        cols[c] = diag[d] = anti[a] = true;
        b[r][c] = 'Q';
        place(r + 1, n, b, cols, diag, anti, res);
        b[r][c] = '.';
        cols[c] = diag[d] = anti[a] = false;
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> b(n, string(n, '.'));
    vector<bool> cols(n), diag(2 * n - 1), anti(2 * n - 1);
    place(0, n, b, cols, diag, anti, res);
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<vector<string>> v) {
    sort(v.begin(), v.end());              // normalize: any order is accepted
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < v[i].size(); j++) cout << (j ? "," : "") << '"' << v[i][j] << '"';
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    for (int n : {4, 1, 2, 3}) {
        print("scan", solveNQueensScan(n));
        print("sets", solveNQueens(n));
        cout << "---\n";
    }
    cout << "scan n=8 count: " << solveNQueensScan(8).size() << "\n";
    cout << "sets n=8 count: " << solveNQueens(8).size() << "\n";
}

/*
 * Syntax notes (C++):
 * - string(n, '.') builds a row of n dots; vector<string> b(n, row) builds the board.
 * - Chained assignment `a = b = c = true` sets all three flags.
 * - Two-variable for loop: `for (int i = r - 1, j = c - 1; ...; i--, j--)`.
 */
