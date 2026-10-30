"""
0287. Find the Duplicate Number  |  Medium  |  Linked List
Link: https://leetcode.com/problems/find-the-duplicate-number/

Problem: n + 1 ints in [1, n]; exactly one value repeats. Find it
         without modifying the array, in O(1) extra space.

Examples:
  [1,3,4,2,2]  -> 2
  [3,1,3,4,2]  -> 3
  [3,3,3,3,3]  -> 3
  [1,1]        -> 1
  [2,2,2]      -> 2

Approaches:
  1. Hash set                     O(n) time, O(n) space
  2. Binary search on value       O(n log n) time, O(1) space
  3. Floyd cycle detection  ⭐     O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Hash Set ----------
def find_duplicate_set(nums: list[int]) -> int:
    seen: set[int] = set()
    for x in nums:
        if x in seen:
            return x
        seen.add(x)
    return -1


# ---------- Approach 2: Binary Search on Value ----------
def find_duplicate_binary(nums: list[int]) -> int:
    lo, hi = 1, len(nums) - 1  # values live in [1, n]
    while lo < hi:
        mid = (lo + hi) // 2
        if sum(x <= mid for x in nums) > mid:  # pigeonhole: too many values <= mid
            hi = mid
        else:
            lo = mid + 1
    return lo


# ---------- Approach 3: Floyd Cycle Detection ⭐ ----------
def find_duplicate(nums: list[int]) -> int:
    slow = fast = 0  # index 0 is the head: no value points to it
    while True:  # phase 1: meet inside the cycle
        slow = nums[slow]
        fast = nums[nums[fast]]
        if slow == fast:
            break
    slow = 0
    while slow != fast:  # phase 2: meet at the cycle entry
        slow, fast = nums[slow], nums[fast]
    return slow  # entry has two incoming edges = duplicate


# ---------- Driver ----------
if __name__ == "__main__":
    for nums in [[1, 3, 4, 2, 2], [3, 1, 3, 4, 2], [3, 3, 3, 3, 3], [1, 1], [2, 2, 2]]:
        print("hashSet:", find_duplicate_set(nums))
        print("binary :", find_duplicate_binary(nums))
        print("floyd  :", find_duplicate(nums))
        print("---")

"""
Syntax notes (Python):
- Python has no do-while: use `while True:` with a break at the bottom.
- sum(x <= mid for x in nums) counts True values (True == 1).
- Here a "node" is an index and its "next" is nums[index].
"""
