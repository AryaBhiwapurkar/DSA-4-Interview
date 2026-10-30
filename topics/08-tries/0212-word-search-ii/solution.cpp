/*
 * 0212. Word Search II  |  Hard  |  Tries
 * Link: https://leetcode.com/problems/word-search-ii/
 *
 * Problem: Return all words that can be traced on the board through
 *          horizontally/vertically adjacent cells, each cell used once per word.
 *
 * Examples (printed sorted):
 *   [[o,a,a,n],[e,t,a,e],[i,h,k,r],[i,f,l,v]], [oath,pea,eat,rain]  -> [eat,oath]
 *   [[a,b],[c,d]], [abcb]                                          -> []
 *   [[a]], [a,b]                                                   -> [a]
 *   [[o,a,b,n],[o,t,a,e],[a,h,k,r],[a,f,l,v]], [oa,oaa]            -> [oa,oaa]
 *
 * Approaches:
 *   1. Word search per word        O(W * m*n * 4*3^(L-1))
 *   2. Trie + backtracking  ⭐      O(m*n * 4*3^(L-1)) worst case   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const int DR[4] = {1, -1, 0, 0}, DC[4] = {0, 0, 1, -1};

// ---------- Approach 1: Word Search Per Word ----------
bool exist(vector<vector<char>>& b, const string& w, int r, int c, size_t i) {
    if (i == w.size()) return true;
    if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size() || b[r][c] != w[i]) return false;
    char saved = b[r][c];
    b[r][c] = '#';                         // mark visited
    bool found = false;
    for (int d = 0; d < 4 && !found; d++) found = exist(b, w, r + DR[d], c + DC[d], i + 1);
    b[r][c] = saved;                       // unmark on backtrack
    return found;
}

vector<string> findWordsBrute(vector<vector<char>> board, const vector<string>& words) {
    vector<string> res;
    for (auto& w : words) {
        bool found = false;
        for (size_t r = 0; r < board.size() && !found; r++)
            for (size_t c = 0; c < board[0].size() && !found; c++) found = exist(board, w, r, c, 0);
        if (found) res.push_back(w);
    }
    return res;
}

// ---------- Approach 2: Trie + Backtracking ⭐ ----------
struct TrieNode {
    TrieNode* next[26] = {};
    string word;                           // non-empty at the end of a word
    int children = 0;                      // for pruning empty branches
};

void dfs(vector<vector<char>>& b, int r, int c, TrieNode* parent, vector<string>& res) {
    char ch = b[r][c];
    TrieNode* node = parent->next[ch - 'a'];
    if (!node->word.empty()) {
        res.push_back(node->word);
        node->word.clear();                // avoid duplicates
    }
    b[r][c] = '#';
    for (int d = 0; d < 4; d++) {
        int nr = r + DR[d], nc = c + DC[d];
        if (nr < 0 || nc < 0 || nr >= (int)b.size() || nc >= (int)b[0].size()) continue;
        char nx = b[nr][nc];
        if (nx != '#' && node->next[nx - 'a']) dfs(b, nr, nc, node, res);   // stay inside the trie
    }
    b[r][c] = ch;
    if (node->children == 0 && node->word.empty()) {   // prune a fully used branch
        parent->next[ch - 'a'] = nullptr;
        parent->children--;
    }
}

vector<string> findWords(vector<vector<char>> board, const vector<string>& words) {
    TrieNode* root = new TrieNode();
    for (auto& w : words) {
        TrieNode* n = root;
        for (char ch : w) {
            if (!n->next[ch - 'a']) { n->next[ch - 'a'] = new TrieNode(); n->children++; }
            n = n->next[ch - 'a'];
        }
        n->word = w;
    }
    vector<string> res;
    for (size_t r = 0; r < board.size(); r++)
        for (size_t c = 0; c < board[0].size(); c++)
            if (root->next[board[r][c] - 'a']) dfs(board, r, c, root, res);
    return res;
}

// ---------- Driver ----------
vector<vector<char>> grid(const vector<string>& rows) {
    vector<vector<char>> g;
    for (auto& s : rows) g.push_back(vector<char>(s.begin(), s.end()));
    return g;
}

void print(const string& label, vector<string> v) {
    sort(v.begin(), v.end());              // normalize: any order is accepted
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << '"' << v[i] << '"';
    cout << "]\n";
}

int main() {
    vector<pair<vector<string>, vector<string>>> tests = {
        {{"oaan", "etae", "ihkr", "iflv"}, {"oath", "pea", "eat", "rain"}},
        {{"ab", "cd"}, {"abcb"}},
        {{"a"}, {"a", "b"}},
        {{"oabn", "otae", "ahkr", "aflv"}, {"oa", "oaa"}},
    };
    for (auto& [rows, words] : tests) {
        print("brute", findWordsBrute(grid(rows), words));
        print("trie ", findWords(grid(rows), words));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Direction arrays DR/DC turn four neighbour checks into one loop.
 * - Marking a cell with '#' (then restoring it) avoids a separate visited grid.
 * - vector<char>(s.begin(), s.end()) turns a string row into a char row.
 */
