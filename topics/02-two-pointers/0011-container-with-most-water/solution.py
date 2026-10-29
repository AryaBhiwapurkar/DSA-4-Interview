"""
0011. Container With Most Water  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/container-with-most-water/

Problem: Choose two lines that, with the x-axis, hold the most water;
         area = min(h[l], h[r]) * (r - l). Return the max area.

Examples:
  [1,8,6,2,5,4,8,3,7]  -> 49
  [1,1]                -> 1
  [4,3,2,1,4]          -> 16
  [0,0]                -> 0

Approaches:
  1. Brute force        O(n^2) time, O(1) space
  2. Two pointers  ⭐    O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def max_area_brute(h: list[int]) -> int:
    n = len(h)
    return max(min(h[i], h[j]) * (j - i) for i in range(n) for j in range(i + 1, n))


# ---------- Approach 2: Two Pointers ⭐ ----------
def max_area(h: list[int]) -> int:
    l, r, best = 0, len(h) - 1, 0
    while l < r:
        best = max(best, min(h[l], h[r]) * (r - l))
        if h[l] < h[r]:  # shorter wall is the bottleneck: only moving it can help
            l += 1
        else:
            r -= 1
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for h in [[1, 8, 6, 2, 5, 4, 8, 3, 7], [1, 1], [4, 3, 2, 1, 4], [0, 0]]:
        print("brute   :", max_area_brute(h))
        print("pointers:", max_area(h))
        print("---")

"""
Syntax notes (Python):
- A nested generator `for i in ... for j in ...` flattens a double loop inside max().
- max(generator) raises on empty input; n >= 2 here.
"""
