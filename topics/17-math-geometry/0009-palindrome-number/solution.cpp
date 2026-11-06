/*
 * 0009. Palindrome Number  |  Easy  |  Math & Geometry
 * Link: https://leetcode.com/problems/palindrome-number/
 *
 * Problem: Is the integer the same read forwards and backwards (base 10)?
 *
 * Examples:
 *   121         -> true
 *   -121        -> false
 *   10          -> false
 *   0           -> true
 *   12321       -> true   (odd length)
 *   2147483647  -> false  (full reverse would overflow int)
 *
 * Approaches:
 *   1. String compare           O(d) time, O(d) space
 *   2. Full reverse (long long) O(d) time, O(1) space
 *   3. Reverse half  ⭐         O(d) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: String Compare ----------
bool isPalindromeString(int x) {
    string s = to_string(x);
    return s == string(s.rbegin(), s.rend());
}

// ---------- Approach 2: Full Reverse ----------
bool isPalindromeFull(int x) {
    if (x < 0) return false;
    long long rev = 0;                             // 64-bit: the reverse may not fit in int
    for (int t = x; t; t /= 10) rev = rev * 10 + t % 10;
    return rev == x;
}

// ---------- Approach 3: Reverse Half ⭐ ----------
bool isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;   // trailing 0 can't be a leading 0
    int rev = 0;
    while (x > rev) {                              // stop at the middle
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return x == rev || x == rev / 10;              // rev / 10 drops the middle digit
}

// ---------- Driver ----------
int main() {
    cout << boolalpha;
    for (int x : {121, -121, 10, 0, 12321, 2147483647}) {
        cout << "string: " << isPalindromeString(x) << "\n";
        cout << "full  : " << isPalindromeFull(x) << "\n";
        cout << "half  : " << isPalindrome(x) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - string(s.rbegin(), s.rend()) builds a reversed copy.
 * - C++ % keeps the sign of the dividend (-121 % 10 == -1); integer / truncates towards 0.
 * - cout << boolalpha prints true/false instead of 1/0.
 */
