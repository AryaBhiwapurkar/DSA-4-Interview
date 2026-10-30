/*
 * 0022. Generate Parentheses  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/generate-parentheses/
 *
 * Problem: Return every well-formed string of n pairs of parentheses.
 *
 * Examples (printed sorted):
 *   n = 3  -> ["((()))","(()())","(())()","()(())","()()()"]
 *   n = 1  -> ["()"]
 *   n = 2  -> ["(())","()()"]
 *
 * Approaches:
 *   1. Generate all, filter      O(2^(2n) * n) time, O(n) depth
 *   2. Backtracking  ⭐           O(4^n / sqrt(n)) time, O(n) depth   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Generate All, Then Filter ----------
bool balanced(const string& s) {
    int bal = 0;
    for (char c : s) {
        bal += c == '(' ? 1 : -1;
        if (bal < 0) return false;         // a ')' with nothing to close
    }
    return bal == 0;
}

void genAll(int n, string& cur, vector<string>& res) {
    if ((int)cur.size() == 2 * n) {
        if (balanced(cur)) res.push_back(cur);
        return;
    }
    for (char c : {'(', ')'}) {
        cur.push_back(c);
        genAll(n, cur, res);
        cur.pop_back();
    }
}

vector<string> generateParenthesisBrute(int n) {
    vector<string> res;
    string cur;
    genAll(n, cur, res);
    return res;
}

// ---------- Approach 2: Backtracking With Counts ⭐ ----------
void backtrack(int n, int open, int close, string& cur, vector<string>& res) {
    if ((int)cur.size() == 2 * n) {
        res.push_back(cur);                // every leaf is valid by construction
        return;
    }
    if (open < n) {
        cur.push_back('(');
        backtrack(n, open + 1, close, cur, res);
        cur.pop_back();
    }
    if (close < open) {                    // NOT close < n
        cur.push_back(')');
        backtrack(n, open, close + 1, cur, res);
        cur.pop_back();
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    string cur;
    backtrack(n, 0, 0, cur, res);
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
    for (int n : {3, 1, 2}) {
        print("brute    ", generateParenthesisBrute(n));
        print("backtrack", generateParenthesis(n));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Pass the string by reference and undo with pop_back() after each call
 *   (choose / explore / unchoose).
 * - `for (char c : {'(', ')'})` loops over a braced initializer list.
 * - `bal += c == '(' ? 1 : -1;` the ternary binds looser than ==.
 * - Recursive helpers need the result vector by reference (vector<string>&).
 */
