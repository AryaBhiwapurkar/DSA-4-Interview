/*
 * 0253. Meeting Rooms II  |  Medium  |  Intervals
 * Link: https://leetcode.com/problems/meeting-rooms-ii/  (LC Premium)
 *
 * Problem: Minimum number of rooms so that all [start, end) meetings can run.
 *
 * Examples:
 *   [[0,30],[5,10],[15,20]]                          -> 2
 *   [[7,10],[2,4]]                                   -> 1
 *   [[1,5],[5,10]]                                   -> 1   (touching reuses the room)
 *   [[1,10],[2,7],[3,19],[8,12],[10,20],[11,30]]     -> 4
 *   [[5,8]]                                          -> 1
 *
 * Approaches:
 *   1. Sweep line over +1/-1 events          O(n log n) time, O(n) space
 *   2. Sort by start + min-heap of end times  ⭐   O(n log n) time, O(n) space   <- go-to
 *   3. Two sorted arrays (starts, ends)      O(n log n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Sweep Line ----------
int minMeetingRoomsSweep(const vector<vector<int>>& iv) {
    vector<pair<int, int>> events;
    for (auto& m : iv) {
        events.push_back({m[0], 1});
        events.push_back({m[1], -1});
    }
    sort(events.begin(), events.end());           // at equal times, -1 (end) first
    int rooms = 0, best = 0;
    for (auto& [t, d] : events) best = max(best, rooms += d);
    return best;
}

// ---------- Approach 2: Min-heap of Ends ⭐ ----------
int minMeetingRooms(vector<vector<int>> iv) {
    sort(iv.begin(), iv.end());
    priority_queue<int, vector<int>, greater<int>> ends;   // end times of rooms in use
    for (auto& m : iv) {
        if (!ends.empty() && ends.top() <= m[0]) ends.pop();   // earliest room is free again
        ends.push(m[1]);
    }
    return ends.size();
}

// ---------- Approach 3: Two Sorted Arrays ----------
int minMeetingRoomsTwo(const vector<vector<int>>& iv) {
    vector<int> starts, ends;
    for (auto& m : iv) { starts.push_back(m[0]); ends.push_back(m[1]); }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    int rooms = 0, best = 0;
    size_t j = 0;
    for (int s : starts) {
        while (ends[j] <= s) { rooms--; j++; }     // ended meetings free their rooms
        best = max(best, ++rooms);
    }
    return best;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{0, 30}, {5, 10}, {15, 20}}, {{7, 10}, {2, 4}}, {{1, 5}, {5, 10}},
        {{1, 10}, {2, 7}, {3, 19}, {8, 12}, {10, 20}, {11, 30}}, {{5, 8}}
    };
    for (auto& t : tests) {
        cout << "sweep: " << minMeetingRoomsSweep(t) << "\n";
        cout << "heap : " << minMeetingRooms(t) << "\n";
        cout << "two  : " << minMeetingRoomsTwo(t) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - priority_queue<int, vector<int>, greater<int>> is a min-heap.
 * - `rooms += d` is an expression, so max(best, rooms += d) updates and compares.
 * - ends[j] never runs past the end: every start has a larger end still unread.
 */
