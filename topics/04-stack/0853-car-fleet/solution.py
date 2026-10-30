"""
0853. Car Fleet  |  Medium  |  Stack
Link: https://leetcode.com/problems/car-fleet/

Problem: Cars drive to target on one lane and can't pass; a car that
         catches up joins that fleet. Count fleets arriving at target.

Examples:
  target 12,  pos [10,8,0,5,3], speed [2,4,1,1,3]  -> 3
  target 10,  pos [3],          speed [3]          -> 1
  target 100, pos [0,2,4],      speed [4,2,1]      -> 1
  target 10,  pos [0,4,8],      speed [1,1,1]      -> 3

Approaches:
  1. Sort + stack of fleet times     O(n log n) time, O(n) space
  2. Sort + slowest fleet time  ⭐    O(n log n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Sort + Stack of Fleet Times ----------
def car_fleet_stack(target: int, position: list[int], speed: list[int]) -> int:
    st: list[float] = []  # arrival time of each fleet ahead
    for p, s in sorted(zip(position, speed), reverse=True):  # closest to target first
        st.append((target - p) / s)
        if len(st) >= 2 and st[-1] <= st[-2]:  # caught up: merged
            st.pop()
    return len(st)


# ---------- Approach 2: Sort + Slowest Fleet Time ⭐ ----------
def car_fleet(target: int, position: list[int], speed: list[int]) -> int:
    fleets, last = 0, 0.0  # last = arrival time of the fleet directly ahead
    for p, s in sorted(zip(position, speed), reverse=True):
        t = (target - p) / s
        if t > last:  # can't catch it: new, slower fleet
            fleets += 1
            last = t
    return fleets


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        (12, [10, 8, 0, 5, 3], [2, 4, 1, 1, 3]),
        (10, [3], [3]),
        (100, [0, 2, 4], [4, 2, 1]),
        (10, [0, 4, 8], [1, 1, 1]),
    ]
    for target, pos, sp in tests:
        print("stack  :", car_fleet_stack(target, pos, sp))
        print("slowest:", car_fleet(target, pos, sp))
        print("---")

"""
Syntax notes (Python):
- sorted(zip(a, b), reverse=True) pairs two lists and sorts by a descending.
- `/` is always float division in Python 3; `//` is integer (floor).
- st[-2] reads the element just below the top.
"""
