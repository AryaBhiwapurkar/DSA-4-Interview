"""
0075. Sort Colors  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/sort-colors/

Problem: Sort an array of 0s, 1s and 2s in place, without a library sort.

Examples:
  [2,0,2,1,1,0]  -> [0,0,1,1,2,2]
  [2,0,1]        -> [0,1,2]
  [1]            -> [1]
  [2,2,0,0]      -> [0,0,2,2]

Approaches:
  1. Counting sort                  O(n) time, O(1) space, two passes
  2. Dutch national flag  ⭐        O(n) time, O(1) space, one pass   <- go-to
"""


# ---------- Approach 1: Counting Sort ----------
def sort_colors_count(nums: list[int]) -> None:
    cnt = [nums.count(c) for c in range(3)]
    nums[:] = [0] * cnt[0] + [1] * cnt[1] + [2] * cnt[2]


# ---------- Approach 2: Dutch National Flag ⭐ ----------
def sort_colors(nums: list[int]) -> None:
    lo, mid, hi = 0, 0, len(nums) - 1  # [0,lo)=0, [lo,mid)=1, (hi,end]=2
    while mid <= hi:
        if nums[mid] == 0:
            nums[lo], nums[mid] = nums[mid], nums[lo]
            lo += 1
            mid += 1
        elif nums[mid] == 1:
            mid += 1
        else:
            nums[mid], nums[hi] = nums[hi], nums[mid]
            hi -= 1  # mid stays: swapped-in value unseen


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[2, 0, 2, 1, 1, 0], [2, 0, 1], [1], [2, 2, 0, 0]]:
        a, b = t[:], t[:]
        sort_colors_count(a)
        sort_colors(b)
        print("count:", a)
        print("flag :", b)
        print("---")

"""
Syntax notes (Python):
- list.count(v) counts occurrences (O(n) each; three calls is still O(n)).
- [0] * k + [1] * m concatenates repeated lists.
- nums[:] = ... overwrites the caller's list in place.
"""
