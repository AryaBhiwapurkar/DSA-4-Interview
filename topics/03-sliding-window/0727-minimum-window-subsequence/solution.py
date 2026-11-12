"""
0727. Minimum Window Subsequence  |  Hard  |  Sliding Window  |  LC Premium
Link: https://leetcode.com/problems/minimum-window-subsequence/

Problem: Shortest substring of s1 containing s2 as a subsequence (left-most on ties), or "".

Examples:
  s1 = "abcdebdde", s2 = "bde"                                 -> "bcde"
  s1 = "jmeqksfrsdcmsiwvaovztaqenprpvnbstl", s2 = "u"          -> ""
  s1 = "abc", s2 = "abc"                                       -> "abc"
  s1 = "fgrqsqsnodwmxzkzxwqegkndaa", s2 = "kzed"               -> "kzxwqegknd"

Approaches:
  1. DP of latest start               O(|s1| * |s2|) time, O(|s2|) space
  2. Forward-backward  ⭐             O(|s1| * |s2|) worst time, O(1) space   <- go-to
"""


# ---------- Approach 1: DP of Latest Start ----------
def min_window_dp(s1: str, s2: str) -> str:
    m = len(s2)
    start = [-1] * m  # start[j]: latest start matching s2[0..j]
    best = (float("inf"), -1)
    for i, c in enumerate(s1):
        for j in range(m - 1, -1, -1):  # high to low: read last step's start[j-1]
            if c == s2[j]:
                start[j] = i if j == 0 else start[j - 1]
        if start[-1] >= 0 and i - start[-1] + 1 < best[0]:
            best = (i - start[-1] + 1, start[-1])
    return "" if best[1] < 0 else s1[best[1]:best[1] + int(best[0])]


# ---------- Approach 2: Forward-Backward ⭐ ----------
def min_window(s1: str, s2: str) -> str:
    n, m = len(s1), len(s2)
    best_start, best_len = -1, n + 1
    i = j = 0
    while i < n:
        if s1[i] == s2[j]:
            j += 1
            if j == m:  # s2 fully matched, ending at i
                end = i
                j = m - 1
                while j >= 0:  # walk back to the latest start
                    if s1[i] == s2[j]:
                        j -= 1
                    i -= 1
                i += 1  # i is now the window start
                if end - i + 1 < best_len:  # strict: keep left-most
                    best_start, best_len = i, end - i + 1
                j = 0  # restart just after this start
        i += 1
    return "" if best_start < 0 else s1[best_start:best_start + best_len]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("abcdebdde", "bde"), ("jmeqksfrsdcmsiwvaovztaqenprpvnbstl", "u"), ("abc", "abc"),
             ("fgrqsqsnodwmxzkzxwqegkndaa", "kzed")]
    for a, b in tests:
        print(f'dp      : "{min_window_dp(a, b)}"')
        print(f'backward: "{min_window(a, b)}"')
        print("---")

"""
Syntax notes (Python):
- Tuples compare element-wise, so (length, start) could also break ties automatically.
- s[a:a + k] slices k characters starting at a.
- n + 1 is a safe "no window yet" length sentinel.
"""
