"""
0032. Longest Valid Parentheses  |  Hard  |  Stack
Link: https://leetcode.com/problems/longest-valid-parentheses/

Problem: Length of the longest well-formed parentheses substring.

Examples:
  "(()"       -> 2
  ")()())"    -> 4
  ""          -> 0
  "()(())"    -> 6
  "())(())"   -> 4

Approaches:
  1. Check every even-length substring     O(n^2) time (with a running balance)
  2. DP ending at i                        O(n) time, O(n) space
  3. Index stack with base  ⭐             O(n) time, O(n) space   <- go-to
  (+ two-pass counters, O(1) space, shown as an extra function)
"""


# ---------- Approach 1: Every Substring ----------
def longest_valid_parentheses_brute(s: str) -> int:
    best = 0
    for i in range(len(s)):
        bal = 0
        for j in range(i, len(s)):
            bal += 1 if s[j] == "(" else -1
            if bal < 0:
                break  # can't recover
            if bal == 0:
                best = max(best, j - i + 1)
    return best


# ---------- Approach 2: DP ----------
def longest_valid_parentheses_dp(s: str) -> int:
    n = len(s)
    dp = [0] * n  # longest valid ending at i
    for i in range(1, n):
        if s[i] != ")":
            continue
        if s[i - 1] == "(":
            dp[i] = (dp[i - 2] if i >= 2 else 0) + 2
        else:
            j = i - dp[i - 1] - 1  # char before the block ending at i-1
            if j >= 0 and s[j] == "(":
                dp[i] = dp[i - 1] + 2 + (dp[j - 1] if j >= 1 else 0)
    return max(dp, default=0)


# ---------- Approach 3: Index Stack ⭐ ----------
def longest_valid_parentheses(s: str) -> int:
    st = [-1]  # base: index before the current run
    best = 0
    for i, c in enumerate(s):
        if c == "(":
            st.append(i)
        else:
            st.pop()
            if not st:
                st.append(i)  # unmatched ')': new base
            else:
                best = max(best, i - st[-1])
    return best


# ---------- Extra: Two-pass Counters, O(1) Space ----------
def longest_valid_parentheses_counters(s: str) -> int:
    best = 0
    for seq, opener in ((s, "("), (s[::-1], ")")):
        o = c = 0
        for ch in seq:
            if ch == opener:
                o += 1
            else:
                c += 1
            if o == c:
                best = max(best, 2 * c)
            elif c > o:
                o = c = 0
    return best


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["(()", ")()())", "", "()(())", "())(())"]:
        print("brute   :", longest_valid_parentheses_brute(s))
        print("dp      :", longest_valid_parentheses_dp(s))
        print("stack   :", longest_valid_parentheses(s))
        print("counters:", longest_valid_parentheses_counters(s))
        print("---")

"""
Syntax notes (Python):
- max(list, default=0) avoids an error on an empty list.
- Reversing the string and swapping which bracket "opens" reuses one loop for both passes.
- st = [-1] seeds the stack with a sentinel index.
"""
