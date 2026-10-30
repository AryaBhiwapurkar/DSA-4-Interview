# 08. Tries

## Core Idea
A trie (prefix tree) stores strings character by character: each node has one child per possible next character and a flag (or the word itself) marking "a word ends here". Words that share a prefix share a path, so "does any word start with P?" costs O(|P|), independent of how many words are stored. Tries shine when you ask many prefix questions, or walk many words at once (a grid DFS that stops the moment its path leaves the trie).

## When to Use
- Prefix queries: startsWith, autocomplete, counting words with a prefix (0208).
- Exact search with wildcards: branch only at the wildcard (0211).
- Searching many words simultaneously in a grid or text: trie + DFS with pruning (0212).
- Longest common prefix of many strings, word-break style dictionaries, XOR-maximum with a bitwise trie.

## Templates

### Node, insert, search, startsWith
```cpp
struct Node { Node* next[26] = {}; bool isEnd = false; };
void insert(Node* root, const string& w) {
    Node* n = root;
    for (char c : w) {
        if (!n->next[c - 'a']) n->next[c - 'a'] = new Node();
        n = n->next[c - 'a'];
    }
    n->isEnd = true;
}
Node* walk(Node* n, const string& s) {
    for (char c : s) if (!(n = n->next[c - 'a'])) return nullptr;
    return n;                            // search: walk && isEnd; startsWith: walk != null
}
```
```python
class Node:
    def __init__(self):
        self.next = {}          # or [None] * 26
        self.is_end = False

def insert(root, w):
    n = root
    for c in w:
        n = n.next.setdefault(c, Node())
    n.is_end = True

def walk(n, s):
    for c in s:
        n = n.next.get(c)
        if not n:
            return None
    return n
```
```go
type node struct {
	next  [26]*node
	isEnd bool
}

func insert(root *node, w string) {
	n := root
	for i := 0; i < len(w); i++ {
		c := w[i] - 'a'
		if n.next[c] == nil {
			n.next[c] = &node{}
		}
		n = n.next[c]
	}
	n.isEnd = true
}
```

### Wildcard DFS
```python
def dfs(n, i):
    if i == len(p):
        return n.is_end
    if p[i] != ".":
        c = n.next.get(p[i])
        return c is not None and dfs(c, i + 1)
    return any(dfs(c, i + 1) for c in n.next.values())
```

## Common Variations
- **Children as array vs hashmap:** array[26] is fast and simple; a map saves memory for large alphabets.
- **Store the word at the end node** instead of a flag, so a DFS can report it without rebuilding strings (0212).
- **Prefix counts per node** for "how many words start with P".
- **Pruning:** delete branches whose words were all found (0212).
- **Bitwise trie:** 0/1 children over bits for maximum XOR pair problems.

## ⚠️ Pitfalls
- **search vs startsWith:** search must check the end flag; a path alone only proves a prefix.
- **Duplicates in grid search:** clear a word once found.
- **Memory:** 26 pointers per node add up; consider maps or a node pool for huge inputs.
- **Visited marking in grid DFS:** mark before recursing, restore after.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0208 | [Implement Trie (Prefix Tree)](0208-implement-trie-prefix-tree/) | Medium | Trie | ✅ |
| 0211 | [Design Add and Search Words Data Structure](0211-design-add-and-search-words-data-structure/) | Medium | Trie + DFS on wildcard | ✅ |
| 0212 | [Word Search II](0212-word-search-ii/) | Hard | Trie + grid backtracking | ✅ |
