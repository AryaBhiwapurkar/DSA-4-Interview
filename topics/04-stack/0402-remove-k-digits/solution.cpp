/*
 * 0402. Remove K Digits  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/remove-k-digits/
 *
 * Problem: Remove exactly k digits from num to make the smallest number (no leading zeros).
 *
 * Examples:
 *   "1432219", k = 3  -> "1219"
 *   "10200",   k = 1  -> "200"
 *   "10",      k = 2  -> "0"
 *   "12345",   k = 2  -> "123"
 *   "112",     k = 1  -> "11"
 *
 * Approaches:
 *   1. Remove one peak at a time      O(n * k) time
 *   2. Monotonic stack  ⭐            O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

string stripZeros(const string& s) {
    size_t i = s.find_first_not_of('0');
    return i == string::npos ? "0" : s.substr(i);
}

// ---------- Approach 1: One Peak at a Time ----------
string removeKdigitsPeaks(string num, int k) {
    while (k--) {
        size_t i = 0;
        while (i + 1 < num.size() && num[i] <= num[i + 1]) i++;   // first digit bigger than its successor
        num.erase(i, 1);
    }
    return stripZeros(num);
}

// ---------- Approach 2: Monotonic Stack ⭐ ----------
string removeKdigits(const string& num, int k) {
    string st;                                     // string as a stack of digits
    for (char d : num) {
        while (k > 0 && !st.empty() && st.back() > d) {
            st.pop_back();                         // a smaller digit earlier always wins
            k--;
        }
        st.push_back(d);
    }
    st.resize(st.size() - min<size_t>(k, st.size()));   // leftover k: trim the tail
    return stripZeros(st);
}

// ---------- Driver ----------
int main() {
    vector<pair<string, int>> tests = {{"1432219", 3}, {"10200", 1}, {"10", 2}, {"12345", 2}, {"112", 1}};
    for (auto& [num, k] : tests) {
        cout << "peaks: \"" << removeKdigitsPeaks(num, k) << "\"\n";
        cout << "stack: \"" << removeKdigits(num, k) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - std::string works as a char stack (push_back / back / pop_back).
 * - find_first_not_of('0') locates the first non-zero; npos means all zeros.
 * - min<size_t>(k, n) forces one type so min() compiles with mixed int/size_t.
 */
