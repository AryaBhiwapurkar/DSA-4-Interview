/*
 * 0012. Integer to Roman  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/integer-to-roman/
 *
 * Problem: Convert an integer in [1, 3999] to a Roman numeral using the
 *          standard subtractive forms (IV, IX, XL, XC, CD, CM).
 *
 * Examples:
 *   3749  -> "MMMDCCXLIX"
 *   58    -> "LVIII"
 *   1994  -> "MCMXCIV"
 *   3999  -> "MMMCMXCIX"
 *
 * Approaches:
 *   1. Digit lookup tables          O(1) time, O(1) space
 *   2. Greedy over value table  ⭐   O(1) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Digit Lookup Tables ----------
string intToRomanTables(int num) {
    static const string th[] = {"", "M", "MM", "MMM"};
    static const string hu[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    static const string te[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    static const string on[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    return th[num / 1000] + hu[num % 1000 / 100] + te[num % 100 / 10] + on[num % 10];
}

// ---------- Approach 2: Greedy Over Value Table ⭐ ----------
string intToRoman(int num) {
    static const vector<pair<int, string>> table = {      // descending; includes subtractive pairs
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
        {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    string out;
    for (const auto& [value, sym] : table)
        while (num >= value) {                             // while, not if: symbols can repeat
            out += sym;
            num -= value;
        }
    return out;
}

// ---------- Driver ----------
int main() {
    for (int num : {3749, 58, 1994, 3999}) {
        cout << "tables: " << intToRomanTables(num) << "\n";
        cout << "greedy: " << intToRoman(num) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - static const local tables are built once.
 * - Range-for over an initializer list: for (int x : {1, 2, 3}).
 * - Structured binding in range-for: const auto& [value, sym].
 */
