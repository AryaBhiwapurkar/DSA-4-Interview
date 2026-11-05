/*
 * 0846. Hand of Straights  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/hand-of-straights/
 *
 * Problem: Can the cards be split into groups of groupSize consecutive values,
 *          every card used exactly once?
 *
 * Examples:
 *   [1,2,3,6,2,3,4,7,8], 3   -> true
 *   [1,2,3,4,5], 4           -> false
 *   [1], 1                   -> true
 *   [1,1,2,2,3,3], 3         -> true
 *   [1,2,4], 3               -> false
 *
 * Approaches:
 *   1. Sort + remove one group at a time       O(n^2) with a list, O(n log n) with a multiset
 *   2. Sorted counts, build from the min  ⭐    O(n log n + n*k) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sort + Remove ----------
bool isNStraightHandBrute(const vector<int>& hand, int k) {
    if (hand.size() % k) return false;
    multiset<int> cards(hand.begin(), hand.end());
    while (!cards.empty()) {
        int low = *cards.begin();                  // the smallest card must start a group
        for (int v = low; v < low + k; v++) {
            auto it = cards.find(v);
            if (it == cards.end()) return false;
            cards.erase(it);                       // erase ONE copy, not every v
        }
    }
    return true;
}

// ---------- Approach 2: Sorted Counts ⭐ ----------
bool isNStraightHand(const vector<int>& hand, int k) {
    if (hand.size() % k) return false;
    map<int, int> count;                           // ordered: iterate from the smallest
    for (int x : hand) count[x]++;
    for (auto& [low, c] : count) {
        if (c == 0) continue;
        int need = c;                              // copy: count[low] changes below
        for (int v = low; v < low + k; v++) {
            auto it = count.find(v);
            if (it == count.end() || it->second < need) return false;
            it->second -= need;                    // open `need` groups starting at low
        }
    }
    return true;
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 2, 3, 6, 2, 3, 4, 7, 8}, 3}, {{1, 2, 3, 4, 5}, 4}, {{1}, 1}, {{1, 1, 2, 2, 3, 3}, 3}, {{1, 2, 4}, 3}
    };
    cout << boolalpha;
    for (auto& [hand, k] : tests) {
        cout << "brute : " << isNStraightHandBrute(hand, k) << "\n";
        cout << "counts: " << isNStraightHand(hand, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - multiset::erase(value) removes ALL copies; erase(iterator) removes one.
 * - count.find(v) avoids map[] inserting missing keys while iterating.
 * - Copy `c` into `need` first: the inner loop zeroes count[low] (c is a reference).
 */
