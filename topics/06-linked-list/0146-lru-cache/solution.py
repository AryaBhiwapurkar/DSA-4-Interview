"""
0146. LRU Cache  |  Medium  |  Linked List
Link: https://leetcode.com/problems/lru-cache/

Problem: Fixed-capacity cache; get(key) -> value or -1; put(key, value)
         inserts/updates and evicts the least recently used key. O(1).

Examples:
  cap 2: put 1 1, put 2 2, get 1, put 3 3, get 2, put 4 4, get 1, get 3, get 4
    -> [null,null,null,1,null,-1,null,-1,3,4]
  cap 1: put 2 1, get 2, put 3 2, get 2, get 3
    -> [null,null,1,null,-1,2]
  cap 2: put 1 1, put 2 2, put 1 10, put 3 3, get 1, get 2, get 3   (update = use)
    -> [null,null,null,null,null,10,-1,3]

Approaches:
  1. Ordered list, linear search    O(cap) per op, O(cap) space
  2. Hashmap + DLL  ⭐               O(1) per op, O(cap) space   <- go-to
"""

from typing import Optional


# ---------- Approach 1: Ordered List, Linear Search ----------
class LRUCacheBrute:
    def __init__(self, capacity: int) -> None:
        self.cap = capacity
        self.items: list[list[int]] = []  # [key, value]; last = most recent

    def get(self, key: int) -> int:
        for i, (k, v) in enumerate(self.items):
            if k == key:
                self.items.append(self.items.pop(i))  # mark as most recent
                return v
        return -1

    def put(self, key: int, value: int) -> None:
        self.items = [kv for kv in self.items if kv[0] != key]
        if len(self.items) == self.cap:
            self.items.pop(0)  # evict least recent
        self.items.append([key, value])


# ---------- Approach 2: Hashmap + Doubly Linked List ⭐ ----------
class Node:
    def __init__(self, key: int = 0, val: int = 0):
        self.key, self.val = key, val  # key stored so eviction can delete it from the map
        self.prev: Optional[Node] = None
        self.next: Optional[Node] = None


class LRUCache:
    def __init__(self, capacity: int) -> None:
        self.cap = capacity
        self.m: dict[int, Node] = {}
        self.head, self.tail = Node(), Node()  # sentinels: head.next = MRU, tail.prev = LRU
        self.head.next, self.tail.prev = self.tail, self.head

    def _unlink(self, n: Node) -> None:
        n.prev.next, n.next.prev = n.next, n.prev

    def _push_front(self, n: Node) -> None:
        n.prev, n.next = self.head, self.head.next
        self.head.next.prev = n
        self.head.next = n

    def get(self, key: int) -> int:
        n = self.m.get(key)
        if n is None:
            return -1
        self._unlink(n)
        self._push_front(n)
        return n.val

    def put(self, key: int, value: int) -> None:
        if key in self.m:  # update: no eviction
            n = self.m[key]
            n.val = value
            self._unlink(n)
            self._push_front(n)
            return
        if len(self.m) == self.cap:
            lru = self.tail.prev
            self._unlink(lru)
            del self.m[lru.key]
        n = Node(key, value)
        self.m[key] = n
        self._push_front(n)


# ---------- Driver ----------
def run(cls: type, ops: list[str], args: list[list[int]]) -> str:
    c = cls(args[0][0])
    out = ["null"]
    for op, a in zip(ops[1:], args[1:]):
        if op == "put":
            c.put(*a)
            out.append("null")
        else:
            out.append(str(c.get(*a)))
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        (["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"],
         [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]),
        (["LRUCache", "put", "get", "put", "get", "get"],
         [[1], [2, 1], [2], [3, 2], [2], [3]]),
        (["LRUCache", "put", "put", "put", "put", "get", "get", "get"],
         [[2], [1, 1], [2, 2], [1, 10], [3, 3], [1], [2], [3]]),
    ]
    for ops, args in tests:
        print("brute:", run(LRUCacheBrute, ops, args))
        print("dll  :", run(LRUCache, ops, args))
        print("---")

"""
Syntax notes (Python):
- Library variant: collections.OrderedDict with move_to_end(key) and
  popitem(last=False) gives the same O(1) behaviour in a few lines.
- dict.get(key) returns None for a missing key without raising.
- Tuple assignment relinks two pointers at once: n.prev.next, n.next.prev = ...
- A leading underscore (_unlink) marks a helper as internal by convention.
"""
