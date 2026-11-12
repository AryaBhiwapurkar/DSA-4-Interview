"""
0904. Fruit Into Baskets  |  Medium  |  Sliding Window
Link: https://leetcode.com/problems/fruit-into-baskets/

Problem: Longest contiguous run of trees containing at most 2 fruit types.

Examples:
  [1,2,1]                    -> 3
  [0,1,2,2]                  -> 3
  [1,2,3,2,2]                -> 4
  [3,3,3,1,2,1,1,2,3,3,4]    -> 5
  [1,2,3,1,2,3]              -> 2

Approaches:
  1. Every start, extend               O(n^2) time
  2. Shrinking window + map  ⭐        O(n) time, O(1) space   <- go-to
"""

from collections import Counter


# ---------- Approach 1: Every Start ----------
def total_fruit_brute(fruits: list[int]) -> int:
    best = 0
    for l in range(len(fruits)):
        types: set[int] = set()
        for r in range(l, len(fruits)):
            types.add(fruits[r])
            if len(types) > 2:
                break
            best = max(best, r - l + 1)
    return best


# ---------- Approach 2: Shrinking Window ⭐ ----------
def total_fruit(fruits: list[int]) -> int:
    cnt: Counter[int] = Counter()  # at most 3 keys at any time
    l = best = 0
    for r, f in enumerate(fruits):
        cnt[f] += 1
        while len(cnt) > 2:
            cnt[fruits[l]] -= 1
            if cnt[fruits[l]] == 0:
                del cnt[fruits[l]]
            l += 1
        best = max(best, r - l + 1)
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 2, 1], [0, 1, 2, 2], [1, 2, 3, 2, 2], [3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4], [1, 2, 3, 1, 2, 3]]:
        print("brute :", total_fruit_brute(t))
        print("window:", total_fruit(t))
        print("---")

"""
Syntax notes (Python):
- A Counter keeps zero-count keys; delete them so len() means "distinct types".
- Counter[int] annotates the key type.
- Same template as 0340 with k = 2.
"""
