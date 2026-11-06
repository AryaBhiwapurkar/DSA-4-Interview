---
number: 208
title: Implement Trie (Prefix Tree)
difficulty: Medium
topic: Tries
pattern: Trie
link: https://leetcode.com/problems/implement-trie-prefix-tree/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0211 Design Add and Search Words Data Structure", "0212 Word Search II", "0014 Longest Common Prefix", "1268 Search Suggestions System"]
---

# 0208. Implement Trie (Prefix Tree)

## ⚡ 30-Second Summary
**Pattern:** Trie: a tree of characters with an end-of-word flag
**Key insight:** Words sharing a prefix share the path for that prefix. Each node has up to 26 children and a flag saying "a word ends here". insert, search and startsWith all walk one character per step: O(L) regardless of how many words are stored.
**Go-to:** Array-of-26 children + end flag, O(L) per operation, O(total chars · 26) space

## Problem
Implement a trie with `insert(word)`, `search(word)` (was this exact word inserted?) and `startsWith(prefix)` (was any inserted word starting with this prefix?). Lowercase letters only. [LeetCode](https://leetcode.com/problems/implement-trie-prefix-tree/)

**Examples:**
```
Input:  ["Trie","insert","search","search","startsWith","insert","search"]
        [[],["apple"],["apple"],["app"],["app"],["app"],["app"]]
Output: [null,null,true,false,true,null,true]
Why:    "app" is only a prefix until it's inserted itself; after that, search("app") is true.
```

**Constraints:**
- 1 ≤ word length ≤ 2000; lowercase a-z; up to 3·10⁴ calls in total.

## Hints
<details><summary>Hint 1</summary>
A hash set handles search, but how would startsWith work without scanning everything?
</details>
<details><summary>Hint 2</summary>
Store words character by character in a tree, so all words with prefix "ap" share one path.
</details>
<details><summary>Hint 3</summary>
Node = children[26] + isEnd. insert creates missing children and sets isEnd at the last node. search walks and checks isEnd; startsWith walks and only checks the path exists.
</details>

## Clarifying Questions
- Character set? (Lowercase a-z.)
- Empty strings? (No, length ≥ 1.)
- Do we need delete? (Not here.)

## Example Walkthrough
insert "apple": path a-p-p-l-e, mark e as end. search "app": path exists but the second p isn't an end → false. startsWith "app" → path exists → true. insert "app": mark that p as end → search "app" true.

## Approaches

### 1. Hash Set of Words: O(L) insert/search, O(N·L) startsWith
search is easy; startsWith checks every stored word.

### 2. Trie With Fixed 26 Children ⭐ Go-to: O(L) for every operation
**Why it's the go-to:** prefix queries become as cheap as exact queries; it's the canonical structure. (A hashmap of children saves memory for big alphabets.)

## Dry Run (Approach 2)
After insert("apple") and insert("app"):

| op | walk | end flag at last node | result |
|----|------|-----------------------|--------|
| search("apple") | a→p→p→l→e | yes | true |
| search("ap") | a→p | no | false |
| startsWith("appl") | a→p→p→l | (not needed) | true |
| search("apz") | a→p→(no z) | | false |

## Edge Case Check
- Word that's a prefix of another (app / apple): the end flag distinguishes them. ✅
- Searching a longer word than any stored: walk falls off → false. ✅
- Same word inserted twice: harmless. ✅

## ⚠️ Pitfalls
- **search returning true when the path merely exists**: must also check isEnd.
- **C++ memory**: `new TrieNode` per character; real code would free them (or use a node pool vector).
- **Python per-node dicts** are slower than a 26-array, but simpler; either is fine.
- **Go zero values**: `[26]*node` starts as all nil; check before descending.

## 🎯 What the Interviewer Wants
- A clean node design and the search vs startsWith distinction.
- Complexity: O(L) per operation, independent of the number of words.

## Follow-ups
- **Wildcard search ('.'):** [LC 0211 Design Add and Search Words Data Structure](../0211-design-add-and-search-words-data-structure/)
- **Many words on a grid:** [LC 0212 Word Search II](../0212-word-search-ii/)
- **Autocomplete suggestions:** LC 1268 Search Suggestions System (not added yet)
- **Prefix shared by all words:** [LC 0014 Longest Common Prefix](../../01-arrays-hashing/0014-longest-common-prefix/)
