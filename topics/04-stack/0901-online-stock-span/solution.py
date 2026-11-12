"""
0901. Online Stock Span  |  Medium  |  Stack
Link: https://leetcode.com/problems/online-stock-span/

Problem: next(price) returns how many consecutive days, ending today, had price <= today's.

Examples:
  next: 100,80,60,70,60,75,85  -> 1,1,1,2,1,4,6
  next: 10,20,30               -> 1,2,3
  next: 5,5,5                  -> 1,2,3

Approaches:
  1. Scan back each day                 O(n) per call
  2. Stack of (price, span)  ⭐         O(1) amortised per call   <- go-to
"""


# ---------- Approach 1: Scan Back ----------
class StockSpannerBrute:
    def __init__(self) -> None:
        self.prices: list[int] = []

    def next(self, price: int) -> int:
        self.prices.append(price)
        span = 0
        for p in reversed(self.prices):
            if p > price:
                break
            span += 1
        return span


# ---------- Approach 2: Monotonic Stack ⭐ ----------
class StockSpanner:
    def __init__(self) -> None:
        self.st: list[tuple[int, int]] = []  # (price, span), prices strictly decreasing

    def next(self, price: int) -> int:
        span = 1
        while self.st and self.st[-1][0] <= price:
            span += self.st.pop()[1]  # absorb the days that entry covered
        self.st.append((price, span))
        return span


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[100, 80, 60, 70, 60, 75, 85], [10, 20, 30], [5, 5, 5]]:
        b, s = StockSpannerBrute(), StockSpanner()
        print("brute:", *[b.next(p) for p in t])
        print("stack:", *[s.next(p) for p in t])
        print("---")

"""
Syntax notes (Python):
- self.st.pop()[1] pops a tuple and reads its second field.
- print(*list) prints elements separated by spaces.
- reversed(list) iterates backwards without copying.
"""
