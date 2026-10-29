/*
 * 0076. Minimum Window Substring  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/minimum-window-substring/
 *
 * Problem: Return the shortest substring of s containing every character
 *          of t (with multiplicity), or "" if none exists.
 *
 * Examples:
 *   s="ADOBECODEBANC", t="ABC"  -> "BANC"
 *   s="a", t="a"                -> "a"
 *   s="a", t="aa"               -> ""
 *   s="aAbB", t="AB"            -> "AbB"
 *
 * Approaches:
 *   1. Brute force                         O(|s|^2 * 128) time, O(128) space
 *   2. Window, compare full counts         O(128 * |s|) time, O(128) space
 *   3. Window with have/need  ⭐            O(|s| + |t|) time, O(128) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

bool covers(const array<int, 128>& win, const array<int, 128>& tc) {
    for (int c = 0; c < 128; c++)
        if (win[c] < tc[c]) return false;
    return true;
}

// ---------- Approach 1: Brute Force ----------
string minWindowBrute(const string& s, const string& t) {
    array<int, 128> tc{};
    for (char c : t) tc[c]++;
    int n = s.size(), bestLen = INT_MAX, bestL = 0;
    for (int i = 0; i < n; i++) {
        array<int, 128> win{};
        for (int j = i; j < n; j++) {
            win[s[j]]++;
            if (covers(win, tc)) {
                if (j - i + 1 < bestLen) bestLen = j - i + 1, bestL = i;
                break;                                   // longer windows from i can't be shorter
            }
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}

// ---------- Approach 2: Window, Compare Full Counts ----------
string minWindowCompare(const string& s, const string& t) {
    array<int, 128> tc{}, win{};
    for (char c : t) tc[c]++;
    int l = 0, bestLen = INT_MAX, bestL = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        win[s[r]]++;
        while (covers(win, tc)) {                         // O(128) validity check
            if (r - l + 1 < bestLen) bestLen = r - l + 1, bestL = l;
            win[s[l++]]--;
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}

// ---------- Approach 3: Window With have/need ⭐ ----------
string minWindow(const string& s, const string& t) {
    array<int, 128> tc{}, win{};
    for (char c : t) tc[c]++;
    int need = 0;
    for (int c = 0; c < 128; c++) need += tc[c] > 0;      // distinct chars to satisfy
    int have = 0, l = 0, bestLen = INT_MAX, bestL = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        char c = s[r];
        if (++win[c] == tc[c]) have++;                    // c just became satisfied
        while (have == need) {
            if (r - l + 1 < bestLen) bestLen = r - l + 1, bestL = l;
            char d = s[l++];
            if (win[d]-- == tc[d]) have--;                // d drops below its requirement
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);   // slice once at the end
}

// ---------- Driver ----------
int main() {
    vector<pair<string, string>> tests = {{"ADOBECODEBANC", "ABC"}, {"a", "a"}, {"a", "aa"}, {"aAbB", "AB"}};
    for (auto& [s, t] : tests) {
        cout << "brute   : \"" << minWindowBrute(s, t) << "\"\n";
        cout << "compare : \"" << minWindowCompare(s, t) << "\"\n";
        cout << "have/need: \"" << minWindow(s, t) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - ++win[c] == tc[c] increments then compares; win[d]-- == tc[d] compares then decrements.
 * - A char indexes a 128-array directly for ASCII input.
 * - Comma in `if (...) a = x, b = y;` performs both assignments in one statement.
 * - Note: tc[c] == 0 for chars not in t, so ++win[c] can never "reach" it (win >= 1).
 */
