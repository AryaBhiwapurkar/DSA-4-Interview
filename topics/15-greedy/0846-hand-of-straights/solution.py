"""
0846. Hand of Straights  |  Medium  |  Greedy
Link: https://leetcode.com/problems/hand-of-straights/

Problem: Can the cards be split into groups of groupSize consecutive values,
         every card used exactly once?

Examples:
  [1,2,3,6,2,3,4,7,8], 3   -> true
  [1,2,3,4,5], 4           -> false
  [1], 1                   -> true
  [1,1,2,2,3,3], 3         -> true
  [1,2,4], 3               -> false

Approaches:
  1. Sort + remove one group at a time       O(n^2) with a list, O(n log n) with a multiset
  2. Sorted counts, build from the min  ⭐    O(n log n + n*k) time, O(n) space   <- go-to
"""

from collections import Counter


# ---------- Approach 1: Sort + Remove ----------
def is_n_straight_hand_brute(hand: list[int], k: int) -> bool:
    if len(hand) % k:
        return False
    cards = sorted(hand)
    while cards:
        low = cards[0]  # the smallest card must start a group
        for v in range(low, low + k):
            if v not in cards:
                return False
            cards.remove(v)  # removes the first occurrence: O(n)
    return True


# ---------- Approach 2: Sorted Counts ⭐ ----------
def is_n_straight_hand(hand: list[int], k: int) -> bool:
    if len(hand) % k:
        return False
    count = Counter(hand)
    for low in sorted(count):  # ascending: the smallest remaining card starts groups
        c = count[low]
        if c == 0:
            continue
        for v in range(low, low + k):  # open c groups starting at low at once
            if count[v] < c:
                return False
            count[v] -= c
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [([1, 2, 3, 6, 2, 3, 4, 7, 8], 3), ([1, 2, 3, 4, 5], 4), ([1], 1), ([1, 1, 2, 2, 3, 3], 3), ([1, 2, 4], 3)]
    for hand, k in tests:
        print("brute :", str(is_n_straight_hand_brute(hand, k)).lower())
        print("counts:", str(is_n_straight_hand(hand, k)).lower())
        print("---")

"""
Syntax notes (Python):
- Counter returns 0 for missing keys (and doesn't insert them on read).
- sorted(counter) iterates the distinct values in ascending order.
- list.remove(x) deletes the first match and raises if absent, hence the `in` check.
"""
