/*
 * 0020. Valid Parentheses  |  Easy  |  Stack
 * Link: https://leetcode.com/problems/valid-parentheses/
 *
 * Problem: A string of ()[]{} is valid if every closer matches the most
 *          recent unclosed opener of the same type and nothing is left open.
 *
 * Examples:
 *   "()"      -> true
 *   "()[]{}"  -> true
 *   "(]"      -> false
 *   "([])"    -> true
 *   "([)]"    -> false
 *   "]"       -> false
 *   "(("      -> false
 *
 * Approaches:
 *   1. Repeated removal   O(n^2) time, O(n) space
 *   2. Stack  ⭐           O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Repeated Removal ----------
bool isValidBrute(string s) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (const char* p : {"()", "[]", "{}"}) {
            size_t pos;
            while ((pos = s.find(p)) != string::npos) {
                s.erase(pos, 2);
                changed = true;
            }
        }
    }
    return s.empty();
}

// ---------- Approach 2: Stack ⭐ ----------
bool isValid(const string& s) {
    unordered_map<char, char> match = {{')', '('}, {']', '['}, {'}', '{'}};
    vector<char> st;
    for (char c : s) {
        if (!match.count(c)) {             // opener
            st.push_back(c);
            continue;
        }
        if (st.empty() || st.back() != match[c]) return false;   // check empty BEFORE back()
        st.pop_back();
    }
    return st.empty();                     // leftovers = unclosed openers
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"()", "()[]{}", "(]", "([])", "([)]", "]", "(("};
    cout << boolalpha;
    for (auto& s : tests) {
        cout << "brute: " << isValidBrute(s) << "\n";
        cout << "stack: " << isValid(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<char> works as a stack (push_back / back / pop_back) and is
 *   usually faster than std::stack.
 * - Range-for over a braced list: `for (const char* p : {"()", "[]"})`.
 * - s.erase(pos, len) removes len chars in place.
 * - cout << boolalpha prints true/false instead of 1/0.
 */
