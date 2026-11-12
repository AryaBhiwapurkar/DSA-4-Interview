"""
0496. Next Greater Element I  |  Easy  |  Stack
Link: https://leetcode.com/problems/next-greater-element-i/

Problem: For each value of nums1 (a subset of nums2, all distinct), return the first
         larger value to its right in nums2, or -1.

Examples:
  nums1 = [4,1,2], nums2 = [1,3,4,2]   -> [-1,3,-1]
  nums1 = [2,4],   nums2 = [1,2,3,4]   -> [3,-1]
  nums1 = [3,2,1], nums2 = [3,2,1]     -> [-1,-1,-1]

Approaches:
  1. Scan right per query            O(n1 * n2) time, O(1) space
  2. Monotonic stack + map  ⭐       O(n1 + n2) time, O(n2) space   <- go-to
"""


# ---------- Approach 1: Scan per Query ----------
def next_greater_element_brute(nums1: list[int], nums2: list[int]) -> list[int]:
    out = []
    for v in nums1:
        i = nums2.index(v)
        out.append(next((x for x in nums2[i + 1:] if x > v), -1))
    return out


# ---------- Approach 2: Monotonic Stack ⭐ ----------
def next_greater_element(nums1: list[int], nums2: list[int]) -> list[int]:
    nxt: dict[int, int] = {}
    st: list[int] = []  # decreasing: values still waiting
    for x in nums2:
        while st and st[-1] < x:
            nxt[st.pop()] = x  # x is the first bigger value
        st.append(x)
    return [nxt.get(v, -1) for v in nums1]


# ---------- Driver ----------
if __name__ == "__main__":
    for a, b in [([4, 1, 2], [1, 3, 4, 2]), ([2, 4], [1, 2, 3, 4]), ([3, 2, 1], [3, 2, 1])]:
        print("brute:", next_greater_element_brute(a, b))
        print("stack:", next_greater_element(a, b))
        print("---")

"""
Syntax notes (Python):
- next(generator, default) returns the first match or the default.
- list.index(v) finds the first position of v (O(n)).
- A list is a stack: append / pop / [-1].
"""
