/*
 * 0068. Text Justification  |  Hard  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/text-justification/
 *
 * Problem: Greedily pack words into lines of exactly maxWidth chars and
 *          fully justify them (extra spaces go to the left gaps). The last
 *          line and single-word lines are left-justified, padded right.
 *
 * Examples:
 *   ["This","is","an","example","of","text","justification."], 16
 *     -> ["This    is    an","example  of text","justification.  "]
 *   ["What","must","be","acknowledgment","shall","be"], 16
 *     -> ["What   must   be","acknowledgment  ","shall be        "]
 *   ["Science","is","what",...,"we","do"], 20
 *     -> ["Science  is  what we","understand      well","enough to explain to",
 *         "a  computer.  Art is","everything  else  we","do                  "]
 *
 * Approaches:
 *   1. Greedy packing + space distribution  ⭐  O(N) time   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Greedy Packing + Space Distribution ⭐ ----------
vector<string> fullJustify(const vector<string>& words, int maxWidth) {
    vector<string> res;
    int n = words.size(), i = 0;
    while (i < n) {
        int j = i, letters = 0;
        while (j < n && letters + (j - i) + (int)words[j].size() <= maxWidth)   // (j - i) separating spaces
            letters += words[j++].size();
        int gaps = j - i - 1;
        string line = words[i];
        if (j == n || gaps == 0) {                                     // last line or single word: left-justify
            for (int k = i + 1; k < j; k++) line += " " + words[k];
            line += string(maxWidth - line.size(), ' ');
        } else {
            int spaces = maxWidth - letters;
            for (int k = i + 1; k < j; k++) {
                int g = k - i - 1;                                     // gap index 0..gaps-1
                line += string(spaces / gaps + (g < spaces % gaps ? 1 : 0), ' ');   // extras go left
                line += words[k];
            }
        }
        res.push_back(line);
        i = j;
    }
    return res;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<string>, int>> tests = {
        {{"This", "is", "an", "example", "of", "text", "justification."}, 16},
        {{"What", "must", "be", "acknowledgment", "shall", "be"}, 16},
        {{"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain",
          "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"}, 20},
    };
    for (auto& [words, w] : tests) {
        for (auto& line : fullJustify(words, w)) cout << "\"" << line << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - string(k, ' ') builds k spaces.
 * - words[j++].size() reads words[j], then advances j.
 * - Mixing int and size_t in comparisons: cast size() to int first.
 */
