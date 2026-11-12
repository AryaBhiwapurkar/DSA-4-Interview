"""
0907. Sum of Subarray Minimums  |  Medium  |  Stack
Link: https://leetcode.com/problems/sum-of-subarray-minimums/

Problem: Sum of min(sub) over all contiguous subarrays, modulo 1e9+7.

Examples:
  [3,1,2,4]         -> 17
  [11,81,94,43,3]   -> 444
  [2,2,2]           -> 12
  [5]               -> 5

Approaches:
  1. All subarrays, running min                O(n^2) time, O(1) space
  2. Contribution via monotonic stacks  ⭐     O(n) time, O(n) space   <- go-to
"""

MOD = 10**9 + 7


# ---------- Approach 1: All Subarrays ----------
def sum_subarray_mins_brute(arr: list[int]) -> int:
    total = 0
    for i in range(len(arr)):
        mn = arr[i]
        for j in range(i, len(arr)):
            mn = min(mn, arr[j])
            total += mn
    return total % MOD


# ---------- Approach 2: Contribution ⭐ ----------
def sum_subarray_mins(arr: list[int]) -> int:
    n = len(arr)
    prev_less, next_less_eq = [-1] * n, [n] * n
    st: list[int] = []
    for i in range(n):  # previous strictly smaller
        while st and arr[st[-1]] >= arr[i]:
            st.pop()
        prev_less[i] = st[-1] if st else -1
        st.append(i)
    st = []
    for i in range(n - 1, -1, -1):  # next smaller-or-equal (tie-break)
        while st and arr[st[-1]] > arr[i]:
            st.pop()
        next_less_eq[i] = st[-1] if st else n
        st.append(i)
    return sum(arr[i] * (i - prev_less[i]) * (next_less_eq[i] - i) for i in range(n)) % MOD


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[3, 1, 2, 4], [11, 81, 94, 43, 3], [2, 2, 2], [5]]:
        print("brute       :", sum_subarray_mins_brute(t))
        print("contribution:", sum_subarray_mins(t))
        print("---")

"""
Syntax notes (Python):
- 10**9 + 7 is the usual modulus; Python ints can sum first and reduce once.
- st[-1] if st else -1 handles the empty-stack boundary inline.
- [n] * n sets "no next smaller" to index n by default.
"""
