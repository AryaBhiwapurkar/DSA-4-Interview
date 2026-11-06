/*
 * 0043. Multiply Strings  |  Medium  |  Math & Geometry
 * Link: https://leetcode.com/problems/multiply-strings/
 *
 * Problem: Multiply two non-negative decimal strings without converting them
 *          to integers. Return the product as a string.
 *
 * Examples:
 *   "2"   * "3"    -> "6"
 *   "123" * "456"  -> "56088"
 *   "0"   * "52"   -> "0"
 *   "9"   * "9"    -> "81"
 *   "999" * "999"  -> "998001"
 *   "123456789" * "987654321" -> "121932631112635269"
 *
 * Approaches:
 *   1. Multiply by each digit + add strings   O(m*n) time, O(m+n) space
 *   2. Position array  ⭐                     O(m*n) time, O(m+n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Multiply by Each Digit + Add Strings ----------
string addStrings(const string& a, const string& b) {
    string out;
    int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int s = carry + (i >= 0 ? a[i--] - '0' : 0) + (j >= 0 ? b[j--] - '0' : 0);
        out.push_back('0' + s % 10);
        carry = s / 10;
    }
    reverse(out.begin(), out.end());
    return out;
}

string multiplyRows(string num1, string num2) {
    if (num1 == "0" || num2 == "0") return "0";
    string total = "0";
    int n = num2.size();
    for (int j = n - 1; j >= 0; j--) {
        int d = num2[j] - '0', carry = 0;
        string row(n - 1 - j, '0');                // shift: trailing zeros (built reversed)
        for (int i = (int)num1.size() - 1; i >= 0; i--) {
            int p = (num1[i] - '0') * d + carry;
            row.push_back('0' + p % 10);
            carry = p / 10;
        }
        if (carry) row.push_back('0' + carry);
        reverse(row.begin(), row.end());
        total = addStrings(total, row);
    }
    return total;
}

// ---------- Approach 2: Position Array ⭐ ----------
string multiply(string num1, string num2) {
    int m = num1.size(), n = num2.size();
    vector<int> res(m + n, 0);                     // product has at most m + n digits
    for (int i = m - 1; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--) {
            int sum = (num1[i] - '0') * (num2[j] - '0') + res[i + j + 1];
            res[i + j + 1] = sum % 10;
            res[i + j] += sum / 10;                // may exceed 9 briefly; fixed by a later pair
        }
    string out;
    for (int d : res)
        if (!(out.empty() && d == 0)) out.push_back('0' + d);   // skip leading zeros
    return out.empty() ? "0" : out;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {
        {"2", "3"}, {"123", "456"}, {"0", "52"}, {"9", "9"}, {"999", "999"},
        {"123456789", "987654321"}};
    for (auto& [a, b] : tests) {
        cout << "rows    : " << multiplyRows(a, b) << "\n";
        cout << "position: " << multiply(a, b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - c - '0' turns a digit char into its value; '0' + d goes back.
 * - string(k, '0') builds k copies of a char.
 * - Build digits backwards with push_back, then reverse(): cheaper than inserting at the front.
 */
