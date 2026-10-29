/*
 * 0205. Isomorphic Strings  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/isomorphic-strings/
 *
 * Problem: Return true if each char of s can be replaced consistently to
 *          get t, with no two different chars of s mapping to the same
 *          char of t (one-to-one mapping).
 *
 * Examples:
 *   s="egg",   t="add"    -> true
 *   s="foo",   t="bar"    -> false
 *   s="paper", t="title"  -> true
 *   s="badc",  t="baba"   -> false
 *
 * Approaches:
 *   1. First-occurrence signature   O(n) time, O(n) space
 *   2. Two maps  ⭐                  O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: First-Occurrence Signature ----------
vector<int> signature(const string& s) {
    unordered_map<char, int> first;           // char -> index of first appearance
    vector<int> sig;
    for (int i = 0; i < (int)s.size(); i++) {
        auto it = first.find(s[i]);
        if (it == first.end()) it = first.emplace(s[i], i).first;
        sig.push_back(it->second);
    }
    return sig;
}

bool isIsomorphicSignature(const string& s, const string& t) {
    return s.size() == t.size() && signature(s) == signature(t);
}

// ---------- Approach 2: Two Maps ⭐ ----------
bool isIsomorphic(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    array<int, 256> st, ts;                   // -1 = unmapped
    st.fill(-1);
    ts.fill(-1);
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char a = s[i], b = t[i];     // unsigned: chars >= 128 would index negative
        if (st[a] == -1 && ts[b] == -1) {
            st[a] = b;
            ts[b] = a;
        } else if (st[a] != b || ts[b] != a) {
            return false;                     // breaks one direction of the bijection
        }
    }
    return true;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"egg", "add"}, {"foo", "bar"}, {"paper", "title"}, {"badc", "baba"}
    };
    cout << boolalpha;
    for (auto& [s, t] : tests) {
        cout << "signature: " << isIsomorphicSignature(s, t) << "\n";
        cout << "two maps : " << isIsomorphic(s, t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - array::fill sets every element; handy for -1 sentinels.
 * - Cast char to unsigned char before indexing: plain char may be signed.
 * - emplace returns pair<iterator, bool>, like insert.
 * - vector<int> == vector<int> compares element-wise.
 */
