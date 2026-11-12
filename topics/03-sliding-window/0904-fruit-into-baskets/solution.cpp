/*
 * 0904. Fruit Into Baskets  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/fruit-into-baskets/
 *
 * Problem: Longest contiguous run of trees containing at most 2 fruit types.
 *
 * Examples:
 *   [1,2,1]                    -> 3
 *   [0,1,2,2]                  -> 3
 *   [1,2,3,2,2]                -> 4
 *   [3,3,3,1,2,1,1,2,3,3,4]    -> 5
 *   [1,2,3,1,2,3]              -> 2
 *
 * Approaches:
 *   1. Every start, extend               O(n^2) time
 *   2. Shrinking window + map  ⭐        O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Every Start ----------
int totalFruitBrute(const vector<int>& fruits) {
    int n = fruits.size(), best = 0;
    for (int l = 0; l < n; l++) {
        set<int> types;
        int r = l;
        while (r < n) {
            types.insert(fruits[r]);
            if (types.size() > 2) break;
            r++;
        }
        best = max(best, r - l);
    }
    return best;
}

// ---------- Approach 2: Shrinking Window ⭐ ----------
int totalFruit(const vector<int>& fruits) {
    unordered_map<int, int> cnt;                   // at most 3 keys at any time
    int l = 0, best = 0;
    for (int r = 0; r < (int)fruits.size(); r++) {
        cnt[fruits[r]]++;
        while (cnt.size() > 2) {
            if (--cnt[fruits[l]] == 0) cnt.erase(fruits[l]);
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<int>> tests = {{1, 2, 1}, {0, 1, 2, 2}, {1, 2, 3, 2, 2}, {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4}, {1, 2, 3, 1, 2, 3}};
    for (auto& t : tests) {
        cout << "brute : " << totalFruitBrute(t) << "\n";
        cout << "window: " << totalFruit(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - cnt.size() > 2 compares size_t with an int literal: fine for small positive constants.
 * - set<int> tracks distinct types in the brute force.
 * - The window template is identical to 0340 with k = 2.
 */
