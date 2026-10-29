"""
0151. Reverse Words in a String  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/reverse-words-in-a-string/

Problem: Return the words of s in reverse order, joined by single
         spaces, with no leading/trailing/repeated spaces.

Examples:
  "the sky is blue"    -> "blue is sky the"
  "  hello world  "    -> "world hello"
  "a good   example"   -> "example good a"
  "single"             -> "single"

Approaches:
  1. Split + reverse + join  ⭐   O(n) time, O(n) space   <- go-to
  2. In-place reversal           O(n) time, O(n) space in Python (str is immutable)
"""


# ---------- Approach 1: Split + Reverse + Join ⭐ ----------
def reverse_words(s: str) -> str:
    return " ".join(reversed(s.split()))


# ---------- Approach 2: In-Place Reversal + Compaction ----------
def reverse_words_in_place(s: str) -> str:
    a = list(s)  # strings are immutable: work on a char list

    def rev(lo: int, hi: int) -> None:  # reverse a[lo:hi]
        hi -= 1
        while lo < hi:
            a[lo], a[hi] = a[hi], a[lo]
            lo, hi = lo + 1, hi - 1

    n = len(a)
    rev(0, n)  # words in final order, each backwards
    write = read = 0
    while read < n:
        if a[read] == " ":
            read += 1
            continue
        if write > 0:  # one space before every word but the first
            a[write] = " "
            write += 1
        start = write
        while read < n and a[read] != " ":
            a[write] = a[read]
            write, read = write + 1, read + 1
        rev(start, write)  # fix this word
    return "".join(a[:write])  # drop leftover tail


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["the sky is blue", "  hello world  ", "a good   example", "single"]:
        print(f'split   : "{reverse_words(s)}"')
        print(f'in-place: "{reverse_words_in_place(s)}"')
        print("---")

"""
Syntax notes (Python):
- s.split() with no argument splits on runs of whitespace and drops empties.
- reversed(list) returns an iterator; " ".join accepts any iterable of str.
- list(s) gives a mutable list of characters.
"""
