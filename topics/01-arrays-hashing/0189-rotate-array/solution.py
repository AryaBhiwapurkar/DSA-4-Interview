"""
0189. Rotate Array  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/rotate-array/

Problem: Rotate the array to the right by k steps, in place.

Examples:
  [1,2,3,4,5,6,7], k=3   -> [5,6,7,1,2,3,4]
  [-1,-100,3,99], k=2    -> [3,99,-1,-100]
  [1,2], k=3             -> [2,1]
  [1,2,3], k=0           -> [1,2,3]

Approaches:
  1. Rotate by one, k times   O(n*k) time, O(1) space
  2. Extra array              O(n) time, O(n) space
  3. Three reversals  ⭐       O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Rotate by One, k Times ----------
def rotate_brute(nums: list[int], k: int) -> None:
    for _ in range(k % len(nums)):
        nums.insert(0, nums.pop())  # insert(0, x) is O(n)


# ---------- Approach 2: Extra Array ----------
def rotate_extra(nums: list[int], k: int) -> None:
    n = len(nums)
    out = [0] * n
    for i, x in enumerate(nums):
        out[(i + k) % n] = x
    nums[:] = out  # slice-assign mutates the caller's list; `nums = out` would not


# ---------- Approach 3: Three Reversals ⭐ ----------
def rotate(nums: list[int], k: int) -> None:
    def rev(lo: int, hi: int) -> None:
        while lo < hi:
            nums[lo], nums[hi] = nums[hi], nums[lo]
            lo, hi = lo + 1, hi - 1

    n = len(nums)
    k %= n  # k may exceed n
    rev(0, n - 1)
    rev(0, k - 1)  # first k: the old tail, fixed
    rev(k, n - 1)  # rest: the old head, fixed


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 3, 4, 5, 6, 7], 3), ([-1, -100, 3, 99], 2), ([1, 2], 3), ([1, 2, 3], 0)]
    for nums, k in tests:
        a, b, c = nums[:], nums[:], nums[:]  # each approach mutates its own copy
        rotate_brute(a, k)
        rotate_extra(b, k)
        rotate(c, k)
        print("brute  :", a)
        print("extra  :", b)
        print("reverse:", c)
        print("---")

"""
Syntax notes (Python):
- nums[:] = other replaces contents in place; nums = other only rebinds the name.
- Tuple swap: a[i], a[j] = a[j], a[i].
- One-liner (not O(1) space): nums[:] = nums[-k:] + nums[:-k] (after k %= n, and k > 0).
- A nested def can modify the enclosing list (mutation, not rebinding).
"""
