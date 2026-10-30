"""
0739. Daily Temperatures  |  Medium  |  Stack
Link: https://leetcode.com/problems/daily-temperatures/

Problem: For each day, how many days until a strictly warmer one?
         0 if none.

Examples:
  [73,74,75,71,69,72,76,73]  -> [1,1,4,2,1,1,0,0]
  [30,40,50,60]              -> [1,1,1,0]
  [30,60,90]                 -> [1,1,0]
  [70,70]                    -> [0,0]
  [5,4,3]                    -> [0,0,0]

Approaches:
  1. Brute force         O(n^2) time, O(1) extra space
  2. Monotonic stack  ⭐  O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def daily_temperatures_brute(t: list[int]) -> list[int]:
    n = len(t)
    ans = [0] * n
    for i in range(n):
        for j in range(i + 1, n):
            if t[j] > t[i]:
                ans[i] = j - i
                break
    return ans


# ---------- Approach 2: Monotonic Stack ⭐ ----------
def daily_temperatures(t: list[int]) -> list[int]:
    ans = [0] * len(t)  # unresolved days stay 0
    st: list[int] = []  # indices; temps decreasing bottom -> top
    for i, temp in enumerate(t):
        while st and temp > t[st[-1]]:  # strictly warmer resolves
            j = st.pop()
            ans[j] = i - j
        st.append(i)
    return ans


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [[73, 74, 75, 71, 69, 72, 76, 73], [30, 40, 50, 60], [30, 60, 90], [70, 70], [5, 4, 3]]
    for t in tests:
        print("brute:", daily_temperatures_brute(t))
        print("stack:", daily_temperatures(t))
        print("---")

"""
Syntax notes (Python):
- [0] * n creates a list of n zeros (safe for immutable ints).
- `while st and ...` checks non-empty before st[-1].
- j = st.pop() both removes and returns the top.
"""
