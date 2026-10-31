/*
 * 0131. Palindrome Partitioning  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/palindrome-partitioning/
 *
 * Problem: Return every way to split s into pieces that are all palindromes.
 *
 * Examples:
 *   "aab"  -> [["a","a","b"],["aa","b"]]
 *   "a"    -> [["a"]]
 *   "efe"  -> [["e","f","e"],["efe"]]
 *   "aaa"  -> [["a","a","a"],["a","aa"],["aa","a"],["aaa"]]
 *
 * Approaches:
 *   1. Backtracking + inline check  ⭐   O(n * 2^n) time, O(n) extra   <- go-to
 *   2. Backtracking + pal table         O(n * 2^n) time, O(n^2) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Backtracking + Inline Check ⭐ ----------
bool isPal(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}

void dfs(const string& s, int start, vector<string>& path, vector<vector<string>>& res) {
    if (start == (int)s.size()) { res.push_back(path); return; }
    for (int end = start; end < (int)s.size(); end++) {
        if (!isPal(s, start, end)) continue;
        path.push_back(s.substr(start, end - start + 1));   // substr takes a length
        dfs(s, end + 1, path, res);
        path.pop_back();
    }
}

vector<vector<string>> partition(const string& s) {
    vector<vector<string>> res;
    vector<string> path;
    dfs(s, 0, path, res);
    return res;
}

// ---------- Approach 2: Backtracking + Palindrome Table ----------
vector<vector<string>> partitionDP(const string& s) {
    int n = s.size();
    vector<vector<bool>> pal(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; i--)       // pal[i][j] needs pal[i+1][j-1]
        for (int j = i; j < n; j++)
            pal[i][j] = s[i] == s[j] && (j - i < 2 || pal[i + 1][j - 1]);

    vector<vector<string>> res;
    vector<string> path;
    function<void(int)> go = [&](int start) {
        if (start == n) { res.push_back(path); return; }
        for (int end = start; end < n; end++) {
            if (!pal[start][end]) continue;
            path.push_back(s.substr(start, end - start + 1));
            go(end + 1);
            path.pop_back();
        }
    };
    go(0);
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
    for (string s : {"aab", "a", "efe", "aaa"}) {
        print("inline", partition(s));
        print("table ", partitionDP(s));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - s.substr(pos, len): the second argument is a length.
 * - function<void(int)> go = [&](int) {...} lets a lambda call itself.
 * - `s[l++] != s[r--]` compares, then moves both pointers inward.
 */
