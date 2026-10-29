"""
0015. 3Sum  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/3sum/

Problem: Return all unique value-triplets [a,b,c] from different indices
         with a + b + c == 0. Any order.

Examples (printed sorted for stable output):
  [-1,0,1,2,-1,-4]  -> [[-1,-1,2],[-1,0,1]]
  [0,1,1]           -> []
  [0,0,0]           -> [[0,0,0]]
  [0,0,0,0]         -> [[0,0,0]]

Approaches:
  1. Brute force + set        O(n^3) time, O(k) space
  2. Hash set per fixed i     O(n^2) time, O(n) space
  3. Sort + two pointers  ⭐   O(n^2) time, O(1) extra space   <- go-to
"""

from itertools import combinations


# ---------- Approach 1: Brute Force + Set ----------
def three_sum_brute(nums: list[int]) -> list[list[int]]:
    found = {tuple(sorted(t)) for t in combinations(nums, 3) if sum(t) == 0}  # canonical order for dedup
    return [list(t) for t in found]


# ---------- Approach 2: Hash Set per Fixed Element ----------
def three_sum_hash(nums: list[int]) -> list[list[int]]:
    found: set[tuple[int, ...]] = set()
    for i in range(len(nums)):
        seen: set[int] = set()
        for j in range(i + 1, len(nums)):
            need = -nums[i] - nums[j]
            if need in seen:
                found.add(tuple(sorted((nums[i], nums[j], need))))
            seen.add(nums[j])
    return [list(t) for t in found]


# ---------- Approach 3: Sort + Two Pointers ⭐ ----------
def three_sum(nums: list[int]) -> list[list[int]]:
    a = sorted(nums)
    res: list[list[int]] = []
    n = len(a)
    for i in range(n - 2):
        if a[i] > 0:  # smallest is positive: no more zeros possible
            break
        if i > 0 and a[i] == a[i - 1]:  # same first value already handled
            continue
        l, r = i + 1, n - 1
        while l < r:
            s = a[i] + a[l] + a[r]
            if s < 0:
                l += 1
            elif s > 0:
                r -= 1
            else:
                res.append([a[i], a[l], a[r]])
                l, r = l + 1, r - 1
                while l < r and a[l] == a[l - 1]:  # skip duplicate seconds
                    l += 1
                while l < r and a[r] == a[r + 1]:  # skip duplicate thirds
                    r -= 1
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    for nums in [[-1, 0, 1, 2, -1, -4], [0, 1, 1], [0, 0, 0], [0, 0, 0, 0]]:
        print("brute   :", sorted(three_sum_brute(nums)))  # sorted: order is unspecified
        print("hash    :", sorted(three_sum_hash(nums)))
        print("pointers:", sorted(three_sum(nums)))
        print("---")

"""
Syntax notes (Python):
- itertools.combinations(seq, 3) yields every 3-element index combination (as values).
- Tuples are hashable; lists aren't, so dedupe with a set of tuples.
- l, r = l + 1, r - 1 moves both pointers at once.
"""
