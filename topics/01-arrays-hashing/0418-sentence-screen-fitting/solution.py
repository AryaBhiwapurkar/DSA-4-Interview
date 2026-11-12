"""
0418. Sentence Screen Fitting  |  Medium  |  Arrays & Hashing  |  LC Premium
Link: https://leetcode.com/problems/sentence-screen-fitting/

Problem: rows x cols screen; write the sentence repeatedly, words never split,
         one space between words on a line. How many full sentences fit?

Examples:
  rows=2, cols=8, ["hello","world"]          -> 1
  rows=3, cols=6, ["a","bcd","e"]            -> 2
  rows=4, cols=5, ["i","had","apple","pie"]  -> 1
  rows=3, cols=2, ["abc"]                    -> 0   (word longer than a row)
  rows=5, cols=3, ["a","b"]                  -> 5   (sentence fits exactly per row)

Approaches:
  1. Word-by-word simulation          O(rows * cols) worst time, O(1) space
  2. Joined-string pointer  ⭐        O(rows * maxWordLen) time, O(L) space   <- go-to
"""


# ---------- Approach 1: Word-by-word ----------
def words_typing_sim(sentence: list[str], rows: int, cols: int) -> int:
    if any(len(w) > cols for w in sentence):
        return 0  # can never be placed
    n, idx, count = len(sentence), 0, 0
    for _ in range(rows):
        used = 0  # characters used on this row
        while used + len(sentence[idx]) <= cols:
            used += len(sentence[idx]) + 1  # word plus a separating space
            idx += 1
            if idx == n:
                idx, count = 0, count + 1
    return count


# ---------- Approach 2: Joined-string Pointer ⭐ ----------
def words_typing(sentence: list[str], rows: int, cols: int) -> int:
    s = " ".join(sentence) + " "  # trailing space marks the wrap boundary
    L, pos = len(s), 0
    for _ in range(rows):
        pos += cols
        if s[pos % L] == " ":
            pos += 1  # row ended on a boundary: skip the space
        else:
            while pos > 0 and s[(pos - 1) % L] != " ":
                pos -= 1  # cut mid-word: move that word down
    return pos // L


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(2, 8, ["hello", "world"]), (3, 6, ["a", "bcd", "e"]),
             (4, 5, ["i", "had", "apple", "pie"]), (3, 2, ["abc"]), (5, 3, ["a", "b"])]
    for rows, cols, words in tests:
        print("simulate:", words_typing_sim(words, rows, cols))
        print("pointer :", words_typing(words, rows, cols))
        print("---")

"""
Syntax notes (Python):
- " ".join(words) + " " builds the looping sentence with a trailing separator.
- pos % L indexes an "infinite" repetition of s without building it.
- idx, count = 0, count + 1 updates two variables at once.
"""
