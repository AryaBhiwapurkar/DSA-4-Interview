"""
0981. Time Based Key-Value Store  |  Medium  |  Binary Search
Link: https://leetcode.com/problems/time-based-key-value-store/

Problem: set(key, value, t) stores a version; get(key, t) returns the
         value with the largest timestamp <= t, or "". Set timestamps
         are strictly increasing.

Examples:
  set foo bar 1, get foo 1, get foo 3, set foo bar2 4, get foo 4, get foo 5
    -> [null,null,"bar","bar",null,"bar2","bar2"]
  set a x 5, get a 4, get b 1, get a 5
    -> [null,null,"","","x"]

Approaches:
  1. Hashmap + linear scan        O(1) set, O(n) get, O(n) space
  2. Hashmap + binary search  ⭐   O(1) set, O(log n) get, O(n) space   <- go-to
"""

from bisect import bisect_right
from collections import defaultdict


# ---------- Approach 1: Hashmap + Linear Scan ----------
class TimeMapLinear:
    def __init__(self) -> None:
        self.m: defaultdict[str, list[tuple[int, str]]] = defaultdict(list)

    def set(self, key: str, value: str, timestamp: int) -> None:
        self.m[key].append((timestamp, value))

    def get(self, key: str, timestamp: int) -> str:
        for t, v in reversed(self.m.get(key, [])):  # newest first; .get avoids inserting
            if t <= timestamp:
                return v
        return ""


# ---------- Approach 2: Hashmap + Binary Search ⭐ ----------
class TimeMap:
    def __init__(self) -> None:
        self.times: defaultdict[str, list[int]] = defaultdict(list)  # sorted for free
        self.vals: defaultdict[str, list[str]] = defaultdict(list)

    def set(self, key: str, value: str, timestamp: int) -> None:
        self.times[key].append(timestamp)
        self.vals[key].append(value)

    def get(self, key: str, timestamp: int) -> str:
        if key not in self.times:
            return ""
        i = bisect_right(self.times[key], timestamp)  # first timestamp > t
        return self.vals[key][i - 1] if i else ""


# ---------- Driver ----------
def run(cls: type, ops: list[str], args: list[list]) -> str:
    tm = cls()  # ops[0] is the constructor
    out = ["null"]
    for op, a in zip(ops[1:], args[1:]):
        if op == "set":
            tm.set(*a)
            out.append("null")
        else:
            out.append(f'"{tm.get(*a)}"')
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        (["TimeMap", "set", "get", "get", "set", "get", "get"],
         [[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]),
        (["TimeMap", "set", "get", "get", "get"],
         [[], ["a", "x", 5], ["a", 4], ["b", 1], ["a", 5]]),
    ]
    for ops, args in tests:
        print("linear:", run(TimeMapLinear, ops, args))
        print("binary:", run(TimeMap, ops, args))
        print("---")

"""
Syntax notes (Python):
- bisect_right(a, x) = first index with a[i] > x (upper bound).
- Parallel lists (times, vals) let bisect work on plain ints; bisect also
  accepts key= (3.10+) on a list of tuples.
- defaultdict(list) creates [] on first access; use `in` or .get() for
  lookups that shouldn't insert.
- f(*a) unpacks a list into positional arguments.
"""
