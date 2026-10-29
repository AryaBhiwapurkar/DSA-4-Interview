"""
0088. Merge Sorted Array  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/merge-sorted-array/

Problem: nums1 holds m sorted values plus n free slots; nums2 holds n
         sorted values. Merge nums2 into nums1 in place, sorted.

Examples:
  [1,2,3,0,0,0], m=3, [2,5,6], n=3   -> [1,2,2,3,5,6]
  [1], m=1, [], n=0                  -> [1]
  [0], m=0, [1], n=1                 -> [1]
  [4,5,0,0], m=2, [1,2], n=2         -> [1,2,4,5]

Approaches:
  1. Copy + sort              O((m+n) log(m+n)) time, O(1) extra
  2. Forward merge with copy  O(m+n) time, O(m) space
  3. Backward merge  ⭐        O(m+n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Copy + Sort ----------
def merge_sort(nums1: list[int], m: int, nums2: list[int], n: int) -> None:
    nums1[m:] = nums2
    nums1.sort()


# ---------- Approach 2: Forward Merge With a Copy ----------
def merge_forward(nums1: list[int], m: int, nums2: list[int], n: int) -> None:
    a = nums1[:m]  # save nums1's values before overwriting
    i = j = 0
    for w in range(m + n):
        if j == n or (i < m and a[i] <= nums2[j]):
            nums1[w] = a[i]
            i += 1
        else:
            nums1[w] = nums2[j]
            j += 1


# ---------- Approach 3: Backward Merge ⭐ ----------
def merge(nums1: list[int], m: int, nums2: list[int], n: int) -> None:
    i, j, w = m - 1, n - 1, m + n - 1
    while j >= 0:  # once nums2 is used up, nums1's rest is in place
        if i >= 0 and nums1[i] > nums2[j]:
            nums1[w] = nums1[i]
            i -= 1
        else:
            nums1[w] = nums2[j]
            j -= 1
        w -= 1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 3, 0, 0, 0], 3, [2, 5, 6], 3), ([1], 1, [], 0), ([0], 0, [1], 1), ([4, 5, 0, 0], 2, [1, 2], 2)]
    for nums1, m, nums2, n in tests:
        a, b, c = nums1[:], nums1[:], nums1[:]
        merge_sort(a, m, nums2, n)
        merge_forward(b, m, nums2, n)
        merge(c, m, nums2, n)
        print("sort    :", a)
        print("forward :", b)
        print("backward:", c)
        print("---")

"""
Syntax notes (Python):
- nums1[m:] = nums2 replaces the tail slice in place.
- i = j = 0 initializes both names to 0 (fine for immutable ints).
- list.sort() sorts in place; sorted() returns a new list.
"""
