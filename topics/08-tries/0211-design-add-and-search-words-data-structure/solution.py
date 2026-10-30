"""
0211. Design Add and Search Words Data Structure  |  Medium  |  Tries
Link: https://leetcode.com/problems/design-add-and-search-words-data-structure/

Problem: addWord(word); search(pattern) where '.' matches any one letter.

Examples:
  add bad, add dad, add mad, search pad, search bad, search .ad, search b..
    -> [null,null,null,null,false,true,true,true]
  add a, search ., search a., search ..
    -> [null,null,true,false,false]

Approaches:
  1. List of words, compare each   O(N*L) per search
  2. Trie + wildcard DFS  ⭐        O(L) add, O(26^dots * L) search   <- go-to
"""


# ---------- Approach 1: List of Words ----------
class WordDictionaryList:
    def __init__(self) -> None:
        self.words: list[str] = []

    def addWord(self, word: str) -> None:
        self.words.append(word)

    def search(self, p: str) -> bool:
        return any(len(w) == len(p) and all(a == "." or a == b for a, b in zip(p, w)) for w in self.words)


# ---------- Approach 2: Trie + Wildcard DFS ⭐ ----------
class TrieNode:
    __slots__ = ("next", "is_end")

    def __init__(self) -> None:
        self.next: dict[str, "TrieNode"] = {}
        self.is_end = False


class WordDictionary:
    def __init__(self) -> None:
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        n = self.root
        for c in word:
            n = n.next.setdefault(c, TrieNode())
        n.is_end = True

    def search(self, p: str) -> bool:
        def dfs(n: TrieNode, i: int) -> bool:
            if i == len(p):
                return n.is_end  # whole pattern consumed
            if p[i] != ".":
                c = n.next.get(p[i])
                return c is not None and dfs(c, i + 1)  # one fixed branch
            return any(dfs(c, i + 1) for c in n.next.values())  # '.': try every child

        return dfs(self.root, 0)


# ---------- Driver ----------
def run(cls: type, ops: list[str], args: list[str]) -> str:
    d = cls()
    out = ["null"]
    for op, a in zip(ops[1:], args[1:]):
        if op == "addWord":
            d.addWord(a)
            out.append("null")
        else:
            out.append(str(d.search(a)).lower())
    return "[" + ",".join(out) + "]"


if __name__ == "__main__":
    tests = [
        (["WordDictionary", "addWord", "addWord", "addWord", "search", "search", "search", "search"],
         ["", "bad", "dad", "mad", "pad", "bad", ".ad", "b.."]),
        (["WordDictionary", "addWord", "search", "search", "search"], ["", "a", ".", "a.", ".."]),
    ]
    for ops, args in tests:
        print("list:", run(WordDictionaryList, ops, args))
        print("trie:", run(WordDictionary, ops, args))
        print("---")

"""
Syntax notes (Python):
- dict.setdefault(k, default) inserts the default only if k is missing
  and returns the stored value: one-line trie insertion.
- any(generator) stops at the first True, so '.' branches short-circuit.
"""
