---
number: 14
title: Longest Common Prefix
difficulty: Easy
topic: Arrays & Hashing
pattern: Vertical scan
link: https://leetcode.com/problems/longest-common-prefix/
lists: [LC Top Interview 150]
followup_of: []
related: ["0208 Implement Trie (Prefix Tree)"]
---

# 0014. Longest Common Prefix

## ⚡ 30-Second Summary
**Pattern:** Vertical (column-by-column) scan
**Key insight:** Compare column i across all strings; the first column where any string ends or disagrees is where the prefix stops.
**Go-to:** Vertical scan, O(S) time (S = total chars), O(1) extra space

## Problem
Given an array of strings, return the longest prefix shared by all of them, or an empty string if there is none. [LeetCode](https://leetcode.com/problems/longest-common-prefix/)

**Examples:**
```
Input:  strs = ["flower","flow","flight"]
Output: "fl"
Why:    All three start with "fl"; at index 2 they have o, o, i.

Input:  strs = ["dog","racecar","car"]
Output: ""
Why:    The first letters already differ.
```

**Constraints:**
- 1 ≤ number of strings ≤ 200; 0 ≤ each length ≤ 200.
- Lowercase letters only. Empty strings are allowed, which forces "".

## Hints
<details><summary>Hint 1</summary>
The answer can't be longer than the shortest string.
</details>
<details><summary>Hint 2</summary>
Check character position 0 in every string, then position 1, and so on.
</details>
<details><summary>Hint 3</summary>
Use the first string as the reference; stop at the first index where some string is too short or has a different char.
</details>

## Clarifying Questions
- Can the array be empty? (Not here: at least one string.)
- Can strings be empty? (Yes, then the answer is "".)
- Character set? (Lowercase.)

## Example Walkthrough
`strs = ["flower","flow","flight"]`
- Column 0: f, f, f. Column 1: l, l, l. Column 2: o, o, i: mismatch.
- Prefix = first 2 chars of "flower" = "fl".

## Approaches

### 1. Horizontal Scan: O(S) time, O(1) extra space
Start with prefix = strs[0]; for each next string, shrink the prefix until the string starts with it. Simple, but can do extra work when an early string is long.

### 2. Sort, Compare First and Last: O(S log n) time, O(1) extra space
After sorting, the first and last strings are the most different; their common prefix is everyone's. Neat trick, slower.

### 3. Vertical Scan ⭐ Go-to: O(S) time, O(1) extra space
For each index i of strs[0], check every other string at i. Stop on a mismatch or when a string runs out.
**Why it's the go-to:** stops as early as possible (at the first bad column) and the code is tiny.

## Dry Run (Approach 3)
`strs = ["flower","flow","flight"]`

| i | strs[0][i] | "flow"[i] | "flight"[i] | result |
|---|------------|-----------|-------------|--------|
| 0 | f | f | f | continue |
| 1 | l | l | l | continue |
| 2 | o | o | i | mismatch, return "fl" |

## Edge Case Check
- One string: the whole string. ✅
- An empty string in the list: column 0 fails immediately, "". ✅
- One string is a prefix of another, `["ab","a"]`: "a" runs out at i = 1, answer "a". ✅

## ⚠️ Pitfalls
- **Reading past a shorter string:** check `i < len(s)` before `s[i]` (C++ `s[i]` at `i == size()` returns '\0', so it fails by luck; don't rely on it).
- **Forgetting the all-match case:** if the loop finishes, the whole first string is the prefix.
- **Python `os.path.commonprefix`** exists but don't reach for it in an interview.

## 🎯 What the Interviewer Wants
- A correct, bug-free scan with tight bounds.
- Mention the trie approach if asked about many queries.

## Follow-ups
- **Many queries for the LCP of different subsets:** build a trie: [LC 0208 Implement Trie (Prefix Tree)](../../08-tries/0208-implement-trie-prefix-tree/)
- **Divide and conquer:** LCP(left half) with LCP(right half), O(S) time, O(m log n) stack.
- **Binary search on the prefix length** with an "all start with prefix of length L?" check.
