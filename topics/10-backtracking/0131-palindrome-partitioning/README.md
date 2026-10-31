---
number: 131
title: Palindrome Partitioning
difficulty: Medium
topic: Backtracking
pattern: Backtrack on cut points
link: https://leetcode.com/problems/palindrome-partitioning/
lists: [NeetCode 150]
followup_of: []
related: ["0132 Palindrome Partitioning II", "0005 Longest Palindromic Substring", "0647 Palindromic Substrings", "0093 Restore IP Addresses"]
---

# 0131. Palindrome Partitioning

## ⚡ 30-Second Summary
**Pattern:** Backtracking over where to cut next
**Key insight:** From position `start`, the next piece is `s[start..end]` for some end. Only recurse when that piece is a palindrome; when `start` reaches the end of the string, the pieces so far are a valid partition.
**Go-to:** Backtracking with an inline palindrome check, O(n · 2ⁿ) time, O(n) extra space

## Problem
Split a string into pieces so that every piece reads the same backwards, and return every such split. Any order. [LeetCode](https://leetcode.com/problems/palindrome-partitioning/)

**Examples:**
```
Input:  s = "aab"
Output: [["a","a","b"],["aa","b"]]
Why:    Single letters always work; "aa" is the only longer palindrome piece.

Input:  s = "a"
Output: [["a"]]
Why:    One letter, one way.
```

**Constraints:**
- 1 ≤ n ≤ 16, lowercase letters. A string of n equal letters has 2ⁿ⁻¹ partitions, so exponential output is possible.

## Hints
<details><summary>Hint 1</summary>
Think of the gaps between letters: each gap is cut or not. Which cut patterns are valid?
</details>
<details><summary>Hint 2</summary>
Choose the first piece, then solve the rest the same way. Which first pieces are allowed?
</details>
<details><summary>Hint 3</summary>
`dfs(start)`: if start == n, save. For end from start to n-1: if s[start..end] is a palindrome, push it, `dfs(end+1)`, pop.
</details>

## Clarifying Questions
- Are single characters palindromes? (Yes, so a partition always exists.)
- Output order? (Any.)

## Example Walkthrough
"aab": first piece "a" → rest "ab" → "a" then "b" gives [a,a,b]; "ab" isn't a palindrome. First piece "aa" → rest "b" gives [aa,b]. "aab" isn't a palindrome.

## Approaches

### 1. Backtracking + Inline Check ⭐ Go-to: O(n · 2ⁿ) time, O(n) extra space
Try every end for the next piece and check it with two pointers before recursing.
**Why it's the go-to:** short, clearly correct, and within limits for n ≤ 16.

### 2. Backtracking + Precomputed Palindrome Table: O(n · 2ⁿ) time, O(n²) space
Fill `pal[i][j]` first (`s[i] == s[j] && (j - i < 2 || pal[i+1][j-1])`, i descending), so each check is O(1). Same worst case, faster in practice; mention it as the optimization.

## Dry Run (Approach 1)
`s = "aab"`

| start | path before | end | piece | palindrome? | action |
|-------|-------------|-----|-------|-------------|--------|
| 0 | [] | 0 | a | yes | recurse(1) |
| 1 | [a] | 1 | a | yes | recurse(2) |
| 2 | [a,a] | 2 | b | yes | recurse(3): save **[a,a,b]** |
| 1 | [a] | 2 | ab | no | skip |
| 0 | [] | 1 | aa | yes | recurse(2) |
| 2 | [aa] | 2 | b | yes | recurse(3): save **[aa,b]** |
| 0 | [] | 2 | aab | no | skip, done |

## Edge Case Check
- One letter: [[s]]. ✅
- All the same letter ("aaa"): 4 partitions = 2². ✅
- Whole string a palindrome ("efe"): [e,f,e] and [efe]. ✅

## ⚠️ Pitfalls
- **Substring end off-by-one**: C++ `s.substr(start, end - start + 1)` takes a length, not an end index.
- **Rebuilding substrings just to test them**: check with indices first, build the piece only if it passes.
- **DP table filled in the wrong order**: `pal[i][j]` needs `pal[i+1][j-1]`, so i must go from n-1 down.

## 🎯 What the Interviewer Wants
- Frame it as "choose the next cut" backtracking.
- Know the precomputed table as an optimization.

## Follow-ups
- **Minimum number of cuts:** LC 0132 Palindrome Partitioning II, a 1-D DP over the pal table (not added yet)
- **Longest palindromic substring:** [LC 0005 Longest Palindromic Substring](../../13-1d-dp/0005-longest-palindromic-substring/)
- **Same "cut points" backtracking with other rules:** LC 0093 Restore IP Addresses (not added yet)
