/*
 * 1011. Capacity To Ship Packages Within D Days  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
 *
 * Problem: Ship packages in order, one load per day, each load <= capacity.
 *          Return the smallest capacity that finishes within `days` days.
 *
 * Examples:
 *   [1,2,3,4,5,6,7,8,9,10], days = 5   -> 15
 *   [3,2,2,4,1,4],          days = 3   -> 6
 *   [1,2,3,1,1],            days = 4   -> 3
 *   [10],                   days = 1   -> 10
 *   [1,1,1,1],              days = 4   -> 1
 *
 * Approaches:
 *   1. Try every capacity                O(n (sum - max)) time, O(1) space
 *   2. Binary search on capacity ⭐      O(n log sum) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

int daysNeeded(const vector<int>& w, int cap) {
    int d = 1, load = 0;
    for (int x : w) {
        if (load + x > cap) { d++; load = 0; }   // x goes on the next day
        load += x;
    }
    return d;
}

// ---------- Approach 1: Try Every Capacity ----------
int shipWithinDaysLinear(const vector<int>& w, int days) {
    int cap = *max_element(w.begin(), w.end());
    while (daysNeeded(w, cap) > days) cap++;
    return cap;
}

// ---------- Approach 2: Binary Search on Capacity ⭐ ----------
int shipWithinDays(const vector<int>& w, int days) {
    int lo = *max_element(w.begin(), w.end());   // must fit the heaviest package
    int hi = accumulate(w.begin(), w.end(), 0);  // everything in one day
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (daysNeeded(w, mid) <= days) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5}, {{3, 2, 2, 4, 1, 4}, 3}, {{1, 2, 3, 1, 1}, 4},
        {{10}, 1}, {{1, 1, 1, 1}, 4}};
    for (auto& [w, days] : tests) {
        cout << "linear: " << shipWithinDaysLinear(w, days) << "\n";
        cout << "binary: " << shipWithinDays(w, days) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - accumulate(begin, end, 0) returns int here; the sum (<= 2.5e7) fits.
 * - A helper that counts days keeps the binary search body to two lines.
 * - auto& [w, days] binds by reference, avoiding a vector copy per test.
 */
