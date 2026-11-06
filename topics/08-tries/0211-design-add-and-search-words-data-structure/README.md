---
number: 211
title: Design Add and Search Words Data Structure
difficulty: Medium
topic: Tries
pattern: Trie + DFS on wildcard
link: https://leetcode.com/problems/design-add-and-search-words-data-structure/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0208 Implement Trie (Prefix Tree)"]
related: ["0208 Implement Trie (Prefix Tree)", "0212 Word Search II", "0010 Regular Expression Matching"]
---

# 0211. Design Add and Search Words Data Structure

## ⚡ 30-Second Summary
**Pattern:** Trie + DFS that branches on '.'
**Key insight:** Store words in a trie. Searching a normal letter follows one child; a '.' must try every existing child. A recursive search over (node, index) handles both, and branching only happens at dots.
**Go-to:** Trie with recursive wildcard search, O(L) add, O(26^dots · L) worst-case search

## Problem
Design `addWord(word)` and `search(word)`, where the search pattern may contain '.' matching any single letter. search returns whether any added word matches the whole pattern. [LeetCode](https://leetcode.com/problems/design-add-and-search-words-data-structure/)

**Examples:**
```
Input:  ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
        [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output: [null,null,null,null,false,true,true,true]
Why:    "pad" was never added; ".ad" matches bad/dad/mad; "b.." matches bad.
```

**Constraints:**
- Word length ≤ 25; lowercase letters, and search patterns may contain '.'.
- At most 2 dots per search query; up to 10⁴ calls.

## Hints
<details><summary>Hint 1</summary>
Without dots this is exactly 0208's search.
</details>
<details><summary>Hint 2</summary>
At a '.', which children could match?
</details>
<details><summary>Hint 3</summary>
dfs(node, i): if i == len → node.isEnd. If word[i] is '.', return true if any child c has dfs(c, i+1). Else follow that one child.
</details>

## Clarifying Questions
- Does '.' match exactly one letter? (Yes, not zero or many.)
- How many dots? (At most 2 per query.)
- Full-word match, not prefix? (Full word.)

## Example Walkthrough
Trie holds bad, dad, mad. search(".ad"): '.' tries children b, d, m; under b: 'a' → 'd' → end ✓ → true.

## Approaches

### 1. List of Words, Compare Each: O(N · L) per search
Check every stored word of the same length character by character ('.' matches anything).

### 2. Trie + Wildcard DFS ⭐ Go-to: O(L) add, O(26^d · L) search (d = dots ≤ 2)
**Why it's the go-to:** non-dot characters prune instantly, so typical searches are O(L).

## Dry Run (Approach 2)
search("b..") over {bad, dad, mad}

| node | i | char | action |
|------|---|------|--------|
| root | 0 | b | follow b |
| b | 1 | . | try children: a |
| b-a | 2 | . | try children: d |
| b-a-d | 3 | end | isEnd → **true** |

## Edge Case Check
- Pattern longer than every word: DFS falls off → false. ✅
- All dots "...": explores every 3-letter path. ✅
- Prefix match only (search "ba" when only "bad" exists): isEnd false → false. ✅

## ⚠️ Pitfalls
- **Returning true when the walk ends without checking isEnd**.
- **Treating '.' as "zero or more"** (that's regex 0010).
- **Iterative BFS without carrying the index**: easy to mix levels up. Recursion is cleaner.

## 🎯 What the Interviewer Wants
- Reuse 0208 and add branching only where needed.
- Complexity discussion that uses the "≤ 2 dots" constraint.

## Follow-ups
- **Plain trie:** [LC 0208 Implement Trie (Prefix Tree)](../0208-implement-trie-prefix-tree/)
- **'*' wildcards / regex:** DP: [LC 0010 Regular Expression Matching](../../14-2d-dp/0010-regular-expression-matching/)
- **Speed-up for many dots:** bucket words by length so mismatched lengths are skipped immediately.
