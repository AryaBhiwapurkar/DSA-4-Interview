/*
 * 0290. Word Pattern  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/word-pattern/
 *
 * Problem: Return true if the words in s follow the letter pattern with
 *          a one-to-one mapping between letters and words.
 *
 * Examples:
 *   "abba", "dog cat cat dog"   -> true
 *   "abba", "dog cat cat fish"  -> false
 *   "aaaa", "dog cat cat dog"   -> false
 *   "abba", "dog dog dog dog"   -> false
 *
 * Approaches:
 *   1. First-occurrence signature   O(n+m) time, O(n+m) space
 *   2. Two hashmaps  ⭐              O(n+m) time, O(k) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string& s) {
    vector<string> words;
    stringstream ss(s);
    string w;
    while (ss >> w) words.push_back(w);     // >> skips any whitespace
    return words;
}

// ---------- Approach 1: First-Occurrence Signature ----------
bool wordPatternSignature(const string& pattern, const string& s) {
    vector<string> words = split(s);
    if (words.size() != pattern.size()) return false;
    unordered_map<char, int> pFirst;
    unordered_map<string, int> wFirst;
    for (int i = 0; i < (int)words.size(); i++) {
        int a = pFirst.emplace(pattern[i], i).first->second;   // emplace keeps existing value
        int b = wFirst.emplace(words[i], i).first->second;
        if (a != b) return false;
    }
    return true;
}

// ---------- Approach 2: Two Hashmaps ⭐ ----------
bool wordPattern(const string& pattern, const string& s) {
    vector<string> words = split(s);
    if (words.size() != pattern.size()) return false;
    unordered_map<char, string> pw;
    unordered_map<string, char> wp;
    for (size_t i = 0; i < words.size(); i++) {
        char c = pattern[i];
        const string& w = words[i];
        auto a = pw.find(c);
        auto b = wp.find(w);
        if (a == pw.end() && b == wp.end()) {
            pw[c] = w;
            wp[w] = c;
        } else if (a == pw.end() || b == wp.end() || a->second != w || b->second != c) {
            return false;
        }
    }
    return true;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"abba", "dog cat cat dog"}, {"abba", "dog cat cat fish"},
        {"aaaa", "dog cat cat dog"}, {"abba", "dog dog dog dog"}
    };
    cout << boolalpha;
    for (auto& [p, s] : tests) {
        cout << "signature: " << wordPatternSignature(p, s) << "\n";
        cout << "two maps : " << wordPattern(p, s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Split on whitespace: stringstream ss(s); while (ss >> w).
 * - emplace(k, v) doesn't overwrite; .first->second is the stored value.
 * - Bind to const string& to avoid copying words.
 */
