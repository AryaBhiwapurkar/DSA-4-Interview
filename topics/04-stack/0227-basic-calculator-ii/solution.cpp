/*
 * 0227. Basic Calculator II  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/basic-calculator-ii/
 *
 * Problem: Evaluate a string with non-negative ints, + - * /, spaces; no parentheses.
 *          Division truncates toward zero.
 *
 * Examples:
 *   "3+2*2"      -> 7
 *   " 3/2 "      -> 1
 *   " 3+5 / 2 "  -> 5
 *   "14-3/2"     -> 13
 *   "42"         -> 42
 *
 * Approaches:
 *   1. Two passes (tokens, then precedence)       O(n) time, O(n) space
 *   2. Stack with previous operator  ⭐           O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Two Passes ----------
int calculateTwoPass(const string& s) {
    vector<long long> nums;
    vector<char> ops;
    long long num = 0;
    for (char c : s) {
        if (isdigit(c)) num = num * 10 + (c - '0');
        else if (c != ' ') { nums.push_back(num); ops.push_back(c); num = 0; }
    }
    nums.push_back(num);
    vector<long long> terms = {nums[0]};           // collapse * and / first
    vector<char> addOps;
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] == '*') terms.back() *= nums[i + 1];
        else if (ops[i] == '/') terms.back() /= nums[i + 1];
        else { addOps.push_back(ops[i]); terms.push_back(nums[i + 1]); }
    }
    long long res = terms[0];
    for (size_t i = 0; i < addOps.size(); i++) res += addOps[i] == '+' ? terms[i + 1] : -terms[i + 1];
    return res;
}

// ---------- Approach 2: Previous-operator Stack ⭐ ----------
int calculate(const string& s) {
    vector<long long> st;
    long long num = 0;
    char op = '+';                                 // operator before the current number
    for (size_t i = 0; i <= s.size(); i++) {
        char c = i < s.size() ? s[i] : '\0';       // '\0' = end: flush the last number
        if (isdigit(c)) { num = num * 10 + (c - '0'); continue; }
        if (c == ' ') continue;
        if (op == '+') st.push_back(num);
        else if (op == '-') st.push_back(-num);
        else if (op == '*') st.back() *= num;
        else st.back() /= num;                     // C++ / truncates toward zero
        op = c;
        num = 0;
    }
    return accumulate(st.begin(), st.end(), 0LL);
}

// ---------- Driver ----------
int main() {
    for (string s : {"3+2*2", " 3/2 ", " 3+5 / 2 ", "14-3/2", "42"}) {
        cout << "two-pass: " << calculateTwoPass(s) << "\n";
        cout << "stack   : " << calculate(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Iterating to i == s.size() with a '\0' sentinel flushes the final number in the same loop.
 * - C++ integer / truncates toward zero, which is what the problem wants.
 * - accumulate(..., 0LL) sums in long long (the init type sets the accumulator type).
 */
