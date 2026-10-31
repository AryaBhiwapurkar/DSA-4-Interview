/*
 * 0127. Word Ladder  |  Hard  |  Graphs
 * Link: https://leetcode.com/problems/word-ladder/
 *
 * Problem: Number of words in the shortest begin -> end chain where each step
 *          changes one letter and every later word is in the list; 0 if none.
 *
 * Examples:
 *   hit -> cog, [hot,dot,dog,lot,log,cog]  -> 5
 *   hit -> cog, [hot,dot,dog,lot,log]      -> 0
 *   a -> c, [a,b,c]                        -> 2
 *   hot -> dog, [hot,dog]                  -> 0 (two letters differ)
 *
 * Approaches:
 *   1. BFS with letter substitution    O(N * 26 * L^2) time, O(N * L) space
 *   2. BFS with wildcard buckets  ⭐    O(N * L^2) time, O(N * L^2) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: BFS with Letter Substitution ----------
int ladderLengthSubst(const string& begin, const string& end, const vector<string>& words) {
    unordered_set<string> left(words.begin(), words.end());   // unvisited dictionary words
    if (!left.count(end)) return 0;
    left.erase(begin);
    queue<pair<string, int>> q;
    q.push({begin, 1});
    while (!q.empty()) {
        auto [w, d] = q.front(); q.pop();
        for (size_t i = 0; i < w.size(); i++) {
            char orig = w[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                w[i] = ch;
                if (!left.count(w)) continue;
                if (w == end) return d + 1;
                left.erase(w);             // erase = mark visited
                q.push({w, d + 1});
            }
            w[i] = orig;
        }
    }
    return 0;
}

// ---------- Approach 2: BFS with Wildcard Buckets ⭐ ----------
int ladderLength(const string& begin, const string& end, const vector<string>& words) {
    if (find(words.begin(), words.end(), end) == words.end()) return 0;
    unordered_map<string, vector<string>> buckets;   // "h*t" -> words matching it
    for (auto& w : words)
        for (size_t i = 0; i < w.size(); i++) {
            string p = w;
            p[i] = '*';
            buckets[p].push_back(w);
        }
    unordered_set<string> seen{begin};
    queue<pair<string, int>> q;
    q.push({begin, 1});
    while (!q.empty()) {
        auto [w, d] = q.front(); q.pop();
        for (size_t i = 0; i < w.size(); i++) {
            string p = w;
            p[i] = '*';
            auto it = buckets.find(p);
            if (it == buckets.end()) continue;
            for (auto& nb : it->second) {
                if (!seen.insert(nb).second) continue;
                if (nb == end) return d + 1;
                q.push({nb, d + 1});
            }
            it->second.clear();            // never scan this pattern again
        }
    }
    return 0;
}

// ---------- Driver ----------
int main() {
    struct T { string b, e; vector<string> words; };
    vector<T> tests = {
        {"hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}},
        {"hit", "cog", {"hot", "dot", "dog", "lot", "log"}},
        {"a", "c", {"a", "b", "c"}},
        {"hot", "dog", {"hot", "dog"}},
    };
    for (auto& t : tests) {
        cout << "subst  : " << ladderLengthSubst(t.b, t.e, t.words) << "\n";
        cout << "buckets: " << ladderLength(t.b, t.e, t.words) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::string is mutable: change w[i], test, restore.
 * - Keeping the iterator from find() lets you clear the bucket without a second lookup.
 * - unordered_set::erase doubles as "visited" in approach 1.
 */
