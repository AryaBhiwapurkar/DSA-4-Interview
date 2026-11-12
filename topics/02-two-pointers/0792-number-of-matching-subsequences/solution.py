"""
0792. Number of Matching Subsequences  |  Medium  |  Two Pointers
Link: https://leetcode.com/problems/number-of-matching-subsequences/

Problem: Count the words that are subsequences of s.

Examples:
  s = "abcde",      words = ["a","bb","acd","ace"]                          -> 3
  s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]      -> 2
  s = "aaa",        words = ["a","aa","aaa","aaaa","a"]                     -> 4

Approaches:
  1. Two pointers per word           O(W * |s|) time, O(1) space
  2. Binary search on positions      O(|s| + sum L * log|s|) time, O(|s|) space
  3. Waiting buckets  ⭐             O(|s| + sum L) time, O(W) space   <- go-to
"""

from bisect import bisect_right
from collections import defaultdict


# ---------- Approach 1: Two Pointers per Word ----------
def num_matching_subseq_two_ptr(s: str, words: list[str]) -> int:
    def is_sub(w: str) -> bool:
        it = iter(s)
        return all(c in it for c in w)  # `in` on an iterator consumes it up to the match

    return sum(is_sub(w) for w in words)


# ---------- Approach 2: Binary Search on Positions ----------
def num_matching_subseq_binary(s: str, words: list[str]) -> int:
    pos: defaultdict[str, list[int]] = defaultdict(list)
    for i, c in enumerate(s):
        pos[c].append(i)
    count = 0
    for w in words:
        cur = -1
        for c in w:
            p = pos[c]
            k = bisect_right(p, cur)  # first position strictly after cur
            if k == len(p):
                break
            cur = p[k]
        else:
            count += 1
    return count


# ---------- Approach 3: Waiting Buckets ⭐ ----------
def num_matching_subseq(s: str, words: list[str]) -> int:
    waiting: defaultdict[str, list[tuple[int, int]]] = defaultdict(list)  # (word index, next pos)
    for i, w in enumerate(words):
        waiting[w[0]].append((i, 0))
    count = 0
    for c in s:
        bucket, waiting[c] = waiting[c], []  # take it out: re-adds go to a fresh bucket
        for wi, j in bucket:
            j += 1
            if j == len(words[wi]):
                count += 1
            else:
                waiting[words[wi][j]].append((wi, j))
    return count


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("abcde", ["a", "bb", "acd", "ace"]),
             ("dsahjpjauf", ["ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"]),
             ("aaa", ["a", "aa", "aaa", "aaaa", "a"])]
    for s, words in tests:
        print("two ptr:", num_matching_subseq_two_ptr(s, words))
        print("binary :", num_matching_subseq_binary(s, words))
        print("buckets:", num_matching_subseq(s, words))
        print("---")

"""
Syntax notes (Python):
- `c in it` on an iterator advances it past the first match: a compact subsequence test.
- bisect_right(list, x) returns the index of the first element > x.
- bucket, waiting[c] = waiting[c], [] swaps a bucket out in one statement.
"""
