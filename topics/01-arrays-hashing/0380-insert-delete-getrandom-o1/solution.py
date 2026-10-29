"""
0380. Insert Delete GetRandom O(1)  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/insert-delete-getrandom-o1/

Problem: Design a set with insert, remove (both return whether they
         changed the set) and getRandom (uniform), all O(1) average.

Examples:
  insert 1, remove 2, insert 2, getRandom, remove 1, insert 2, getRandom
  -> true, false, true, (1 or 2), true, false, 2

Approaches:
  1. Hash set only               insert/remove O(1), getRandom O(n)
  2. Map + array, swap-delete  ⭐  all O(1) average, O(n) space   <- go-to
"""

import random


# ---------- Approach 1: Hash Set Only ----------
class RandomizedSetNaive:
    def __init__(self) -> None:
        self.s: set[int] = set()

    def insert(self, val: int) -> bool:
        if val in self.s:
            return False
        self.s.add(val)
        return True

    def remove(self, val: int) -> bool:
        if val not in self.s:
            return False
        self.s.remove(val)
        return True

    def get_random(self) -> int:
        return random.choice(list(self.s))  # O(n) copy: sets have no random access


# ---------- Approach 2: Map + Array, Swap-Delete ⭐ ----------
class RandomizedSet:
    def __init__(self) -> None:
        self.arr: list[int] = []
        self.pos: dict[int, int] = {}  # value -> index in arr

    def insert(self, val: int) -> bool:
        if val in self.pos:
            return False
        self.pos[val] = len(self.arr)
        self.arr.append(val)
        return True

    def remove(self, val: int) -> bool:
        if val not in self.pos:
            return False
        idx, last = self.pos[val], self.arr[-1]
        self.arr[idx] = last  # fill the hole with the last element
        self.pos[last] = idx  # update BEFORE deleting (val may equal last)
        self.arr.pop()
        del self.pos[val]
        return True

    def get_random(self) -> int:
        return random.choice(self.arr)


# ---------- Driver ----------
def run(label: str, rs: RandomizedSetNaive | RandomizedSet) -> None:
    out = [rs.insert(1), rs.remove(2), rs.insert(2)]
    r = rs.get_random()
    out.append(f"(rand in {{1,2}}: {r in (1, 2)})")
    out += [rs.remove(1), rs.insert(2), rs.get_random()]
    print(f"{label}:", " ".join(str(x).lower() for x in out))


if __name__ == "__main__":
    random.seed(42)
    run("naive", RandomizedSetNaive())
    run("map+array", RandomizedSet())

"""
Syntax notes (Python):
- random.choice(seq) needs an indexable sequence (list), not a set.
- del d[k] removes a key; d.pop(k, None) removes without raising.
- {{ and }} in an f-string produce literal braces.
- X | Y in type hints (3.10+) means "either type".
"""
