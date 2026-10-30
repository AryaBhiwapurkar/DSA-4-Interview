/*
 * 0071. Simplify Path  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/simplify-path/
 *
 * Problem: Turn an absolute Unix path into canonical form: single slashes,
 *          no trailing slash, "." and ".." resolved ("..." is a name).
 *
 * Examples:
 *   "/home/"                             -> "/home"
 *   "/home//foo/"                        -> "/home/foo"
 *   "/home/user/Documents/../Pictures"   -> "/home/user/Pictures"
 *   "/../"                               -> "/"
 *   "/.../a/../b/c/../d/./"              -> "/.../b/d"
 *   "/a/./b/../../c/"                    -> "/c"
 *   "/"                                  -> "/"
 *
 * Approaches:
 *   1. Split + stack  ⭐   O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Split + Stack ⭐ ----------
string simplifyPath(const string& path) {
    vector<string> st;
    stringstream ss(path);
    string part;
    while (getline(ss, part, '/')) {       // "" between repeated slashes
        if (part.empty() || part == ".") continue;
        if (part == "..") {
            if (!st.empty()) st.pop_back();    // ".." at root is a no-op
        } else {
            st.push_back(part);
        }
    }
    if (st.empty()) return "/";
    string res;
    for (auto& d : st) res += "/" + d;
    return res;
}

// ---------- Driver ----------
int main() {
    vector<string> tests = {"/home/", "/home//foo/", "/home/user/Documents/../Pictures", "/../",
                            "/.../a/../b/c/../d/./", "/a/./b/../../c/", "/"};
    for (auto& p : tests) {
        cout << "stack: \"" << simplifyPath(p) << "\"\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - getline(stream, out, delim) splits on any single char delimiter.
 * - stringstream ss(s) wraps a string so stream functions can read it.
 * - String concatenation with + works on std::string, not on two literals.
 */
