"""
0202. Happy Number  |  Easy  |  Math & Geometry
Link: https://leetcode.com/problems/happy-number/

Problem: Repeatedly replace n by the sum of the squares of its digits.
         Happy if this reaches 1; otherwise it cycles forever.

Examples:
  19          -> True   (19 -> 82 -> 68 -> 100 -> 1)
  2           -> False  (falls into the 4 -> 16 -> ... -> 4 cycle)
  1           -> True
  7           -> True
  2147483647  -> False

Approaches:
  1. Hash set of seen values  ⭐  O(log n) per step, O(k) space   <- go-to
  2. Floyd slow/fast pointers      O(log n) per step, O(1) space
"""


def next_num(n: int) -> int:
    s = 0
    while n:
        n, d = divmod(n, 10)
        s += d * d
    return s


# ---------- Approach 1: Hash Set ⭐ ----------
def is_happy(n: int) -> bool:
    seen: set[int] = set()
    while n != 1 and n not in seen:  # stop at 1 or a repeat
        seen.add(n)
        n = next_num(n)
    return n == 1


# ---------- Approach 2: Floyd ----------
def is_happy_floyd(n: int) -> bool:
    slow, fast = n, next_num(n)
    while fast != 1 and slow != fast:  # 1 is a fixed point, so fast stays there
        slow = next_num(slow)
        fast = next_num(next_num(fast))
    return fast == 1


# ---------- Driver ----------
if __name__ == "__main__":
    for n in [19, 2, 1, 7, 2147483647]:
        print("set  :", is_happy(n))
        print("floyd:", is_happy_floyd(n))
        print("---")

"""
Syntax notes (Python):
- n, d = divmod(n, 10) pops the last digit.
- sum(int(c) ** 2 for c in str(n)) is a shorter (slower) digit-square sum.
- Annotate an empty set as seen: set[int] = set().
"""
