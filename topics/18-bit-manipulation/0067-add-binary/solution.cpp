/*
 * 0067. Add Binary  |  Easy  |  Bit Manipulation
 * Link: https://leetcode.com/problems/add-binary/
 *
 * Problem: Add two binary strings and return the sum as a binary string.
 *
 * Examples:
 *   "11", "1"         -> "100"
 *   "1010", "1011"    -> "10101"
 *   "0", "0"          -> "0"
 *   "1111", "1"       -> "10000"
 *   "1", "111"        -> "1000"
 *
 * Approaches:
 *   1. Pad to equal length, add column by column  O(max(m, n)) time, O(max(m, n)) space
 *   2. Two pointers from the right with carry  ⭐  O(max(m, n)) time, O(max(m, n)) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Pad + Column Add ----------
string addBinaryPad(string a, string b) {
    size_t n = max(a.size(), b.size());
    a.insert(0, n - a.size(), '0');                // left-pad with zeros
    b.insert(0, n - b.size(), '0');
    string out;
    int carry = 0;
    for (int k = n - 1; k >= 0; k--) {
        int s = (a[k] - '0') + (b[k] - '0') + carry;
        out.push_back('0' + s % 2);
        carry = s / 2;
    }
    if (carry) out.push_back('1');
    reverse(out.begin(), out.end());
    return out;
}

// ---------- Approach 2: Two Pointers + Carry ⭐ ----------
string addBinary(const string& a, const string& b) {
    int i = a.size() - 1, j = b.size() - 1, carry = 0;
    string out;
    while (i >= 0 || j >= 0 || carry) {
        int s = carry;
        if (i >= 0) s += a[i--] - '0';
        if (j >= 0) s += b[j--] - '0';
        out.push_back('0' + (s & 1));              // sum bit
        carry = s >> 1;
    }
    reverse(out.begin(), out.end());               // built least significant first
    return out;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {{"11", "1"}, {"1010", "1011"}, {"0", "0"}, {"1111", "1"}, {"1", "111"}};
    for (auto& [a, b] : tests) {
        cout << "pad  : " << addBinaryPad(a, b) << "\n";
        cout << "carry: " << addBinary(a, b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - a[i--] - '0' reads a digit and moves the pointer left in one step.
 * - push_back then reverse is O(n); inserting at the front each time would be O(n^2).
 * - '0' + bit converts 0/1 back to a character.
 */
