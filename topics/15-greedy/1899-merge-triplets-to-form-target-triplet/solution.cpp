/*
 * 1899. Merge Triplets to Form Target Triplet  |  Medium  |  Greedy
 * Link: https://leetcode.com/problems/merge-triplets-to-form-target-triplet/
 *
 * Problem: Merging two triplets takes the element-wise max. Can repeated merges
 *          make some triplet equal to target?
 *
 * Examples:
 *   [[2,5,3],[1,8,4],[1,7,5]], [2,7,5]           -> true
 *   [[3,4,5],[4,5,6]], [3,2,5]                   -> false
 *   [[2,5,3],[2,3,4],[1,2,5],[5,2,3]], [5,5,5]   -> true
 *   [[1,1,1]], [1,1,1]                           -> true
 *   [[2,1,1],[1,2,1]], [2,2,2]                   -> false
 *
 * Approaches:
 *   1. Merge every usable triplet, compare   O(n) time, O(1) space
 *   2. One pass, three "found" flags  ⭐      O(n) time, O(1) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Merge Usable Triplets ----------
bool mergeTripletsMerge(const vector<vector<int>>& triplets, const vector<int>& target) {
    vector<int> merged(3, 0);
    for (auto& t : triplets)
        if (t[0] <= target[0] && t[1] <= target[1] && t[2] <= target[2])   // never overshoots
            for (int i = 0; i < 3; i++) merged[i] = max(merged[i], t[i]);
    return merged == target;
}

// ---------- Approach 2: Found Flags ⭐ ----------
bool mergeTriplets(const vector<vector<int>>& triplets, const vector<int>& target) {
    bool found[3] = {false, false, false};
    for (auto& t : triplets) {
        if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2]) continue;   // unusable
        for (int i = 0; i < 3; i++)
            if (t[i] == target[i]) found[i] = true;
    }
    return found[0] && found[1] && found[2];
}

// ---------- Driver ----------
int main() {
    vector<pair<vector<vector<int>>, vector<int>>> tests = {
        {{{2, 5, 3}, {1, 8, 4}, {1, 7, 5}}, {2, 7, 5}},
        {{{3, 4, 5}, {4, 5, 6}}, {3, 2, 5}},
        {{{2, 5, 3}, {2, 3, 4}, {1, 2, 5}, {5, 2, 3}}, {5, 5, 5}},
        {{{1, 1, 1}}, {1, 1, 1}},
        {{{2, 1, 1}, {1, 2, 1}}, {2, 2, 2}},
    };
    cout << boolalpha;
    for (auto& [triplets, target] : tests) {
        cout << "merge: " << mergeTripletsMerge(triplets, target) << "\n";
        cout << "flags: " << mergeTriplets(triplets, target) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector == vector compares sizes and elements.
 * - A plain array `bool found[3] = {...}` is enough for fixed-size flags.
 * - `continue` skips a triplet that would push any coordinate past target.
 */
