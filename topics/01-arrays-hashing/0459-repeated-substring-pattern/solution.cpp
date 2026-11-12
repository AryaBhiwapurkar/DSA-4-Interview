/*
 * 0459. Repeated Substring Pattern  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/repeated-substring-pattern/
 *
 * Problem: Can s be formed by repeating one of its substrings at least twice?
 *
 * Examples:
 *   "abab"          -> true
 *   "aba"           -> false
 *   "abcabcabcabc"  -> true
 *   "a"             -> false
 *   "aaaa"          -> true
 *   "abac"          -> false
 *
 * Approaches:
 *   1. Divisor-length check  ⭐   O(n * d(n)) time, O(n) space   <- go-to
 *   2. Doubled string             O(n) with a linear search, O(n) space
 *   3. KMP prefix function        O(n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Divisor-length Check ⭐ ----------
bool repeatedSubstringPattern(const string& s) {
    int n = s.size();
    for (int len = 1; len <= n / 2; len++) {       // block must repeat at least twice
        if (n % len) continue;
        bool ok = true;
        for (int i = len; i < n && ok; i++) ok = s[i] == s[i - len];   // s[i] equals the char one block back
        if (ok) return true;
    }
    return false;
}

// ---------- Approach 2: Doubled String ----------
bool repeatedSubstringPatternDoubled(const string& s) {
    string t = s + s;
    return t.substr(1, t.size() - 2).find(s) != string::npos;   // trim first and last char
}

// ---------- Approach 3: KMP Prefix Function ----------
bool repeatedSubstringPatternKMP(const string& s) {
    int n = s.size();
    vector<int> lps(n, 0);
    for (int i = 1, k = 0; i < n; i++) {
        while (k > 0 && s[i] != s[k]) k = lps[k - 1];
        if (s[i] == s[k]) k++;
        lps[i] = k;
    }
    int p = n - lps[n - 1];                        // smallest period
    return lps[n - 1] > 0 && n % p == 0;
}

// ---------- Driver ----------
int main() {
    cout << boolalpha;
    for (string s : {"abab", "aba", "abcabcabcabc", "a", "aaaa", "abac"}) {
        cout << "divisor: " << repeatedSubstringPattern(s) << "\n";
        cout << "doubled: " << repeatedSubstringPatternDoubled(s) << "\n";
        cout << "kmp    : " << repeatedSubstringPatternKMP(s) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - s[i] == s[i - len] for all i >= len is the same as "s is s[:len] repeated" (no copies built).
 * - str.find(sub) returns string::npos when absent.
 * - for (int i = 1, k = 0; ...) declares two loop variables of the same type.
 */
