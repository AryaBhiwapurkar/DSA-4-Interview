/*
 * 0875. Koko Eating Bananas  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/koko-eating-bananas/
 *
 * Problem: Each hour Koko eats up to k bananas from one pile. Return the
 *          minimum integer k to finish all piles within h hours.
 *
 * Examples:
 *   [3,6,7,11],       h 8   -> 4
 *   [30,11,23,4,20],  h 5   -> 30
 *   [30,11,23,4,20],  h 6   -> 23
 *   [5],              h 5   -> 1
 *   [1,1,1,1],        h 4   -> 1
 *
 * Approaches:
 *   1. Try every speed               O(n * max) time, O(1) space
 *   2. Binary search on speed  ⭐     O(n log max) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

long long hoursAt(const vector<int>& piles, int k) {
    long long total = 0;                   // can reach 1e13 at k = 1
    for (int p : piles) total += (p + (long long)k - 1) / k;   // ceil(p / k), exact
    return total;
}

// ---------- Approach 1: Try Every Speed ----------
int minEatingSpeedBrute(const vector<int>& piles, int h) {
    for (int k = 1;; k++)
        if (hoursAt(piles, k) <= h) return k;   // k = max(piles) always works
}

// ---------- Approach 2: Binary Search on Speed ⭐ ----------
int minEatingSpeed(const vector<int>& piles, int h) {
    int lo = 1, hi = *max_element(piles.begin(), piles.end());   // lo = 1: never divide by 0
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (hoursAt(piles, mid) <= h) hi = mid;   // fast enough: try slower
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{3, 6, 7, 11}, 8}, {{30, 11, 23, 4, 20}, 5}, {{30, 11, 23, 4, 20}, 6}, {{5}, 5}, {{1, 1, 1, 1}, 4}
    };
    for (auto& [piles, h] : tests) {
        cout << "brute : " << minEatingSpeedBrute(piles, h) << "\n";
        cout << "binary: " << minEatingSpeed(piles, h) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Ceil division for positive ints: (p + k - 1) / k; widen to long long
 *   first so p + k can't overflow.
 * - *max_element(b, e) gives the largest value.
 * - `for (int k = 1;; k++)` is an endless loop that returns from inside.
 */
