/*
 * 0249. Group Shifted Strings  |  Medium  |  Arrays & Hashing  |  LC Premium
 * Link: https://leetcode.com/problems/group-shifted-strings/
 *
 * Problem: Group strings that can be shifted into each other (each letter +k, z wraps to a).
 *
 * Examples:
 *   ["abc","bcd","acef","xyz","az","ba","a","z"]  -> [["a","z"],["abc","bcd","xyz"],["acef"],["az","ba"]]
 *   ["a"]                                         -> [["a"]]
 *   ["ab","ba","bc"]                              -> [["ab","bc"],["ba"]]
 *
 * Approaches:
 *   1. Pairwise compare + grouping     O(n^2 * L) time
 *   2. Canonical gap key  ⭐           O(N) time, O(N) space   <- go-to (N = total chars)
 *   (Groups are printed sorted so both approaches compare equal.)
 */

#include <bits/stdc++.h>
using namespace std;

bool sameShift(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    int d = (b[0] - a[0] + 26) % 26;
    for (size_t i = 1; i < a.size(); i++)
        if ((b[i] - a[i] + 26) % 26 != d) return false;
    return true;
}

// ---------- Approach 1: Pairwise Compare ----------
vector<vector<string>> groupStringsPairwise(const vector<string>& strs) {
    vector<vector<string>> groups;
    for (auto& s : strs) {
        bool placed = false;
        for (auto& g : groups)
            if (sameShift(g[0], s)) { g.push_back(s); placed = true; break; }   // compare to a representative
        if (!placed) groups.push_back({s});
    }
    return groups;
}

// ---------- Approach 2: Canonical Gap Key ⭐ ----------
vector<vector<string>> groupStrings(const vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (auto& s : strs) {
        string key;
        for (size_t i = 1; i < s.size(); i++)
            key += char('a' + (s[i] - s[i - 1] + 26) % 26);   // one fixed-width char per gap
        groups[key].push_back(s);
    }
    vector<vector<string>> out;
    for (auto& [k, g] : groups) out.push_back(g);
    return out;
}

// ---------- Driver ----------
void print(vector<vector<string>> gs) {
    for (auto& g : gs) sort(g.begin(), g.end());
    sort(gs.begin(), gs.end());
    cout << "[";
    for (size_t i = 0; i < gs.size(); i++) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < gs[i].size(); j++) cout << (j ? "," : "") << "\"" << gs[i][j] << "\"";
        cout << "]";
    }
    cout << "]\n";
}

int main() {
    vector<vector<string>> tests = {{"abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"}, {"a"}, {"ab", "ba", "bc"}};
    for (auto& t : tests) {
        cout << "pairwise: "; print(groupStringsPairwise(t));
        cout << "key     : "; print(groupStrings(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (b - a + 26) % 26 keeps the gap in 0..25 (C++ % can be negative).
 * - Encoding each gap as one char ('a' + gap) gives a fixed-width, collision-free string key.
 * - groups.push_back({s}) builds a one-element vector<string> in place.
 */
