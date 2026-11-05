/*
 * 0135. Candy  |  Hard  |  Greedy
 * Link: https://leetcode.com/problems/candy/
 *
 * Problem: Give each child at least one candy; a child rated higher than a
 *          neighbour gets more than that neighbour. Minimise the total.
 *
 * Examples:
 *   [1,0,2]             -> 5
 *   [1,2,2]             -> 4
 *   [5]                 -> 1
 *   [3,2,1]             -> 6
 *   [1,3,4,5,2]         -> 11
 *   [1,2,87,87,87,2,1]  -> 13
 *   [1,2,5,4,3,2]       -> 13  (right pass raises the peak)
 *
 * Approaches:
 *   1. Repeated relaxation until stable     O(n^2) time, O(n) space
 *   2. Two passes, left then right  ⭐       O(n) time, O(n) space   <- go-to
 *   3. One pass over slopes                 O(n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Repeated Relaxation ----------
int candyBrute(const vector<int>& r) {
    int n = r.size();
    vector<int> c(n, 1);
    bool changed = true;
    while (changed) {                              // fix violations until none remain
        changed = false;
        for (int i = 0; i < n; i++) {
            if (i > 0 && r[i] > r[i - 1] && c[i] <= c[i - 1]) { c[i] = c[i - 1] + 1; changed = true; }
            if (i + 1 < n && r[i] > r[i + 1] && c[i] <= c[i + 1]) { c[i] = c[i + 1] + 1; changed = true; }
        }
    }
    return accumulate(c.begin(), c.end(), 0);
}

// ---------- Approach 2: Two Passes ⭐ ----------
int candy(const vector<int>& r) {
    int n = r.size();
    vector<int> c(n, 1);
    for (int i = 1; i < n; i++)                    // left neighbour rule
        if (r[i] > r[i - 1]) c[i] = c[i - 1] + 1;
    for (int i = n - 2; i >= 0; i--)               // right neighbour rule, keep the left result
        if (r[i] > r[i + 1]) c[i] = max(c[i], c[i + 1] + 1);
    return accumulate(c.begin(), c.end(), 0);
}

// ---------- Approach 3: One Pass over Slopes ----------
int candySlopes(const vector<int>& r) {
    int total = 1, up = 0, down = 0, peak = 0;
    for (size_t i = 1; i < r.size(); i++) {
        if (r[i] > r[i - 1]) {
            up++;
            peak = up;
            down = 0;
            total += 1 + up;
        } else if (r[i] == r[i - 1]) {             // flat: restart from 1
            up = down = peak = 0;
            total += 1;
        } else {
            up = 0;
            down++;
            total += 1 + down - (peak >= down ? 1 : 0);   // peak grows only once down passes it
        }
    }
    return total;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 0, 2}, {1, 2, 2}, {5}, {3, 2, 1}, {1, 3, 4, 5, 2}, {1, 2, 87, 87, 87, 2, 1}, {1, 2, 5, 4, 3, 2}};
    for (auto& t : tests) {
        cout << "brute : " << candyBrute(t) << "\n";
        cout << "passes: " << candy(t) << "\n";
        cout << "slopes: " << candySlopes(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - accumulate(begin, end, 0) sums the candy array (<numeric>).
 * - `up = down = peak = 0` chains assignments right to left.
 * - Two independent passes are easier to get right than one pass with both neighbours.
 */
