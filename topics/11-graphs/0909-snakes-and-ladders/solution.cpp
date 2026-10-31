/*
 * 0909. Snakes and Ladders  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/snakes-and-ladders/
 *
 * Problem: Zigzag-numbered n x n board, start at 1, each move rolls 1-6 and
 *          follows at most one snake/ladder. Fewest moves to reach n^2, or -1.
 *
 * Examples:
 *   6x6 LeetCode board (2->15, 14->35, 17->13)   -> 4
 *   [[-1,-1],[-1,3]]                             -> 1
 *   [[-1,-1,-1],[-1,9,8],[-1,8,9]]               -> 1 (3 is a ladder to 9)
 *   [[1,1,-1],[1,1,1],[-1,1,1]]                  -> -1 (every roll slides back to 1)
 *
 * Approaches:
 *   1. BFS with on-the-fly coordinates    O(n^2) time, O(n^2) space
 *   2. Flatten + BFS  ⭐                   O(n^2) time, O(n^2) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// square s (1-based) -> (row, col) on the zigzag board
pair<int, int> cell(int s, int n) {
    int q = (s - 1) / n, c = (s - 1) % n;
    if (q % 2 == 1) c = n - 1 - c;         // odd rows (from the bottom) run right-to-left
    return {n - 1 - q, c};
}

// ---------- Approach 1: BFS with On-the-Fly Coordinates ----------
int snakesAndLaddersCoords(const vector<vector<int>>& board) {
    int n = board.size(), target = n * n;
    vector<int> dist(target + 1, -1);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int s = q.front(); q.pop();
        for (int t = s + 1; t <= min(s + 6, target); t++) {
            auto [r, c] = cell(t, n);
            int dest = board[r][c] == -1 ? t : board[r][c];
            if (dist[dest] != -1) continue;
            dist[dest] = dist[s] + 1;
            if (dest == target) return dist[dest];
            q.push(dest);
        }
    }
    return -1;
}

// ---------- Approach 2: Flatten + BFS ⭐ ----------
int snakesAndLadders(const vector<vector<int>>& board) {
    int n = board.size(), target = n * n;
    vector<int> jump(target + 1);
    for (int s = 1; s <= target; s++) {
        auto [r, c] = cell(s, n);
        jump[s] = board[r][c];
    }
    vector<int> dist(target + 1, -1);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int s = q.front(); q.pop();
        for (int t = s + 1; t <= min(s + 6, target); t++) {
            int dest = jump[t] == -1 ? t : jump[t];   // one jump per roll, no chaining
            if (dist[dest] != -1) continue;           // visit the square you end on
            dist[dest] = dist[s] + 1;
            if (dest == target) return dist[dest];
            q.push(dest);
        }
    }
    return -1;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{-1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1},
         {-1, 35, -1, -1, 13, -1}, {-1, -1, -1, -1, -1, -1}, {-1, 15, -1, -1, -1, -1}},
        {{-1, -1}, {-1, 3}},
        {{-1, -1, -1}, {-1, 9, 8}, {-1, 8, 9}},
        {{1, 1, -1}, {1, 1, 1}, {-1, 1, 1}},
    };
    for (auto& b : tests) {
        cout << "coords : " << snakesAndLaddersCoords(b) << "\n";
        cout << "flatten: " << snakesAndLadders(b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Returning pair<int,int> and unpacking with auto [r, c] keeps index math in one helper.
 * - dist initialised to -1 doubles as the visited marker.
 */
