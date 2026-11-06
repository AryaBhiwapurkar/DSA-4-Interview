/*
 * 0066. Plus One  |  Easy  |  Math & Geometry
 * Link: https://leetcode.com/problems/plus-one/
 *
 * Problem: A big number is given as its digits (most significant first). Add one.
 *
 * Examples:
 *   [1,2,3]    -> [1,2,4]
 *   [4,3,2,1]  -> [4,3,2,2]
 *   [9]        -> [1,0]
 *   [9,9,9]    -> [1,0,0,0]
 *   [1,9,9]    -> [2,0,0]
 *   [0]        -> [1]
 *
 * Approaches:
 *   1. General carry loop          O(n) time, O(1) extra
 *   2. Early-exit carry  ⭐        O(n) time, O(1) extra   <- go-to
 *   (Parsing into an integer overflows past ~19 digits, so it's not an option in C++.)
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: General Carry Loop ----------
vector<int> plusOneCarry(vector<int> digits) {
    int carry = 1;                                 // the "+1"
    for (int i = (int)digits.size() - 1; i >= 0; i--) {
        int sum = digits[i] + carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry) digits.insert(digits.begin(), carry);
    return digits;
}

// ---------- Approach 2: Early-exit Carry ⭐ ----------
vector<int> plusOne(vector<int> digits) {
    for (int i = (int)digits.size() - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;                         // carry absorbed
        }
        digits[i] = 0;                             // 9 + 1 = 10: write 0, carry on
    }
    digits.insert(digits.begin(), 1);              // all nines
    return digits;
}

// ---------- Driver ----------
void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    vector<vector<int>> tests = {{1, 2, 3}, {4, 3, 2, 1}, {9}, {9, 9, 9}, {1, 9, 9}, {0}};
    for (auto& t : tests) {
        cout << "carry: "; print(plusOneCarry(t));
        cout << "early: "; print(plusOne(t));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Iterate down with a signed int: size() - 1 on an empty vector wraps around as size_t.
 * - v.insert(v.begin(), x) prepends (O(n)).
 * - Taking the vector by value gives a copy you can modify and return.
 */
