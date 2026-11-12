/*
 * 0772. Basic Calculator III  |  Hard  |  Stack  |  LC Premium
 * Link: https://leetcode.com/problems/basic-calculator-iii/
 *
 * Problem: Evaluate non-negative ints with + - * /, parentheses and spaces;
 *          division truncates toward zero.
 *
 * Examples:
 *   "1+1"                    -> 2
 *   "6-4/2"                  -> 4
 *   "2*(5+5*2)/3+(6/2+8)"    -> 21
 *   "((2))"                  -> 2
 *   "(0-3)/2"                -> -1
 *
 * Approaches:
 *   1. Two stacks (shunting-yard)               O(n) time, O(n) space
 *   2. Recursive previous-operator stack  ⭐    O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Two Stacks ----------
int prec(char op) { return op == '+' || op == '-' ? 1 : op == '*' || op == '/' ? 2 : 0; }

void applyTop(vector<long long>& vals, vector<char>& ops) {
    long long b = vals.back(); vals.pop_back();
    long long a = vals.back(); vals.pop_back();
    char op = ops.back(); ops.pop_back();
    vals.push_back(op == '+' ? a + b : op == '-' ? a - b : op == '*' ? a * b : a / b);
}

int calculateTwoStacks(const string& s) {
    vector<long long> vals;
    vector<char> ops;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == ' ') continue;
        if (isdigit(c)) {
            long long num = 0;
            while (i < s.size() && isdigit(s[i])) num = num * 10 + (s[i++] - '0');
            i--;
            vals.push_back(num);
        } else if (c == '(') ops.push_back(c);
        else if (c == ')') {
            while (ops.back() != '(') applyTop(vals, ops);
            ops.pop_back();                        // drop '('
        } else {
            while (!ops.empty() && prec(ops.back()) >= prec(c)) applyTop(vals, ops);   // left-assoc
            ops.push_back(c);
        }
    }
    while (!ops.empty()) applyTop(vals, ops);
    return vals.back();
}

// ---------- Approach 2: Recursive Stack ⭐ ----------
long long evalFrom(const string& s, size_t& i) {
    vector<long long> st;
    long long num = 0;
    char op = '+';
    for (; i <= s.size(); i++) {
        char c = i < s.size() ? s[i] : '\0';
        if (isdigit(c)) { num = num * 10 + (c - '0'); continue; }
        if (c == ' ') continue;
        if (c == '(') { i++; num = evalFrom(s, i); continue; }   // group = one operand; i lands on ')'
        if (op == '+') st.push_back(num);
        else if (op == '-') st.push_back(-num);
        else if (op == '*') st.back() *= num;
        else st.back() /= num;
        if (c == ')' || c == '\0') break;          // caller resumes after ')'
        op = c;
        num = 0;
    }
    return accumulate(st.begin(), st.end(), 0LL);
}

int calculate(const string& s) {
    size_t i = 0;
    return evalFrom(s, i);
}

// ---------- Driver ----------
int main() {
    for (string s : {"1+1", "6-4/2", "2*(5+5*2)/3+(6/2+8)", "((2))", "(0-3)/2"}) {
        cout << "two stacks: " << calculateTwoStacks(s) << "\n";
        cout << "recursive : " << calculate(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Passing size_t& i lets the recursive call advance the caller's position.
 * - Nested ternaries pick the operator result in one expression.
 * - prec(top) >= prec(c) pops equal precedence first: left-to-right evaluation.
 */
