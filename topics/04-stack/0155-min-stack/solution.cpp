/*
 * 0155. Min Stack  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/min-stack/
 *
 * Problem: Design a stack with push, pop, top and getMin, all O(1).
 *          pop/top/getMin are only called on a non-empty stack.
 *
 * Examples:
 *   push -2, push 0, push -3, getMin, pop, top, getMin
 *     -> [null,null,null,null,-3,null,0,-2]
 *   push 0, push 1, push 0, getMin, pop, getMin          (duplicate min)
 *     -> [null,null,null,null,0,null,0]
 *
 * Approaches:
 *   1. Plain stack, scan on getMin   O(n) getMin, O(n) space
 *   2. Stack of (val, min)  ⭐        O(1) all ops, O(n) space   <- go-to
 *   3. Two stacks                    O(1) all ops, O(n) space worst case
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Plain Stack, Scan for Min ----------
class MinStackBrute {
    vector<int> st;
public:
    void push(int val) { st.push_back(val); }
    void pop() { st.pop_back(); }
    int top() { return st.back(); }
    int getMin() { return *min_element(st.begin(), st.end()); }
};

// ---------- Approach 2: Stack of (val, min) ⭐ ----------
class MinStack {
    vector<pair<int, int>> st;             // (value, min of this and everything below)
public:
    void push(int val) {
        int m = st.empty() ? val : min(val, st.back().second);
        st.push_back({val, m});
    }
    void pop() { st.pop_back(); }
    int top() { return st.back().first; }
    int getMin() { return st.back().second; }
};

// ---------- Approach 3: Two Stacks ----------
class MinStackTwoStacks {
    vector<int> st, mins;
public:
    void push(int val) {
        st.push_back(val);
        if (mins.empty() || val <= mins.back()) mins.push_back(val);   // <= keeps duplicate mins
    }
    void pop() {
        if (st.back() == mins.back()) mins.pop_back();
        st.pop_back();
    }
    int top() { return st.back(); }
    int getMin() { return mins.back(); }
};

// ---------- Driver ----------
template <class S>
void run(const string& label, const vector<string>& ops, const vector<int>& args) {
    S st;
    cout << label << ": [null";            // ops[0] is the constructor
    for (size_t i = 1; i < ops.size(); i++) {
        cout << ",";
        if (ops[i] == "push") { st.push(args[i]); cout << "null"; }
        else if (ops[i] == "pop") { st.pop(); cout << "null"; }
        else if (ops[i] == "top") cout << st.top();
        else cout << st.getMin();
    }
    cout << "]\n";
}

int main() {
    vector<pair<vector<string>, vector<int>>> tests = {
        {{"MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"},
         {0, -2, 0, -3, 0, 0, 0, 0}},
        {{"MinStack", "push", "push", "push", "getMin", "pop", "getMin"},
         {0, 0, 1, 0, 0, 0, 0}},
    };
    for (auto& [ops, args] : tests) {
        run<MinStackBrute>("brute    ", ops, args);
        run<MinStack>("pairs    ", ops, args);
        run<MinStackTwoStacks>("twoStacks", ops, args);
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<pair<int,int>>: .back().first / .back().second read the top pair.
 * - A function template run<S>() drives several classes with the same API.
 * - *min_element(b, e) dereferences the iterator to the smallest value.
 * - std::stack::pop() returns void; read top() before popping.
 */
