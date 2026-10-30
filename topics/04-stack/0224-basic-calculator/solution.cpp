/*
 * 0224. Basic Calculator  |  Hard  |  Stack
 * Link: https://leetcode.com/problems/basic-calculator/
 *
 * Problem: Evaluate a valid expression with non-negative integers, + - ( )
 *          and spaces. '-' may be unary. No eval.
 *
 * Examples:
 *   "1 + 1"                -> 2
 *   " 2-1 + 2 "            -> 3
 *   "(1+(4+5+2)-3)+(6+8)"  -> 23
 *   "-(2+3)"               -> -5
 *   "1-(     -2)"          -> 3
 *   "2147483647"           -> 2147483647
 *
 * Approaches:
 *   1. Recursive descent       O(n) time, O(depth) space
 *   2. Stack of (result, sign) ⭐ O(n) time, O(depth) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Recursive Descent ----------
int parse(const string& s, size_t& i) {
    int res = 0, sign = 1;
    while (i < s.size()) {
        char c = s[i++];
        if (isdigit(c)) {
            int num = c - '0';
            while (i < s.size() && isdigit(s[i])) num = num * 10 + (s[i++] - '0');
            res += sign * num;
        } else if (c == '+') sign = 1;
        else if (c == '-') sign = -1;
        else if (c == '(') res += sign * parse(s, i);   // a group is just a number
        else if (c == ')') return res;
    }
    return res;
}

int calculateRecursive(const string& s) {
    size_t i = 0;
    return parse(s, i);
}

// ---------- Approach 2: Stack of (result, sign) ⭐ ----------
int calculate(const string& s) {
    int res = 0, num = 0, sign = 1;
    vector<int> st;                        // pairs pushed as result, then sign
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '+' || c == '-') {
            res += sign * num;             // flush the pending number
            num = 0;
            sign = c == '+' ? 1 : -1;
        } else if (c == '(') {
            st.push_back(res);
            st.push_back(sign);
            res = 0, sign = 1;
        } else if (c == ')') {
            res += sign * num;
            num = 0;
            int outerSign = st.back(); st.pop_back();   // sign was pushed last
            int outerRes = st.back(); st.pop_back();
            res = outerRes + outerSign * res;
        }                                  // spaces fall through
    }
    return res + sign * num;               // flush the final number
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"1 + 1", " 2-1 + 2 ", "(1+(4+5+2)-3)+(6+8)", "-(2+3)", "1-(     -2)", "2147483647"};
    for (auto& s : tests) {
        cout << "recursive: " << calculateRecursive(s) << "\n";
        cout << "stack    : " << calculate(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Pass an index by reference (size_t& i) so recursive calls advance it.
 * - s[i++] reads then advances in one expression.
 * - `res = 0, sign = 1;` uses the comma operator for two assignments.
 * - isdigit(c) is safe here because the input is plain ASCII.
 */
