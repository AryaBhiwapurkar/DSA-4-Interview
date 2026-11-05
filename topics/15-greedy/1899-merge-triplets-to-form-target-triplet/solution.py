"""
1899. Merge Triplets to Form Target Triplet  |  Medium  |  Greedy
Link: https://leetcode.com/problems/merge-triplets-to-form-target-triplet/

Problem: Merging two triplets takes the element-wise max. Can repeated merges
         make some triplet equal to target?

Examples:
  [[2,5,3],[1,8,4],[1,7,5]], [2,7,5]           -> true
  [[3,4,5],[4,5,6]], [3,2,5]                   -> false
  [[2,5,3],[2,3,4],[1,2,5],[5,2,3]], [5,5,5]   -> true
  [[1,1,1]], [1,1,1]                           -> true
  [[2,1,1],[1,2,1]], [2,2,2]                   -> false

Approaches:
  1. Merge every usable triplet, compare   O(n) time, O(1) space
  2. One pass, three "found" flags  ⭐      O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Merge Usable Triplets ----------
def merge_triplets_merge(triplets: list[list[int]], target: list[int]) -> bool:
    merged = [0, 0, 0]
    for t in triplets:
        if all(t[i] <= target[i] for i in range(3)):  # never overshoots target
            merged = [max(merged[i], t[i]) for i in range(3)]
    return merged == target


# ---------- Approach 2: Found Flags ⭐ ----------
def merge_triplets(triplets: list[list[int]], target: list[int]) -> bool:
    found = [False] * 3
    for t in triplets:
        if any(t[i] > target[i] for i in range(3)):  # would overshoot: unusable
            continue
        for i in range(3):
            if t[i] == target[i]:
                found[i] = True
    return all(found)


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ([[2, 5, 3], [1, 8, 4], [1, 7, 5]], [2, 7, 5]),
        ([[3, 4, 5], [4, 5, 6]], [3, 2, 5]),
        ([[2, 5, 3], [2, 3, 4], [1, 2, 5], [5, 2, 3]], [5, 5, 5]),
        ([[1, 1, 1]], [1, 1, 1]),
        ([[2, 1, 1], [1, 2, 1]], [2, 2, 2]),
    ]
    for triplets, target in tests:
        print("merge:", str(merge_triplets_merge(triplets, target)).lower())
        print("flags:", str(merge_triplets(triplets, target)).lower())
        print("---")

"""
Syntax notes (Python):
- all() / any() over a generator express "every coordinate" / "some coordinate".
- List equality (merged == target) compares element by element.
- Starting merged at [0,0,0] is safe because values are >= 1.
"""
