/*
 * 0271. Encode and Decode Strings  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/encode-and-decode-strings/
 *
 * Problem: Design encode(list<string>) -> string and decode(string) ->
 *          list<string> with decode(encode(x)) == x. Strings can hold
 *          any ASCII character.
 *
 * Examples:
 *   ["Hello","World"]  -> encoded "5#Hello5#World"  -> ["Hello","World"]
 *   [""]               -> encoded "0#"              -> [""]
 *   ["1#2","#","//;"]  -> round-trips unchanged
 *   []                 -> encoded ""                -> []
 *
 * Approaches:
 *   1. Escaped delimiter     O(N) time, O(N) space
 *   2. Length prefix  ⭐      O(N) time, O(N) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Escaped Delimiter ----------
// '/' is written as "//", and every string ends with "/;".
string encodeEscaped(const vector<string>& strs) {
    string out;
    for (const string& s : strs) {
        for (char c : s) {
            if (c == '/') out += '/';           // double the escape char
            out += c;
        }
        out += "/;";
    }
    return out;
}

vector<string> decodeEscaped(const string& s) {
    vector<string> res;
    string cur;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '/') {
            if (s[i + 1] == ';') {               // terminator
                res.push_back(cur);
                cur.clear();
            } else {
                cur += '/';                      // "//" -> literal '/'
            }
            i++;
        } else {
            cur += s[i];
        }
    }
    return res;
}

// ---------- Approach 2: Length Prefix ⭐ ----------
string encode(const vector<string>& strs) {
    string out;
    for (const string& s : strs) out += to_string(s.size()) + "#" + s;
    return out;
}

vector<string> decode(const string& s) {
    vector<string> res;
    size_t i = 0;
    while (i < s.size()) {
        size_t j = s.find('#', i);               // search from i: earlier content may contain '#'
        int len = stoi(s.substr(i, j - i));
        res.push_back(s.substr(j + 1, len));
        i = j + 1 + len;
    }
    return res;
}

// ---------- Driver ----------
void print(const string& label, const vector<string>& v) {
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << "\"" << v[i] << "\"";
    cout << "]\n";
}

int main() {
    vector<vector<string>> tests = {{"Hello", "World"}, {""}, {"1#2", "#", "//;"}, {}};
    for (auto& strs : tests) {
        cout << "encoded: \"" << encode(strs) << "\"\n";
        print("escaped", decodeEscaped(encodeEscaped(strs)));
        print("length ", decode(encode(strs)));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - s.find(ch, pos) searches starting at pos; returns string::npos if absent.
 * - stoi parses a decimal int; to_string formats one.
 * - s.substr(pos, len) clamps len at the end of the string.
 */
