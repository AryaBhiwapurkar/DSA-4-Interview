/*
 * 0208. Implement Trie (Prefix Tree)  |  Medium  |  Tries
 * Link: https://leetcode.com/problems/implement-trie-prefix-tree/
 *
 * Problem: insert(word), search(word) for an exact word, startsWith(prefix).
 *
 * Examples:
 *   insert apple, search apple, search app, startsWith app, insert app, search app
 *     -> [null,null,true,false,true,null,true]
 *   insert a, search a, startsWith b, search ab
 *     -> [null,null,true,false,false]
 *
 * Approaches:
 *   1. Hash set of words           O(L) insert/search, O(N*L) startsWith
 *   2. Trie with 26 children  ⭐    O(L) per operation   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Hash Set of Words ----------
class TrieSet {
    unordered_set<string> words;
public:
    void insert(const string& w) { words.insert(w); }
    bool search(const string& w) { return words.count(w); }
    bool startsWith(const string& p) {
        for (auto& w : words)              // scans every word: O(N * L)
            if (w.compare(0, p.size(), p) == 0) return true;
        return false;
    }
};

// ---------- Approach 2: Trie With 26 Children ⭐ ----------
class Trie {
    struct Node {
        Node* next[26] = {};               // all null
        bool isEnd = false;
    };
    Node* root = new Node();

    Node* walk(const string& s) {          // node at the end of s, or null
        Node* n = root;
        for (char c : s) {
            n = n->next[c - 'a'];
            if (!n) return nullptr;
        }
        return n;
    }

public:
    void insert(const string& w) {
        Node* n = root;
        for (char c : w) {
            if (!n->next[c - 'a']) n->next[c - 'a'] = new Node();
            n = n->next[c - 'a'];
        }
        n->isEnd = true;
    }
    bool search(const string& w) {
        Node* n = walk(w);
        return n && n->isEnd;              // path existing isn't enough
    }
    bool startsWith(const string& p) { return walk(p) != nullptr; }
};

// ---------- Driver ----------
template <class T>
void run(const string& label, const vector<string>& ops, const vector<string>& args) {
    T t;
    cout << label << ": [null" << boolalpha;
    for (size_t i = 1; i < ops.size(); i++) {
        if (ops[i] == "insert") { t.insert(args[i]); cout << ",null"; }
        else if (ops[i] == "search") cout << "," << t.search(args[i]);
        else cout << "," << t.startsWith(args[i]);
    }
    cout << "]\n";
}

int main() {
    vector<pair<vector<string>, vector<string>>> tests = {
        {{"Trie", "insert", "search", "search", "startsWith", "insert", "search"},
         {"", "apple", "apple", "app", "app", "app", "app"}},
        {{"Trie", "insert", "search", "startsWith", "search"}, {"", "a", "a", "b", "ab"}},
    };
    for (auto& [ops, args] : tests) {
        run<TrieSet>("set ", ops, args);
        run<Trie>("trie", ops, args);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `Node* next[26] = {};` zero-initialises the array (all nullptr).
 * - c - 'a' maps 'a'..'z' to 0..25.
 * - s.compare(0, p.size(), p) == 0 is "s starts with p".
 */
