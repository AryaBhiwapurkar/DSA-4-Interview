"""
0208. Implement Trie (Prefix Tree)  |  Medium  |  Tries
Link: https://leetcode.com/problems/implement-trie-prefix-tree/

Problem: insert(word), search(word) for an exact word, startsWith(prefix).

Examples:
  insert apple, search apple, search app, startsWith app, insert app, search app
    -> [null,null,true,false,true,null,true]
  insert a, search a, startsWith b, search ab
    -> [null,null,true,false,false]

Approaches:
  1. Hash set of words           O(L) insert/search, O(N*L) startsWith
  2. Trie with 26 children  ⭐    O(L) per operation   <- go-to
"""

from typing import Optional


# ---------- Approach 1: Hash Set of Words ----------
class TrieSet:
    def __init__(self) -> None:
        self.words: set[str] = set()

    def insert(self, word: str) -> None:
        self.words.add(word)

    def search(self, word: str) -> bool:
        return word in self.words

    def startsWith(self, prefix: str) -> bool:
        return any(w.startswith(prefix) for w in self.words)  # scans every word: O(N * L)


# ---------- Approach 2: Trie With 26 Children ⭐ ----------
class TrieNode:
    __slots__ = ("next", "is_end")

    def __init__(self) -> None:
        self.next: list[Optional[TrieNode]] = [None] * 26
        self.is_end = False


class Trie:
    def __init__(self) -> None:
        self.root = TrieNode()

    def _walk(self, s: str) -> Optional[TrieNode]:  # node at the end of s, or None
        n = self.root
        for c in s:
            n = n.next[ord(c) - 97]
            if not n:
                return None
        return n

    def insert(self, word: str) -> None:
        n = self.root
        for c in word:
            i = ord(c) - 97
            if not n.next[i]:
                n.next[i] = TrieNode()
            n = n.next[i]
        n.is_end = True

    def search(self, word: str) -> bool:
        n = self._walk(word)
        return n is not None and n.is_end  # path existing isn't enough

    def startsWith(self, prefix: str) -> bool:
        return self._walk(prefix) is not None


# ---------- Driver ----------
def run(cls: type, ops: list[str], args: list[str]) -> str:
    t = cls()
    out = ["null"]
    for op, a in zip(ops[1:], args[1:]):
        if op == "insert":
            t.insert(a)
            out.append("null")
        else:
            out.append(str(getattr(t, op)(a)).lower())
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        (["Trie", "insert", "search", "search", "startsWith", "insert", "search"],
         ["", "apple", "apple", "app", "app", "app", "app"]),
        (["Trie", "insert", "search", "startsWith", "search"], ["", "a", "a", "b", "ab"]),
    ]
    for ops, args in tests:
        print("set :", run(TrieSet, ops, args))
        print("trie:", run(Trie, ops, args))
        print("---")

"""
Syntax notes (Python):
- __slots__ trims per-node memory (no __dict__), useful for big tries.
- ord(c) - 97 maps 'a'..'z' to 0..25 (97 == ord('a')).
- getattr(obj, "search")(x) calls a method by name.
- A dict of children (defaultdict(TrieNode)) is the shorter alternative.
"""
