/*
 * 0013. Roman to Integer  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/roman-to-integer/
 *
 * Problem: Convert a valid Roman numeral (1..3999) to an integer.
 *          IV, IX, XL, XC, CD, CM are subtractive pairs.
 *
 * Examples:
 *   "III"       -> 3
 *   "LVIII"     -> 58
 *   "MCMXCIV"   -> 1994
 *   "MMMCMXCIX" -> 3999
 *
 * Approaches:
 *   1. Match two-char pairs first   O(n) time, O(1) space
 *   2. Compare with next  ⭐         O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

int val(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
    }
    return 0;
}

// ---------- Approach 1: Match Two-Char Pairs First ----------
int romanToIntPairs(const string& s) {
    static const unordered_map<string, int> pairs = {
        {"IV", 4}, {"IX", 9}, {"XL", 40}, {"XC", 90}, {"CD", 400}, {"CM", 900}
    };
    int total = 0;
    size_t i = 0;
    while (i < s.size()) {
        if (i + 1 < s.size()) {
            auto it = pairs.find(s.substr(i, 2));
            if (it != pairs.end()) {
                total += it->second;
                i += 2;
                continue;
            }
        }
        total += val(s[i++]);
    }
    return total;
}

// ---------- Approach 2: Compare With Next ⭐ ----------
int romanToInt(const string& s) {
    int total = 0;
    for (size_t i = 0; i < s.size(); i++) {
        int v = val(s[i]);
        if (i + 1 < s.size() && v < val(s[i + 1])) total -= v;   // smaller before larger: subtract
        else total += v;
    }
    return total;
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"III", "LVIII", "MCMXCIV", "MMMCMXCIX"};
    for (auto& s : tests) {
        cout << "pairs  : " << romanToIntPairs(s) << "\n";
        cout << "compare: " << romanToInt(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - switch on char is a fast, insert-free lookup table.
 * - s.substr(pos, len) copies a substring.
 * - static const local: the map is built once, not on every call.
 * - s[i++] reads s[i], then increments i.
 */
