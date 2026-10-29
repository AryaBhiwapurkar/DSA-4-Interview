"""
0030. Substring with Concatenation of All Words  |  Hard  |  Sliding Window
Link: https://leetcode.com/problems/substring-with-concatenation-of-all-words/

Problem: Words all have length w. Return every start index in s where
         the next m*w chars are a concatenation of all words, each once.

Examples (printed sorted):
  "barfoothefoobarman", ["foo","bar"]                         -> [0,9]
  "wordgoodgoodgoodbestword", ["word","good","best","word"]   -> []
  "barfoofoobarthefoobarman", ["bar","foo","the"]             -> [6,9,12]
  "aaaa", ["aa","aa"]                                         -> [0]

Approaches:
  1. Check every start             O(n * m * w) time, O(m * w) space
  2. Per-offset token window  ⭐    O(n * w) time, O(m * w) space   <- go-to
"""

from collections import Counter


# ---------- Approach 1: Check Every Start ----------
def find_substring_brute(s: str, words: list[str]) -> list[int]:
    m, w = len(words), len(words[0])
    need = Counter(words)
    return [
        i
        for i in range(len(s) - m * w + 1)
        if Counter(s[i + j * w : i + (j + 1) * w] for j in range(m)) == need
    ]


# ---------- Approach 2: Per-Offset Token Window ⭐ ----------
def find_substring(s: str, words: list[str]) -> list[int]:
    n, m, w = len(s), len(words), len(words[0])
    need = Counter(words)
    res: list[int] = []
    for off in range(w):  # valid starts live on one of w tracks
        win: Counter = Counter()
        left = off
        count = 0  # tokens in window
        for r in range(off, n - w + 1, w):
            tok = s[r : r + w]
            if tok not in need:  # non-word breaks every window: reset
                win.clear()
                count = 0
                left = r + w
                continue
            win[tok] += 1
            count += 1
            while win[tok] > need[tok]:  # too many copies: drop from the left
                win[s[left : left + w]] -= 1
                left += w
                count -= 1
            if count == m:
                res.append(left)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ("barfoothefoobarman", ["foo", "bar"]),
        ("wordgoodgoodgoodbestword", ["word", "good", "best", "word"]),
        ("barfoofoobarthefoobarman", ["bar", "foo", "the"]),
        ("aaaa", ["aa", "aa"]),
    ]
    for s, words in tests:
        print("brute :", sorted(find_substring_brute(s, words)))  # sorted: order is unspecified
        print("window:", sorted(find_substring(s, words)))
        print("---")

"""
Syntax notes (Python):
- Counter(iterable) == Counter(...) compares multisets.
- range(off, n - w + 1, w) steps through tokens on one offset track.
- Counter.clear() empties the counts in place.
"""
