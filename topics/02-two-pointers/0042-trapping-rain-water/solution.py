"""
0042. Trapping Rain Water  |  Hard  |  Two Pointers
Link: https://leetcode.com/problems/trapping-rain-water/

Problem: Given bar heights (width 1), return the total water trapped.

Examples:
  [0,1,0,2,1,0,1,3,2,1,2,1]  -> 6
  [4,2,0,3,2,5]              -> 9
  [3,0,3]                    -> 3
  [1,2,3]                    -> 0

Approaches:
  1. Brute force                O(n^2) time, O(1) space
  2. Prefix/suffix max arrays   O(n) time, O(n) space
  3. Monotonic stack            O(n) time, O(n) space
  4. Two pointers  ⭐            O(n) time, O(1) space   <- go-to
"""

from itertools import accumulate


# ---------- Approach 1: Brute Force ----------
def trap_brute(h: list[int]) -> int:
    return sum(min(max(h[: i + 1]), max(h[i:])) - h[i] for i in range(len(h)))


# ---------- Approach 2: Prefix/Suffix Max Arrays ----------
def trap_arrays(h: list[int]) -> int:
    L = list(accumulate(h, max))  # running max, includes h[i]
    R = list(accumulate(reversed(h), max))[::-1]
    return sum(min(l, r) - x for l, r, x in zip(L, R, h))


# ---------- Approach 3: Monotonic Stack ----------
def trap_stack(h: list[int]) -> int:
    st: list[int] = []  # indices with decreasing heights
    total = 0
    for i, x in enumerate(h):
        while st and x > h[st[-1]]:
            bottom = st.pop()
            if not st:  # no left wall
                break
            left = st[-1]
            total += (i - left - 1) * (min(h[left], x) - h[bottom])  # fill one horizontal layer
        st.append(i)
    return total


# ---------- Approach 4: Two Pointers ⭐ ----------
def trap(h: list[int]) -> int:
    l, r = 0, len(h) - 1
    left_max = right_max = total = 0
    while l < r:
        if h[l] < h[r]:  # right side has a wall >= h[l]: left is the bottleneck
            left_max = max(left_max, h[l])
            total += left_max - h[l]
            l += 1
        else:
            right_max = max(right_max, h[r])
            total += right_max - h[r]
            r -= 1
    return total


# ---------- Driver ----------
if __name__ == "__main__":
    for h in [[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1], [4, 2, 0, 3, 2, 5], [3, 0, 3], [1, 2, 3]]:
        print("brute   :", trap_brute(h))
        print("arrays  :", trap_arrays(h))
        print("stack   :", trap_stack(h))
        print("pointers:", trap(h))
        print("---")

"""
Syntax notes (Python):
- itertools.accumulate(seq, max) yields running maxima.
- list(...)[::-1] reverses; reversed() is a lazy iterator.
- a = b = c = 0 chains initialization of immutable ints.
"""
