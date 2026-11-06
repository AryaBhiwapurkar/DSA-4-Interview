"""
0066. Plus One  |  Easy  |  Math & Geometry
Link: https://leetcode.com/problems/plus-one/

Problem: A big number is given as its digits (most significant first). Add one.

Examples:
  [1,2,3]    -> [1,2,4]
  [4,3,2,1]  -> [4,3,2,2]
  [9]        -> [1,0]
  [9,9,9]    -> [1,0,0,0]
  [1,9,9]    -> [2,0,0]
  [0]        -> [1]

Approaches:
  1. General carry loop           O(n) time, O(1) extra
  2. Early-exit carry  ⭐         O(n) time, O(1) extra   <- go-to
  (Parsing into an int works in Python but overflows in C++; not used.)
"""


# ---------- Approach 1: General Carry Loop ----------
def plus_one_carry(digits: list[int]) -> list[int]:
    digits = digits[:]
    carry = 1  # the "+1"
    for i in range(len(digits) - 1, -1, -1):
        carry, digits[i] = divmod(digits[i] + carry, 10)
    return [carry] + digits if carry else digits


# ---------- Approach 2: Early-exit Carry ⭐ ----------
def plus_one(digits: list[int]) -> list[int]:
    digits = digits[:]
    for i in range(len(digits) - 1, -1, -1):
        if digits[i] < 9:
            digits[i] += 1
            return digits  # carry absorbed
        digits[i] = 0  # 9 + 1 = 10: write 0, carry on
    return [1] + digits  # all nines


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 2, 3], [4, 3, 2, 1], [9], [9, 9, 9], [1, 9, 9], [0]]:
        print("carry:", plus_one_carry(t))
        print("early:", plus_one(t))
        print("---")

"""
Syntax notes (Python):
- range(n - 1, -1, -1) walks indices right to left.
- carry, d = divmod(s, 10) gives quotient and remainder in one call.
- digits[:] copies the list so the caller's input isn't mutated.
"""
