/*
 * 0151. Reverse Words in a String  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/reverse-words-in-a-string/
 *
 * Problem: Return the words of s in reverse order, joined by single
 *          spaces, with no leading/trailing/repeated spaces.
 *
 * Examples:
 *   "the sky is blue"    -> "blue is sky the"
 *   "  hello world  "    -> "world hello"
 *   "a good   example"   -> "example good a"
 *   "single"             -> "single"
 *
 * Approaches:
 *   1. Split + reverse + join  ⭐   O(n) time, O(n) space   <- go-to
 *   2. In-place reversal           O(n) time, O(1) extra space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Split + Reverse + Join ⭐ ----------
string reverseWords(const string& s) {
    stringstream ss(s);
    vector<string> words;
    string w;
    while (ss >> w) words.push_back(w);           // >> skips any amount of whitespace
    reverse(words.begin(), words.end());
    string out;
    for (size_t i = 0; i < words.size(); i++) out += (i ? " " : "") + words[i];
    return out;
}

// ---------- Approach 2: In-Place Reversal + Compaction ----------
string reverseWordsInPlace(string s) {            // by value: we mutate our copy
    reverse(s.begin(), s.end());                  // words in final order, each backwards
    int n = s.size(), write = 0;
    for (int read = 0; read < n; read++) {
        if (s[read] == ' ') continue;
        if (write > 0) s[write++] = ' ';          // one space before every word but the first
        int start = write;
        while (read < n && s[read] != ' ') s[write++] = s[read++];
        reverse(s.begin() + start, s.begin() + write);   // fix this word
    }
    s.resize(write);                              // drop leftover tail
    return s;
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"the sky is blue", "  hello world  ", "a good   example", "single"};
    for (auto& s : tests) {
        cout << "split   : \"" << reverseWords(s) << "\"\n";
        cout << "in-place: \"" << reverseWordsInPlace(s) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::string is mutable: reverse() and indexed writes work in place.
 * - s.resize(k) truncates (or pads) the string to length k.
 * - (i ? " " : "") + words[i]: const char* + std::string yields std::string.
 */
