/*
 * 0017. Letter Combinations of a Phone Number  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 *
 * Problem: Return every letter string that a string of digits 2-9 could
 *          spell on a phone keypad. Any order.
 *
 * Examples:
 *   "23"  -> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *   ""    -> []
 *   "2"   -> ["a","b","c"]
 *   "79"  -> 16 strings, "pw" .. "sz"
 *
 * Approaches:
 *   1. Iterative expansion       O(4^n * n) time, O(4^n * n) space
 *   2. Backtracking  ⭐           O(4^n * n) time, O(n) extra space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

const vector<string> KEYS = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// ---------- Approach 1: Iterative Expansion ----------
vector<string> letterCombinationsIter(const string& digits) {
    if (digits.empty()) return {};
    vector<string> res = {""};
    for (char d : digits) {
        vector<string> next;
        for (auto& s : res)
            for (char c : KEYS[d - '0']) next.push_back(s + c);
        res = move(next);
    }
    return res;
}

// ---------- Approach 2: Backtracking ⭐ ----------
void dfs(const string& digits, int i, string& path, vector<string>& res) {
    if (i == (int)digits.size()) { res.push_back(path); return; }
    for (char c : KEYS[digits[i] - '0']) {
        path.push_back(c);
        dfs(digits, i + 1, path, res);
        path.pop_back();                   // unchoose
    }
}

vector<string> letterCombinations(const string& digits) {
    if (digits.empty()) return {};         // otherwise dfs would save ""
    vector<string> res;
    string path;
    dfs(digits, 0, path, res);
    return res;
}

// ---------- Driver ----------
void print(const string& label, vector<string> v) {
    sort(v.begin(), v.end());              // normalize: any order is accepted
    cout << label << ": [";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << '"' << v[i] << '"';
    cout << "]\n";
}

int main() {
    for (string d : {"23", "", "2", "79"}) {
        print("iter     ", letterCombinationsIter(d));
        print("backtrack", letterCombinations(d));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - digits[i] - '0' turns a digit char into an index.
 * - res = move(next) swaps buffers without copying every string.
 * - path.push_back / pop_back on a std::string makes it a cheap stack.
 * - for (string d : {"23", ...}) iterates an initializer_list.
 */
