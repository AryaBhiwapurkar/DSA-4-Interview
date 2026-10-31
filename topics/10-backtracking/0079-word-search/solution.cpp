/*
 * 0079. Word Search  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/word-search/
 *
 * Problem: Can `word` be traced on a letter grid through 4-adjacent
 *          cells, each cell used at most once?
 *
 * Examples (board B = ABCE / SFCS / ADEE):
 *   B, "ABCCED"  -> true
 *   B, "SEE"     -> true
 *   B, "ABCB"    -> false
 *   ["a"], "a"   -> true
 *   ["ab"], "ba" -> true
 *   ["aa"], "aaa" -> false (too long)
 *
 * Approaches:
 *   1. DFS + visited grid               O(m*n*3^L) time, O(m*n + L) space
 *   2. In-place mark + count prune  ⭐   O(m*n*3^L) time, O(L) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: DFS + Visited Grid ----------
bool dfsVisited(const vector<vector<char>>& b, const string& w, int r, int c, int i, vector<vector<bool>>& vis) {
    if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size()) return false;
    if (vis[r][c] || b[r][c] != w[i]) return false;
    if (i == (int)w.size() - 1) return true;
    vis[r][c] = true;
    bool found = false;
    for (int d = 0; d < 4 && !found; d++) found = dfsVisited(b, w, r + DR[d], c + DC[d], i + 1, vis);
    vis[r][c] = false;
    return found;
}

bool existVisited(const vector<vector<char>>& board, const string& word) {
    int m = board.size(), n = board[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++)
            if (dfsVisited(board, word, r, c, 0, vis)) return true;
    return false;
}

// ---------- Approach 2: In-Place Mark + Count Prune ⭐ ----------
bool dfs(vector<vector<char>>& b, const string& w, int r, int c, int i) {
    if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size() || b[r][c] != w[i]) return false;
    if (i == (int)w.size() - 1) return true;
    char saved = b[r][c];
    b[r][c] = '#';                         // on the path: can't be reused
    bool found = false;
    for (int d = 0; d < 4 && !found; d++) found = dfs(b, w, r + DR[d], c + DC[d], i + 1);
    b[r][c] = saved;                       // unchoose
    return found;
}

bool exist(vector<vector<char>> board, string word) {
    int m = board.size(), n = board[0].size();
    if ((int)word.size() > m * n) return false;
    unordered_map<char, int> have, need;
    for (auto& row : board) for (char ch : row) have[ch]++;
    for (char ch : word) need[ch]++;
    for (auto& [ch, k] : need) if (have[ch] < k) return false;
    if (have[word.back()] < have[word.front()]) reverse(word.begin(), word.end());   // start from the rarer end
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++)
            if (dfs(board, word, r, c, 0)) return true;
    return false;
}

// ---------- Driver ----------
vector<vector<char>> grid(const vector<string>& rows) {
    vector<vector<char>> g;
    for (auto& s : rows) g.push_back(vector<char>(s.begin(), s.end()));
    return g;
}

int main() {
    vector<string> B = {"ABCE", "SFCS", "ADEE"};
    vector<pair<vector<string>, string>> tests = {
        {B, "ABCCED"}, {B, "SEE"}, {B, "ABCB"}, {{"a"}, "a"}, {{"ab"}, "ba"}, {{"aa"}, "aaa"}
    };
    cout << boolalpha;
    for (auto& [rows, word] : tests) {
        cout << "visited: " << existVisited(grid(rows), word) << "\n";
        cout << "inplace: " << exist(grid(rows), word) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (...; d < 4 && !found; ...)` stops trying directions once found.
 * - cout << boolalpha prints true/false instead of 1/0.
 * - Taking board by value lets the go-to mark cells without touching the caller's copy.
 */
