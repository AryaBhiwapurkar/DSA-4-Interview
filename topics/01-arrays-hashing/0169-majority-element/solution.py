"""
0169. Majority Element  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/majority-element/

Problem: Return the element that appears more than n/2 times.
         It is guaranteed to exist.

Examples:
  [3,2,3]           -> 3
  [2,2,1,1,1,2,2]   -> 2
  [1,2,2]           -> 2

Approaches:
  1. Hashmap count      O(n) time, O(n) space
  2. Sort, take middle  O(n log n) time, O(n) space (sorted copy)
  3. Boyer-Moore  ⭐     O(n) time, O(1) space   <- go-to
"""

from collections import Counter


# ---------- Approach 1: Hashmap Count ----------
def majority_element_hash(nums: list[int]) -> int:
    return Counter(nums).most_common(1)[0][0]


# ---------- Approach 2: Sort, Take Middle ----------
def majority_element_sorted(nums: list[int]) -> int:
    return sorted(nums)[len(nums) // 2]  # majority spans the middle index


# ---------- Approach 3: Boyer-Moore Voting ⭐ ----------
def majority_element(nums: list[int]) -> int:
    candidate, count = 0, 0
    for x in nums:
        if count == 0:  # previous votes fully cancelled
            candidate = x
        count += 1 if x == candidate else -1
    return candidate


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[3, 2, 3], [2, 2, 1, 1, 1, 2, 2], [1, 2, 2]]
    for nums in tests:
        print("hash  :", majority_element_hash(nums))
        print("sorted:", majority_element_sorted(nums))
        print("voting:", majority_element(nums))
        print("---")

"""
Syntax notes (Python):
- Counter(x).most_common(k) returns the k (value, count) pairs with highest counts.
- `a if cond else b` is Python's ternary.
- // is integer (floor) division.
"""
