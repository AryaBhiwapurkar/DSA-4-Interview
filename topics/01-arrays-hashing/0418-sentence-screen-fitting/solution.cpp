/*
 * 0418. Sentence Screen Fitting  |  Medium  |  Arrays & Hashing  |  LC Premium
 * Link: https://leetcode.com/problems/sentence-screen-fitting/
 *
 * Problem: rows x cols screen; write the sentence repeatedly, words never split,
 *          one space between words on a line. How many full sentences fit?
 *
 * Examples:
 *   rows=2, cols=8, ["hello","world"]          -> 1
 *   rows=3, cols=6, ["a","bcd","e"]            -> 2
 *   rows=4, cols=5, ["i","had","apple","pie"]  -> 1
 *   rows=3, cols=2, ["abc"]                    -> 0   (word longer than a row)
 *   rows=5, cols=3, ["a","b"]                  -> 5   (sentence fits exactly per row)
 *
 * Approaches:
 *   1. Word-by-word simulation          O(rows * cols) worst time, O(1) space
 *   2. Joined-string pointer  ⭐        O(rows * maxWordLen) time, O(L) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Word-by-word ----------
int wordsTypingSim(const vector<string>& sentence, int rows, int cols) {
    int n = sentence.size(), idx = 0, count = 0;
    for (auto& w : sentence)
        if ((int)w.size() > cols) return 0;        // can never be placed
    for (int r = 0; r < rows; r++) {
        int used = 0;                              // characters used on this row
        while (used + (int)sentence[idx].size() <= cols) {
            used += sentence[idx].size() + 1;      // word plus a separating space
            if (++idx == n) idx = 0, count++;
        }
    }
    return count;
}

// ---------- Approach 2: Joined-string Pointer ⭐ ----------
int wordsTyping(const vector<string>& sentence, int rows, int cols) {
    string s;
    for (auto& w : sentence) s += w + " ";         // trailing space marks the wrap boundary
    long long L = s.size(), pos = 0;
    for (int r = 0; r < rows; r++) {
        pos += cols;
        if (s[pos % L] == ' ') pos++;              // row ended on a boundary: skip the space
        else
            while (pos > 0 && s[(pos - 1) % L] != ' ') pos--;   // cut mid-word: move that word down
    }
    return pos / L;
}

// ---------- Driver ----------
int main() {
    struct T { int rows, cols; vector<string> words; };
    vector<T> tests = {{2, 8, {"hello", "world"}}, {3, 6, {"a", "bcd", "e"}},
                       {4, 5, {"i", "had", "apple", "pie"}}, {3, 2, {"abc"}}, {5, 3, {"a", "b"}}};
    for (auto& t : tests) {
        cout << "simulate: " << wordsTypingSim(t.words, t.rows, t.cols) << "\n";
        cout << "pointer : " << wordsTyping(t.words, t.rows, t.cols) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - if (++idx == n) idx = 0, count++; wraps an index and counts the wrap in one line.
 * - A local struct T groups test inputs; aggregate init {2, 8, {...}} fills it.
 * - pos grows to about rows * (cols + 1) <= 4e8: fits in int, long long just leaves headroom.
 */
