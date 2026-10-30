/*
 * 0150. Evaluate Reverse Polish Notation  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/
 *
 * Problem: Evaluate a postfix expression of integers and + - * /.
 *          Division truncates toward zero. Input is always valid.
 *
 * Examples:
 *   ["2","1","+","3","*"]                                        -> 9
 *   ["4","13","5","/","+"]                                       -> 6
 *   ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]    -> 22
 *   ["18"]                                                       -> 18
 *   ["4","-3","/"]                                               -> -1
 *
 * Approaches:
 *   1. Repeated collapse   O(n^2) time, O(n) space
 *   2. Stack  ⭐            O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

bool isOp(const string& t) { return t.size() == 1 && string("+-*/").find(t[0]) != string::npos; }

int apply(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        default:  return a / b;            // C++ truncates toward zero already
    }
}

// ---------- Approach 1: Repeated Collapse ----------
int evalRPNBrute(vector<string> t) {
    while (t.size() > 1) {
        int i = 0;
        while (!isOp(t[i])) i++;           // first operator; its operands are t[i-2], t[i-1]
        t[i - 2] = to_string(apply(stoi(t[i - 2]), stoi(t[i - 1]), t[i][0]));
        t.erase(t.begin() + i - 1, t.begin() + i + 1);
    }
    return stoi(t[0]);
}

// ---------- Approach 2: Stack ⭐ ----------
int evalRPN(const vector<string>& tokens) {
    vector<int> st;
    for (auto& t : tokens) {
        if (!isOp(t)) {                    // "-11" is a number: isOp checks length too
            st.push_back(stoi(t));
            continue;
        }
        int b = st.back(); st.pop_back();  // first pop = RIGHT operand
        int a = st.back(); st.pop_back();
        st.push_back(apply(a, b, t[0]));
    }
    return st.back();
}

// ---------- Driver ----------
int main() {
    vector<vector<string>> tests = {
        {"2", "1", "+", "3", "*"},
        {"4", "13", "5", "/", "+"},
        {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"},
        {"18"},
        {"4", "-3", "/"},
    };
    for (auto& t : tests) {
        cout << "brute: " << evalRPNBrute(t) << "\n";
        cout << "stack: " << evalRPN(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - stoi(s) parses "-11" correctly; to_string(x) goes the other way.
 * - Integer / and % truncate toward zero in C++ (since C++11).
 * - vector::erase(first, last) removes the half-open range [first, last).
 * - switch on a char with `default` keeps the operator dispatch compact.
 */
