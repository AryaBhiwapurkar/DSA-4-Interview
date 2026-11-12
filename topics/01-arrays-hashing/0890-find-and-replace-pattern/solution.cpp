/*
 * 0890. Find and Replace Pattern  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/find-and-replace-pattern/
 *
 * Problem: Return the words that match the pattern under a one-to-one letter mapping.
 *
 * Examples:
 *   ["abc","deq","mee","aqq","dkd","ccc"], "abb"  -> ["mee","aqq"]
 *   ["a","b","c"], "a"                            -> ["a","b","c"]
 *   ["xyz","xxy","yyx"], "abc"                    -> ["xyz"]
 *
 * Approaches:
 *   1. Two-map bijection check  ⭐       O(N) time, O(1) space per word   <- go-to
 *   2. First-occurrence signature        O(N) time, O(L) space
 */

#include <bits/stdc++.h>
using namespace std;

bool matches(const string& w, const string& p) {
    array<char, 26> p2w{}, w2p{};                  // 0 = unmapped
    for (size_t i = 0; i < p.size(); i++) {
        char a = p[i], b = w[i];
        if (p2w[a - 'a'] && p2w[a - 'a'] != b) return false;   // one pattern letter -> two letters
        if (w2p[b - 'a'] && w2p[b - 'a'] != a) return false;   // two pattern letters -> one letter
        p2w[a - 'a'] = b;
        w2p[b - 'a'] = a;
    }
    return true;
}

// ---------- Approach 1: Two-map Bijection ⭐ ----------
vector<string> findAndReplacePattern(const vector<string>& words, const string& pattern) {
    vector<string> out;
    for (auto& w : words)
        if (matches(w, pattern)) out.push_back(w);
    return out;
}

// ---------- Approach 2: First-occurrence Signature ----------
vector<int> signature(const string& s) {
    array<int, 26> first;
    first.fill(-1);
    vector<int> sig;
    for (int i = 0; i < (int)s.size(); i++) {
        int& f = first[s[i] - 'a'];
        if (f == -1) f = i;
        sig.push_back(f);                          // "abb" -> [0,1,1]
    }
    return sig;
}

vector<string> findAndReplacePatternSig(const vector<string>& words, const string& pattern) {
    auto target = signature(pattern);
    vector<string> out;
    for (auto& w : words)
        if (signature(w) == target) out.push_back(w);
    return out;
}

// ---------- Driver ----------
void print(const vector<string>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << "\"" << v[i] << "\"";
    cout << "]\n";
}

int main() {
    vector<pair<vector<string>, string>> tests = {
        {{"abc", "deq", "mee", "aqq", "dkd", "ccc"}, "abb"}, {{"a", "b", "c"}, "a"}, {{"xyz", "xxy", "yyx"}, "abc"}};
    for (auto& [words, p] : tests) {
        cout << "two maps : "; print(findAndReplacePattern(words, p));
        cout << "signature: "; print(findAndReplacePatternSig(words, p));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - array<char, 26> m{} value-initialises every slot to 0 (usable as "unmapped").
 * - arr.fill(-1) sets every element of a std::array.
 * - int& f = first[...] binds a reference so the slot can be updated through f.
 */
