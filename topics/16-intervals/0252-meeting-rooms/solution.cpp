/*
 * 0252. Meeting Rooms  |  Easy  |  Intervals
 * Link: https://leetcode.com/problems/meeting-rooms/  (LC Premium)
 *
 * Problem: Given meeting [start, end) times, can one person attend all of them?
 *
 * Examples:
 *   [[0,30],[5,10],[15,20]]   -> false
 *   [[7,10],[2,4]]            -> true
 *   [[1,2],[2,3]]             -> true   (end == next start is fine)
 *   []                        -> true
 *   [[5,8],[6,8]]             -> false
 *
 * Approaches:
 *   1. Check every pair             O(n^2) time, O(1) space
 *   2. Sort by start, compare neighbours  ⭐   O(n log n) time, O(1) extra   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Every Pair ----------
bool canAttendMeetingsBrute(const vector<vector<int>>& iv) {
    for (size_t i = 0; i < iv.size(); i++)
        for (size_t j = i + 1; j < iv.size(); j++)
            if (iv[i][0] < iv[j][1] && iv[j][0] < iv[i][1]) return false;   // strict: touching ok
    return true;
}

// ---------- Approach 2: Sort + Neighbours ⭐ ----------
bool canAttendMeetings(vector<vector<int>> iv) {
    sort(iv.begin(), iv.end());
    for (size_t i = 1; i < iv.size(); i++)
        if (iv[i][0] < iv[i - 1][1]) return false;   // starts before the previous ends
    return true;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {{{0, 30}, {5, 10}, {15, 20}}, {{7, 10}, {2, 4}}, {{1, 2}, {2, 3}}, {}, {{5, 8}, {6, 8}}};
    cout << boolalpha;
    for (auto& t : tests) {
        cout << "brute: " << canAttendMeetingsBrute(t) << "\n";
        cout << "sort : " << canAttendMeetings(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - Starting the loop at i = 1 with size_t is safe even for an empty vector.
 * - Pass by value to sort a copy and leave the caller's data alone.
 * - Overlap test for half-open intervals: a.start < b.end && b.start < a.end.
 */
