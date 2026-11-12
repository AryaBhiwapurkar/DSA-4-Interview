"""
0085. Maximal Rectangle  |  Hard  |  Stack
Link: https://leetcode.com/problems/maximal-rectangle/

Problem: Largest all-'1' rectangle area in a binary character matrix.

Examples:
  [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]  -> 6
  [["0"]]                    -> 0
  [["1"]]                    -> 1
  [["1","1"],["1","1"]]      -> 4
  [["0","1"],["1","0"]]      -> 1

Approaches:
  1. Every rectangle (prefix-sum check)        O(r^2 * c^2) time
  2. Row widths, extend upwards                O(r^2 * c) time, O(r * c) space
  3. Histogram + monotonic stack  ⭐           O(r * c) time, O(c) space   <- go-to
"""


# ---------- Approach 1: Every Rectangle ----------
def maximal_rectangle_brute(m: list[list[str]]) -> int:
    R, C = len(m), len(m[0])
    P = [[0] * (C + 1) for _ in range(R + 1)]  # 2-D prefix count of ones
    for r in range(R):
        for c in range(C):
            P[r + 1][c + 1] = (m[r][c] == "1") + P[r][c + 1] + P[r + 1][c] - P[r][c]
    best = 0
    for r1 in range(R):
        for c1 in range(C):
            for r2 in range(r1, R):
                for c2 in range(c1, C):
                    area = (r2 - r1 + 1) * (c2 - c1 + 1)
                    if P[r2 + 1][c2 + 1] - P[r1][c2 + 1] - P[r2 + 1][c1] + P[r1][c1] == area:
                        best = max(best, area)
    return best


# ---------- Approach 2: Row Widths ----------
def maximal_rectangle_widths(m: list[list[str]]) -> int:
    R, C = len(m), len(m[0])
    w = [[0] * C for _ in range(R)]  # run of ones ending here, going left
    best = 0
    for r in range(R):
        for c in range(C):
            if m[r][c] != "1":
                continue
            w[r][c] = (w[r][c - 1] if c else 0) + 1
            width, k = w[r][c], r
            while k >= 0 and w[k][c] > 0:  # extend upwards
                width = min(width, w[k][c])
                best = max(best, width * (r - k + 1))
                k -= 1
    return best


# ---------- Approach 3: Histogram + Stack ⭐ ----------
def largest_rectangle(h: list[int]) -> int:
    st: list[int] = []
    best = 0
    for i, cur in enumerate(h + [0]):  # sentinel 0 flushes the stack
        while st and h[st[-1]] > cur:
            height = h[st.pop()]
            left = st[-1] if st else -1
            best = max(best, height * (i - left - 1))
        st.append(i)
    return best


def maximal_rectangle(m: list[list[str]]) -> int:
    h = [0] * len(m[0])
    best = 0
    for row in m:
        h = [x + 1 if cell == "1" else 0 for x, cell in zip(h, row)]  # reset on '0'
        best = max(best, largest_rectangle(h))
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        [["1", "0", "1", "0", "0"], ["1", "0", "1", "1", "1"], ["1", "1", "1", "1", "1"], ["1", "0", "0", "1", "0"]],
        [["0"]], [["1"]], [["1", "1"], ["1", "1"]], [["0", "1"], ["1", "0"]],
    ]
    for t in tests:
        print("brute    :", maximal_rectangle_brute(t))
        print("widths   :", maximal_rectangle_widths(t))
        print("histogram:", maximal_rectangle(t))
        print("---")

"""
Syntax notes (Python):
- h + [0] appends a sentinel without modifying h.
- zip(h, row) walks heights and cells together to build the next histogram.
- (cell == "1") adds as 0/1 in arithmetic.
"""
