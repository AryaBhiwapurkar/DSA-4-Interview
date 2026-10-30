/*
 * 0211. Design Add and Search Words Data Structure  |  Medium  |  Tries
 * Link: https://leetcode.com/problems/design-add-and-search-words-data-structure/
 *
 * Problem: addWord(word); search(pattern) where '.' matches any one letter.
 *
 * Examples:
 *   add bad, add dad, add mad, search pad, search bad, search .ad, search b..
 *     -> [null,null,null,null,false,true,true,true]
 *   add a, search ., search a., search ..
 *     -> [null,null,true,false,false]
 *
 * Approaches:
 *   1. List of words, compare each   O(N*L) per search
 *   2. Trie + wildcard DFS  ⭐        O(L) add, O(26^dots * L) search   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: List of Words ----------
class WordDictionaryList {
    vector<string> words;
public:
    void addWord(const string& w) { words.push_back(w); }
    bool search(const string& p) {
        for (auto& w : words) {
            if (w.size() != p.size()) continue;
            bool ok = true;
            for (size_t i = 0; i < p.size() && ok; i++) ok = p[i] == '.' || p[i] == w[i];
            if (ok) return true;
        }
        return false;
    }
};

// ---------- Approach 2: Trie + Wildcard DFS ⭐ ----------
class WordDictionary {
    struct Node {
        Node* next[26] = {};
        bool isEnd = false;
    };
    Node* root = new Node();

    bool dfs(Node* n, const string& p, size_t i) {
        if (i == p.size()) return n->isEnd;    // whole pattern consumed
        if (p[i] != '.') {
            Node* c = n->next[p[i] - 'a'];
            return c && dfs(c, p, i + 1);      // one fixed branch
        }
        for (Node* c : n->next)                // '.': try every existing child
            if (c && dfs(c, p, i + 1)) return true;
        return false;
    }

public:
    void addWord(const string& w) {
        Node* n = root;
        for (char ch : w) {
            if (!n->next[ch - 'a']) n->next[ch - 'a'] = new Node();
            n = n->next[ch - 'a'];
        }
        n->isEnd = true;
    }
    bool search(const string& p) { return dfs(root, p, 0); }
};

// ---------- Driver ----------
template <class D>
void run(const string& label, const vector<string>& ops, const vector<string>& args) {
    D d;
    cout << label << ": [null" << boolalpha;
    for (size_t i = 1; i < ops.size(); i++) {
        if (ops[i] == "addWord") { d.addWord(args[i]); cout << ",null"; }
        else cout << "," << d.search(args[i]);
    }
    cout << "]\n";
}

int main() {
    vector<pair<vector<string>, vector<string>>> tests = {
        {{"WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"},
         {"", "bad", "dad", "mad", "pad", "bad", ".ad", "b.."}},
        {{"WordDictionary", "addWord", "search", "search", "search"}, {"", "a", ".", "a.", ".."}},
    };
    for (auto& [ops, args] : tests) {
        run<WordDictionaryList>("list", ops, args);
        run<WordDictionary>("trie", ops, args);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Range-for over a C array (for (Node* c : n->next)) works for fixed-size arrays.
 * - `c && dfs(...)` short-circuits on a missing child.
 */
