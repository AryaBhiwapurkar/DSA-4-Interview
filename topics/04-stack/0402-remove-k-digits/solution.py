"""
0402. Remove K Digits  |  Medium  |  Stack
Link: https://leetcode.com/problems/remove-k-digits/

Problem: Remove exactly k digits from num to make the smallest number (no leading zeros).

Examples:
  "1432219", k = 3  -> "1219"
  "10200",   k = 1  -> "200"
  "10",      k = 2  -> "0"
  "12345",   k = 2  -> "123"
  "112",     k = 1  -> "11"

Approaches:
  1. Remove one peak at a time      O(n * k) time
  2. Monotonic stack  ⭐            O(n) time, O(n) space   <- go-to
"""


# ---------- Approach 1: One Peak at a Time ----------
def remove_kdigits_peaks(num: str, k: int) -> str:
    for _ in range(k):
        i = 0
        while i + 1 < len(num) and num[i] <= num[i + 1]:
            i += 1  # first digit bigger than its successor
        num = num[:i] + num[i + 1:]
    return num.lstrip("0") or "0"


# ---------- Approach 2: Monotonic Stack ⭐ ----------
def remove_kdigits(num: str, k: int) -> str:
    st: list[str] = []
    for d in num:
        while k and st and st[-1] > d:
            st.pop()  # a smaller digit earlier always wins
            k -= 1
        st.append(d)
    if k:
        st = st[:-k]  # leftover k: trim the tail
    return "".join(st).lstrip("0") or "0"


# ---------- Driver ----------
if __name__ == "__main__":
    for num, k in [("1432219", 3), ("10200", 1), ("10", 2), ("12345", 2), ("112", 1)]:
        print(f'peaks: "{remove_kdigits_peaks(num, k)}"')
        print(f'stack: "{remove_kdigits(num, k)}"')
        print("---")

"""
Syntax notes (Python):
- Digit characters compare correctly as strings ("3" > "2").
- st[:-k] drops the last k items; guard k == 0, since st[:-0] is empty.
- s.lstrip("0") or "0" strips leading zeros and falls back to "0".
"""
