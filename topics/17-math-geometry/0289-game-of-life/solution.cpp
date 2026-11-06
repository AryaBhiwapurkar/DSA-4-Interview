/*
 * 0289. Game of Life  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/game-of-life/
 *
 * Problem: Advance Conway's Game of Life one generation, in place.
 *          Live: survives with 2 or 3 live neighbours. Dead: born with exactly 3.
 *
 * Examples:
 *   [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]  -> [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
 *   [[1,1],[1,0]]                      -> [[1,1],[1,1]]
 *   [[1]]                              -> [[0]]
 *   [[0,1,0],[0,1,0],[0,1,0]]          -> [[0,0,0],[1,1,1],[0,0,0]]   (blinker)
 *
 * Approaches:
 *   1. Copy the board                O(m*n) time, O(m*n) space
 *   2. Two-bit state encoding  ⭐    O(m*n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

int liveNeighbours(const vector<vector<int>>& b, int r, int c) {
    int m = b.size(), n = b[0].size(), cnt = 0;
    for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) cnt += b[nr][nc] & 1;   // bit 0 = old state
        }
    return cnt;
}

// ---------- Approach 1: Copy ----------
void gameOfLifeCopy(vector<vector<int>>& board) {
    auto old = board;
    for (int r = 0; r < (int)board.size(); r++)
        for (int c = 0; c < (int)board[0].size(); c++) {
            int k = liveNeighbours(old, r, c);
            board[r][c] = (k == 3 || (old[r][c] && k == 2)) ? 1 : 0;
        }
}

// ---------- Approach 2: Bit Encoding ⭐ ----------
void gameOfLife(vector<vector<int>>& board) {
    for (int r = 0; r < (int)board.size(); r++)
        for (int c = 0; c < (int)board[0].size(); c++) {
            int k = liveNeighbours(board, r, c);
            if (k == 3 || ((board[r][c] & 1) && k == 2)) board[r][c] |= 2;   // bit 1 = next state
        }
    for (auto& row : board)
        for (int& cell : row) cell >>= 1;          // promote next state
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
        {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}},
        {{1, 1}, {1, 0}},
        {{1}},
        {{0, 1, 0}, {0, 1, 0}, {0, 1, 0}}};
    for (auto& t : tests) {
        auto a = t, b = t;
        gameOfLifeCopy(a); gameOfLife(b);
        cout << "copy: "; print(a);
        cout << "bits: "; print(b);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - x & 1 reads bit 0, x |= 2 sets bit 1, x >>= 1 shifts bit 1 down to bit 0.
 * - Range-for with int& cell modifies elements in place.
 * - Two nested dr/dc loops from -1 to 1 cover all 8 neighbours (skip 0,0).
 */
