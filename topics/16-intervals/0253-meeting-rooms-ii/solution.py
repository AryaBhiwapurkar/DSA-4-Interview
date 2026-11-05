"""
0253. Meeting Rooms II  |  Medium  |  Intervals
Link: https://leetcode.com/problems/meeting-rooms-ii/  (LC Premium)

Problem: Minimum number of rooms so that all [start, end) meetings can run.

Examples:
  [[0,30],[5,10],[15,20]]                          -> 2
  [[7,10],[2,4]]                                   -> 1
  [[1,5],[5,10]]                                   -> 1   (touching reuses the room)
  [[1,10],[2,7],[3,19],[8,12],[10,20],[11,30]]     -> 4
  [[5,8]]                                          -> 1

Approaches:
  1. Sweep line over +1/-1 events          O(n log n) time, O(n) space
  2. Sort by start + min-heap of end times  ⭐   O(n log n) time, O(n) space   <- go-to
  3. Two sorted arrays (starts, ends)      O(n log n) time, O(n) space
"""

import heapq


# ---------- Approach 1: Sweep Line ----------
def min_meeting_rooms_sweep(intervals: list[list[int]]) -> int:
    events = []
    for s, e in intervals:
        events.append((s, 1))
        events.append((e, -1))
    events.sort()  # at equal times, -1 (end) sorts before +1 (start)
    rooms = best = 0
    for _, d in events:
        rooms += d
        best = max(best, rooms)
    return best


# ---------- Approach 2: Min-heap of Ends ⭐ ----------
def min_meeting_rooms(intervals: list[list[int]]) -> int:
    ends: list[int] = []  # end times of rooms in use
    for s, e in sorted(intervals):
        if ends and ends[0] <= s:  # earliest-ending room is free again
            heapq.heapreplace(ends, e)
        else:
            heapq.heappush(ends, e)
    return len(ends)


# ---------- Approach 3: Two Sorted Arrays ----------
def min_meeting_rooms_two(intervals: list[list[int]]) -> int:
    starts = sorted(s for s, _ in intervals)
    ends = sorted(e for _, e in intervals)
    rooms = best = j = 0
    for s in starts:
        while ends[j] <= s:  # meetings that ended by now free their rooms
            rooms -= 1
            j += 1
        rooms += 1
        best = max(best, rooms)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [[0, 30], [5, 10], [15, 20]],
        [[7, 10], [2, 4]],
        [[1, 5], [5, 10]],
        [[1, 10], [2, 7], [3, 19], [8, 12], [10, 20], [11, 30]],
        [[5, 8]],
    ]
    for t in tests:
        print("sweep:", min_meeting_rooms_sweep(t))
        print("heap :", min_meeting_rooms(t))
        print("two  :", min_meeting_rooms_two(t))
        print("---")

"""
Syntax notes (Python):
- heapq is a min-heap on a plain list; ends[0] is the smallest end time.
- heapreplace(h, x) pops the min and pushes x in one O(log n) step.
- Tuples sort by first item, then second: (t, -1) comes before (t, 1).
"""
