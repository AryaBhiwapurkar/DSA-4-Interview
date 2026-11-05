"""
0135. Candy  |  Hard  |  Greedy
Link: https://leetcode.com/problems/candy/

Problem: Give each child at least one candy; a child rated higher than a
         neighbour gets more than that neighbour. Minimise the total.

Examples:
  [1,0,2]             -> 5
  [1,2,2]             -> 4
  [5]                 -> 1
  [3,2,1]             -> 6
  [1,3,4,5,2]         -> 11
  [1,2,87,87,87,2,1]  -> 13
  [1,2,5,4,3,2]       -> 13  (right pass raises the peak)

Approaches:
  1. Repeated relaxation until stable     O(n^2) time, O(n) space
  2. Two passes, left then right  ⭐       O(n) time, O(n) space   <- go-to
  3. One pass over slopes                 O(n) time, O(1) space
"""


# ---------- Approach 1: Repeated Relaxation ----------
def candy_brute(ratings: list[int]) -> int:
    n = len(ratings)
    c = [1] * n
    changed = True
    while changed:  # fix violations until none remain
        changed = False
        for i in range(n):
            if i > 0 and ratings[i] > ratings[i - 1] and c[i] <= c[i - 1]:
                c[i] = c[i - 1] + 1
                changed = True
            if i + 1 < n and ratings[i] > ratings[i + 1] and c[i] <= c[i + 1]:
                c[i] = c[i + 1] + 1
                changed = True
    return sum(c)


# ---------- Approach 2: Two Passes ⭐ ----------
def candy(ratings: list[int]) -> int:
    n = len(ratings)
    c = [1] * n
    for i in range(1, n):  # left neighbour rule
        if ratings[i] > ratings[i - 1]:
            c[i] = c[i - 1] + 1
    for i in range(n - 2, -1, -1):  # right neighbour rule, keeping the left result
        if ratings[i] > ratings[i + 1]:
            c[i] = max(c[i], c[i + 1] + 1)
    return sum(c)


# ---------- Approach 3: One Pass over Slopes ----------
def candy_slopes(ratings: list[int]) -> int:
    total, up, down, peak = 1, 0, 0, 0
    for i in range(1, len(ratings)):
        if ratings[i] > ratings[i - 1]:
            up += 1
            peak, down = up, 0
            total += 1 + up
        elif ratings[i] == ratings[i - 1]:  # flat: restart from 1
            up = down = peak = 0
            total += 1
        else:
            up = 0
            down += 1
            total += 1 + down - (1 if peak >= down else 0)  # grow the peak only once down passes it
    return total


# ---------- Driver ----------
if __name__ == "__main__":
    for t in [[1, 0, 2], [1, 2, 2], [5], [3, 2, 1], [1, 3, 4, 5, 2], [1, 2, 87, 87, 87, 2, 1], [1, 2, 5, 4, 3, 2]]:
        print("brute :", candy_brute(t))
        print("passes:", candy(t))
        print("slopes:", candy_slopes(t))
        print("---")

"""
Syntax notes (Python):
- range(n - 2, -1, -1) walks right to left, ending at index 0.
- max(c[i], c[i + 1] + 1) keeps whatever the left pass already required.
- `up = down = peak = 0` resets several names at once.
"""
