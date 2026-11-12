"""
0557. Reverse Words in a String III  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/reverse-words-in-a-string-iii/

Problem: Reverse the characters of each word, keeping word order and single spaces.

Examples:
  "Let's take LeetCode contest"  -> "s'teL ekat edoCteeL tsetnoc"
  "Mr Ding"                      -> "rM gniD"
  "a"                            -> "a"
  "ab c de"                      -> "ba c ed"

Approaches:
  1. Split, reverse, join               O(n) time, O(n) space
  2. In-place per-word reversal  ⭐     O(n) time, O(1) extra   <- go-to (on a char list)
"""


# ---------- Approach 1: Split, Reverse, Join ----------
def reverse_words_split(s: str) -> str:
    return " ".join(w[::-1] for w in s.split(" "))


# ---------- Approach 2: In-place Per-word ⭐ ----------
def reverse_words(s: str) -> str:
    a = list(s)  # strings are immutable; work on a list
    start = 0
    for i in range(len(a) + 1):
        if i == len(a) or a[i] == " ":  # i == len catches the last word
            lo, hi = start, i - 1
            while lo < hi:
                a[lo], a[hi] = a[hi], a[lo]
                lo, hi = lo + 1, hi - 1
            start = i + 1
    return "".join(a)


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["Let's take LeetCode contest", "Mr Ding", "a", "ab c de"]:
        print(f'split  : "{reverse_words_split(s)}"')
        print(f'inplace: "{reverse_words(s)}"')
        print("---")

"""
Syntax notes (Python):
- s.split(" ") keeps exact single-space structure; s.split() also drops extra whitespace.
- list(s) / "".join(a) convert between an immutable str and a mutable char list.
- Short-circuit `i == len(a) or a[i] == " "` avoids indexing past the end.
"""
