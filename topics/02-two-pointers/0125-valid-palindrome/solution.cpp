/*
 * 0125. Valid Palindrome  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/valid-palindrome/
 *
 * Problem: After lowercasing and removing non-alphanumeric characters,
 *          does the string read the same forwards and backwards?
 *
 * Examples:
 *   "A man, a plan, a canal: Panama"  -> true
 *   "race a car"                      -> false
 *   " "                               -> true
 *   "0P"                              -> false
 *
 * Approaches:
 *   1. Clean + reverse      O(n) time, O(n) space
 *   2. Two pointers  ⭐      O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Clean + Reverse ----------
bool isPalindromeClean(const string& s) {
    string t;
    for (unsigned char c : s)
        if (isalnum(c)) t += tolower(c);
    return t == string(t.rbegin(), t.rend());
}

// ---------- Approach 2: Two Pointers ⭐ ----------
bool isPalindrome(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        while (l < r && !isalnum((unsigned char)s[l])) l++;   // skip junk on the left
        while (l < r && !isalnum((unsigned char)s[r])) r--;   // skip junk on the right
        if (tolower((unsigned char)s[l]) != tolower((unsigned char)s[r])) return false;
        l++, r--;
    }
    return true;
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"A man, a plan, a canal: Panama", "race a car", " ", "0P"};
    cout << boolalpha;
    for (auto& s : tests) {
        cout << "clean   : " << isPalindromeClean(s) << "\n";
        cout << "pointers: " << isPalindrome(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - isalnum/tolower live in <cctype>; pass unsigned char to avoid UB on negative chars.
 * - string(t.rbegin(), t.rend()) builds a reversed copy.
 * - l++, r-- uses the comma operator to update both in one statement.
 */
