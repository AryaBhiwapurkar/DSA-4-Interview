"""
1283. Find the Smallest Divisor Given a Threshold  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/

Problem: Return the smallest positive d such that the sum of ceil(x / d)
         over nums is <= threshold.

Examples:
  [1,2,5,9],             threshold = 6         -> 5
  [44,22,33,11,1],       threshold = 5         -> 44
  [21212,10101,12121],   threshold = 1000000   -> 1
  [2,3,5,7,11],          threshold = 11        -> 3
  [19],                  threshold = 5         -> 4

Approaches:
  1. Try every divisor                O(n max) time, O(1) space
  2. Binary search on the divisor ⭐  O(n log max) time, O(1) space   <- go-to
"""


def cost_for(nums: list[int], d: int) -> int:
    return sum(-(-x // d) for x in nums)  # integer ceil


# ---------- Approach 1: Try Every Divisor ----------
def smallest_divisor_linear(nums: list[int], threshold: int) -> int:
    d = 1
    while cost_for(nums, d) > threshold:
        d += 1
    return d


# ---------- Approach 2: Binary Search on the Divisor ⭐ ----------
def smallest_divisor(nums: list[int], threshold: int) -> int:
    lo, hi = 1, max(nums)  # d = max gives n <= threshold
    while lo < hi:
        mid = (lo + hi) // 2
        if cost_for(nums, mid) <= threshold:
            hi = mid
        else:
            lo = mid + 1
    return lo


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 5, 9], 6), ([44, 22, 33, 11, 1], 5), ([21212, 10101, 12121], 1000000),
             ([2, 3, 5, 7, 11], 11), ([19], 5)]
    for nums, t in tests:
        print("linear:", smallest_divisor_linear(nums, t))
        print("binary:", smallest_divisor(nums, t))
        print("---")

"""
Syntax notes (Python):
- -(-x // d) is ceil division: floor division rounds toward -inf.
- (x + d - 1) // d also works for positive x and d.
- sum(generator) avoids building an intermediate list.
"""
