/*
 * 0433. Minimum Genetic Mutation  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/minimum-genetic-mutation/
 *
 * Problem: 8-letter genes over ACGT. A mutation changes one letter; every
 *          intermediate must be in the bank. Fewest mutations start -> end, or -1.
 *
 * Examples:
 *   AACCGGTT -> AACCGGTA, [AACCGGTA]                      -> 1
 *   AACCGGTT -> AAACGGTA, [AACCGGTA,AACCGCTA,AAACGGTA]    -> 2
 *   AAAAACCC -> AACCCCCC, [AAAACCCC,AAACCCCC,AACCCCCC]    -> 3
 *   AACCGGTT -> AACCGGTA, []                              -> -1
 *   AACCGGTT -> AACCGGTT, []                              -> 0
 *
 * Approaches:
 *   1. BFS scanning the bank             O(B^2 * 8) time, O(B) space
 *   2. BFS with letter substitution  ⭐   O(B * 8 * 4) time, O(B) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: BFS Scanning the Bank ----------
int minMutationScan(const string& start, const string& end, const vector<string>& bank) {
    if (start == end) return 0;
    vector<bool> used(bank.size(), false);
    queue<pair<string, int>> q;
    q.push({start, 0});
    while (!q.empty()) {
        auto [g, d] = q.front(); q.pop();
        for (size_t i = 0; i < bank.size(); i++) {
            if (used[i]) continue;
            int diff = 0;
            for (int k = 0; k < 8; k++) diff += g[k] != bank[i][k];
            if (diff != 1) continue;
            if (bank[i] == end) return d + 1;
            used[i] = true;
            q.push({bank[i], d + 1});
        }
    }
    return -1;
}

// ---------- Approach 2: BFS with Letter Substitution ⭐ ----------
int minMutation(const string& start, const string& end, const vector<string>& bank) {
    if (start == end) return 0;
    unordered_set<string> valid(bank.begin(), bank.end());
    if (!valid.count(end)) return -1;
    unordered_set<string> seen{start};
    queue<pair<string, int>> q;
    q.push({start, 0});
    while (!q.empty()) {
        auto [g, d] = q.front(); q.pop();
        for (int i = 0; i < 8; i++) {
            char orig = g[i];
            for (char ch : string("ACGT")) {
                if (ch == orig) continue;
                g[i] = ch;
                if (valid.count(g) && seen.insert(g).second) {   // mark on push
                    if (g == end) return d + 1;
                    q.push({g, d + 1});
                }
            }
            g[i] = orig;                   // restore before the next position
        }
    }
    return -1;
}

// ---------- Driver ----------
int main() {
    struct T { string s, e; vector<string> bank; };
    vector<T> tests = {
        {"AACCGGTT", "AACCGGTA", {"AACCGGTA"}},
        {"AACCGGTT", "AAACGGTA", {"AACCGGTA", "AACCGCTA", "AAACGGTA"}},
        {"AAAAACCC", "AACCCCCC", {"AAAACCCC", "AAACCCCC", "AACCCCCC"}},
        {"AACCGGTT", "AACCGGTA", {}},
        {"AACCGGTT", "AACCGGTT", {}},
    };
    for (auto& t : tests) {
        cout << "scan : " << minMutationScan(t.s, t.e, t.bank) << "\n";
        cout << "subst: " << minMutation(t.s, t.e, t.bank) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `diff += a != b` adds 1 for each mismatch (bool converts to int).
 * - `auto [g, d] = q.front();` copies, so g can be mutated freely.
 * - unordered_set<string> valid(bank.begin(), bank.end()) builds the lookup set.
 */
