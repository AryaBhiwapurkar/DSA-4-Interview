/*
 * 0269. Alien Dictionary  |  Hard  |  Advanced Graphs
 * Link: https://leetcode.com/problems/alien-dictionary/
 *
 * Problem: Words are sorted by an unknown alphabet. Return a letter order
 *          consistent with them, or "" if none exists.
 *
 * Examples:
 *   ["wrt","wrf","er","ett","rftt"]  -> "wertf"
 *   ["z","x"]                        -> "zx"
 *   ["z","x","z"]                    -> "" (z<x and x<z: cycle)
 *   ["abc","ab"]                     -> "" (longer word before its prefix)
 *   ["z","z"]                        -> "z"
 *
 * Approaches:
 *   1. DFS post-order (three colors)  O(C) time, O(1) space (26 letters)
 *   2. Kahn's BFS  ⭐                  O(C) time, O(1) space   <- go-to
 *   C = total characters in all words.
 */

#include <bits/stdc++.h>
using namespace std;

// Builds letter set + edges; returns false if a word comes before its own prefix.
bool buildGraph(const vector<string>& words, map<char, set<char>>& adj) {
    for (auto& w : words)
        for (char c : w) adj[c];                  // every letter is a node, even without edges
    for (size_t i = 0; i + 1 < words.size(); i++) {
        const string &a = words[i], &b = words[i + 1];
        size_t j = 0;
        while (j < a.size() && j < b.size() && a[j] == b[j]) j++;
        if (j < a.size() && j < b.size()) adj[a[j]].insert(b[j]);   // first difference only
        else if (a.size() > b.size()) return false;                 // "abc" before "ab"
    }
    return true;
}

// ---------- Approach 1: DFS post-order ----------
bool dfs(char u, map<char, set<char>>& adj, map<char, int>& color, string& out) {
    color[u] = 1;                                 // 1 = on the current path
    for (char v : adj[u]) {
        if (color[v] == 1) return false;          // back edge: cycle
        if (color[v] == 0 && !dfs(v, adj, color, out)) return false;
    }
    color[u] = 2;                                 // 2 = done
    out += u;
    return true;
}

string alienOrderDFS(const vector<string>& words) {
    map<char, set<char>> adj;
    if (!buildGraph(words, adj)) return "";
    map<char, int> color;
    string out;
    for (auto& [c, _] : adj)
        if (color[c] == 0 && !dfs(c, adj, color, out)) return "";
    reverse(out.begin(), out.end());              // post-order reversed = topological order
    return out;
}

// ---------- Approach 2: Kahn's BFS ⭐ ----------
string alienOrder(const vector<string>& words) {
    map<char, set<char>> adj;
    if (!buildGraph(words, adj)) return "";
    map<char, int> indeg;
    for (auto& [c, nbrs] : adj) {
        indeg[c];
        for (char v : nbrs) indeg[v]++;
    }
    queue<char> q;
    for (auto& [c, d] : indeg)
        if (d == 0) q.push(c);
    string out;
    while (!q.empty()) {
        char u = q.front(); q.pop();
        out += u;
        for (char v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return out.size() == adj.size() ? out : "";   // leftovers mean a cycle
}

// ---------- Driver ----------
int main() {
    vector<vector<string>> tests = {
        {"wrt", "wrf", "er", "ett", "rftt"}, {"z", "x"}, {"z", "x", "z"}, {"abc", "ab"}, {"z", "z"}
    };
    for (auto& w : tests) {
        cout << "dfs : \"" << alienOrderDFS(w) << "\"\n";
        cout << "kahn: \"" << alienOrder(w) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `adj[c];` on a map inserts c with an empty set: a cheap way to register a node.
 * - set<char> dedups edges, so a repeated pair doesn't inflate indegrees.
 * - `const string &a = ..., &b = ...;` the & binds to each name separately.
 * - `for (auto& [c, _] : adj)` iterates map entries in key order.
 */
