"""
0503. Next Greater Element II  |  Medium  |  Stack
Link: https://leetcode.com/problems/next-greater-element-ii/

Problem: Circular array: for each element, the first strictly larger value moving
         forward (wrapping once), or -1.

Examples:
  [1,2,1]        -> [2,-1,2]
  [1,2,3,4,3]    -> [2,3,4,-1,4]
  [5,5,5]        -> [-1,-1,-1]
  [3,1,2]        -> [-1,2,3]

Approaches:
  1. Scan forward per element          O(n^2) time, O(1) space
  2. Two-pass monotonic stack  ⭐      O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Scan per Element ----------
def next_greater_elements_brute(nums: list[int]) -> list[int]:
    n = len(nums)
    return [next((nums[(i + d) % n] for d in range(1, n) if nums[(i + d) % n] > nums[i]), -1)
            for i in range(n)]


# ---------- Approach 2: Two-pass Stack ⭐ ----------
def next_greater_elements(nums: list[int]) -> list[int]:
    n = len(nums)
    ans = [-1] * n
    st: list[int] = []  # indices still waiting
    for i in range(2 * n):
        x = nums[i % n]  # second lap simulates the wrap
        while st and nums[st[-1]] < x:
            ans[st.pop()] = x
        if i < n:
            st.append(i)  # push each index once
    return ans


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 2, 1], [1, 2, 3, 4, 3], [5, 5, 5], [3, 1, 2]]:
        print("brute:", next_greater_elements_brute(t))
        print("stack:", next_greater_elements(t))
        print("---")

"""
Syntax notes (Python):
- ans[st.pop()] = x pops an index and writes its answer in one line.
- range(2 * n) with i % n walks the array twice without copying it.
- next(gen, -1) gives the first match or -1.
"""
