"""
0219. Contains Duplicate II  |  Easy  |  Sliding Window
Link: https://leetcode.com/problems/contains-duplicate-ii/

Problem: Return true if two equal values sit at most k indices apart.

Examples:
  [1,2,3,1], k=3        -> True
  [1,0,1,1], k=1        -> True
  [1,2,3,1,2,3], k=2    -> False
  [1,1], k=0            -> False

Approaches:
  1. Brute force          O(n*k) time, O(1) space
  2. Last-seen hashmap    O(n) time, O(n) space
  3. Window set  ⭐        O(n) time, O(min(n,k)) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def contains_nearby_duplicate_brute(nums: list[int], k: int) -> bool:
    n = len(nums)
    return any(nums[i] == nums[j] for i in range(n) for j in range(i + 1, min(n, i + k + 1)))


# ---------- Approach 2: Last-Seen Hashmap ----------
def contains_nearby_duplicate_map(nums: list[int], k: int) -> bool:
    last: dict[int, int] = {}  # value -> most recent index
    for i, x in enumerate(nums):
        if x in last and i - last[x] <= k:
            return True
        last[x] = i
    return False


# ---------- Approach 3: Window Set ⭐ ----------
def contains_nearby_duplicate(nums: list[int], k: int) -> bool:
    window: set[int] = set()  # values at indices [i-k, i-1]
    for i, x in enumerate(nums):
        if x in window:
            return True
        window.add(x)
        if len(window) > k:
            window.remove(nums[i - k])  # drop the value that leaves the window
    return False


# ---------- Driver ----------
if __name__ == "__main__":
    for nums, k in [([1, 2, 3, 1], 3), ([1, 0, 1, 1], 1), ([1, 2, 3, 1, 2, 3], 2), ([1, 1], 0)]:
        print("brute :", contains_nearby_duplicate_brute(nums, k))
        print("map   :", contains_nearby_duplicate_map(nums, k))
        print("window:", contains_nearby_duplicate(nums, k))
        print("---")

"""
Syntax notes (Python):
- set.remove(x) raises KeyError if missing; set.discard(x) doesn't.
- range(i + 1, min(n, i + k + 1)) caps the inner loop at k steps.
- any(generator) short-circuits on the first True.
"""
