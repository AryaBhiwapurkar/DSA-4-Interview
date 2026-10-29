/*
 * 0030. Substring with Concatenation of All Words  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 *
 * Problem: Words all have length w. Return every start index in s where
 *          the next m*w chars are a concatenation of all words, each once.
 *
 * Examples (printed sorted):
 *   "barfoothefoobarman", ["foo","bar"]                         -> [0,9]
 *   "wordgoodgoodgoodbestword", ["word","good","best","word"]   -> []
 *   "barfoofoobarthefoobarman", ["bar","foo","the"]             -> [6,9,12]
 *   "aaaa", ["aa","aa"]                                         -> [0]
 *
 * Approaches:
 *   1. Check every start             O(n * m * w) time, O(m * w) space
 *   2. Per-offset token window  ⭐    O(n * w) time, O(m * w) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Check Every Start ----------
vector<int> findSubstringBrute(const string& s, const vector<string>& words) {
    int n = s.size(), m = words.size(), w = words[0].size();
    unordered_map<string, int> need;
    for (auto& word : words) need[word]++;
    vector<int> res;
    for (int i = 0; i + m * w <= n; i++) {
        unordered_map<string, int> seen;
        int j = 0;
        for (; j < m; j++) {
            string tok = s.substr(i + j * w, w);
            auto it = need.find(tok);
            if (it == need.end() || ++seen[tok] > it->second) break;   // unknown or too many
        }
        if (j == m) res.push_back(i);
    }
    return res;
}

// ---------- Approach 2: Per-Offset Token Window ⭐ ----------
vector<int> findSubstring(const string& s, const vector<string>& words) {
    int n = s.size(), m = words.size(), w = words[0].size();
    unordered_map<string, int> need;
    for (auto& word : words) need[word]++;
    vector<int> res;
    for (int off = 0; off < w; off++) {                    // valid starts live on one of w tracks
        unordered_map<string, int> win;
        int left = off, count = 0;                         // count = tokens in window
        for (int r = off; r + w <= n; r += w) {
            string tok = s.substr(r, w);
            auto it = need.find(tok);
            if (it == need.end()) {                        // non-word breaks every window: reset
                win.clear();
                count = 0;
                left = r + w;
                continue;
            }
            win[tok]++, count++;
            while (win[tok] > it->second) {                // too many copies: drop from the left
                win[s.substr(left, w)]--;
                left += w, count--;
            }
            if (count == m) res.push_back(left);
        }
    }
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<int> v) {
    sort(v.begin(), v.end());                              // normalize: order is unspecified
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<pair<string, vector<string>>> tests = {
        {"barfoothefoobarman", {"foo", "bar"}},
        {"wordgoodgoodgoodbestword", {"word", "good", "best", "word"}},
        {"barfoofoobarthefoobarman", {"bar", "foo", "the"}},
        {"aaaa", {"aa", "aa"}},
    };
    for (auto& [s, words] : tests) {
        print("brute ", findSubstringBrute(s, words));
        print("window", findSubstring(s, words));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (; j < m; j++)` keeps j alive after the loop to check how far it got.
 * - ++seen[tok] > limit: increment (inserting 0 first if new), then compare.
 * - unordered_map<string,int>::clear() empties the window counts.
 */
