/*
 * 0187. Repeated DNA Sequences  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/repeated-dna-sequences/
 *
 * Problem: Return every 10-letter substring of a DNA string (ACGT) that occurs more than once.
 *
 * Examples:
 *   "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"  -> ["AAAAACCCCC","CCCCCAAAAA"]
 *   "AAAAAAAAAAAAA"                     -> ["AAAAAAAAAA"]
 *   "ACGT"                              -> []    (shorter than 10)
 *   "ACGTACGTACGTACGT"                  -> ["ACGTACGTAC","CGTACGTACG","GTACGTACGT"]
 *
 * Approaches:
 *   1. Substring hash set  ⭐     O(n*L) time, O(n*L) space   <- go-to (L = 10)
 *   2. 2-bit rolling encoding     O(n) time, O(n) space
 *   (Output is printed sorted so both approaches compare equal.)
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Substring Set ⭐ ----------
vector<string> findRepeatedDnaSequences(const string& s) {
    unordered_set<string> seen, repeated;
    for (int i = 0; i + 10 <= (int)s.size(); i++) {      // int: no size_t underflow
        string w = s.substr(i, 10);
        if (!seen.insert(w).second) repeated.insert(w);  // insert fails -> seen before
    }
    return vector<string>(repeated.begin(), repeated.end());
}

// ---------- Approach 2: 2-bit Rolling Encoding ----------
vector<string> findRepeatedDnaSequencesBits(const string& s) {
    auto val = [](char c) { return c == 'A' ? 0 : c == 'C' ? 1 : c == 'G' ? 2 : 3; };
    const int MASK = (1 << 20) - 1;                // 10 letters x 2 bits
    unordered_set<int> seen, added;
    vector<string> out;
    int code = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        code = ((code << 2) | val(s[i])) & MASK;   // shift in the new letter, drop the oldest
        if (i < 9) continue;                       // window not full yet
        if (!seen.insert(code).second && added.insert(code).second)
            out.push_back(s.substr(i - 9, 10));
    }
    return out;
}

// ---------- Driver ----------
void print(vector<string> v) {
    sort(v.begin(), v.end());
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << "\"" << v[i] << "\"";
    cout << "]\n";
}

int main() {
    for (string s : {"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", "AAAAAAAAAAAAA", "ACGT", "ACGTACGTACGTACGT"}) {
        cout << "set : "; print(findRepeatedDnaSequences(s));
        cout << "bits: "; print(findRepeatedDnaSequencesBits(s));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - set.insert(x).second is false when x was already present: a check-and-insert in one call.
 * - Write loop bounds as i + 10 <= (int)s.size(); s.size() - 10 underflows when size < 10.
 * - A nested ternary in a lambda maps a few characters to codes.
 */
