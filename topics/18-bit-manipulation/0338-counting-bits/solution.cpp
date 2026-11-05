/*
 * 0338. Counting Bits  |  Easy  |  Bit Manipulation
 * Link: https://leetcode.com/problems/counting-bits/
 *
 * Problem: Return ans where ans[i] is the number of 1 bits in i, for 0 <= i <= n.
 *
 * Examples:
 *   2   -> [0,1,1]
 *   5   -> [0,1,1,2,1,2]
 *   0   -> [0]
 *   8   -> [0,1,1,2,1,2,2,3,1]
 *
 * Approaches:
 *   1. Popcount every number              O(n log n) time, O(1) extra
 *   2. DP: bits(i) = bits(i >> 1) + (i & 1)  ⭐   O(n) time, O(1) extra   <- go-to
 *   3. DP: bits(i) = bits(i & (i - 1)) + 1        O(n) time, O(1) extra
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Popcount Each ----------
vector<int> countBitsNaive(int n) {
    vector<int> res;
    for (int i = 0; i <= n; i++) {
        int c = 0;
        for (int x = i; x; x &= x - 1) c++;
        res.push_back(c);
    }
    return res;
}

// ---------- Approach 2: DP on i >> 1 ⭐ ----------
vector<int> countBits(int n) {
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; i++) ans[i] = ans[i >> 1] + (i & 1);   // drop last bit, add it back
    return ans;
}

// ---------- Approach 3: DP on i & (i - 1) ----------
vector<int> countBitsLowbit(int n) {
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; i++) ans[i] = ans[i & (i - 1)] + 1;     // drop lowest 1, add one
    return ans;
}

void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? ", " : "") << v[i];
    cout << "]\n";
}

// ---------- Driver ----------
int main() {
    for (int n : {2, 5, 0, 8}) {
        cout << "naive : "; print(countBitsNaive(n));
        cout << "shift : "; print(countBits(n));
        cout << "lowbit: "; print(countBitsLowbit(n));
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - (i & 1) needs parentheses: + has higher precedence than &.
 * - i >> 1 < i for i >= 1, so ans[i >> 1] is always filled already.
 * - for (int x = i; x; x &= x - 1) counts set bits inline.
 */
