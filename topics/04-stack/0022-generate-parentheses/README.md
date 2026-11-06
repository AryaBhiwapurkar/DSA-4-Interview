---
number: 22
title: Generate Parentheses
difficulty: Medium
topic: Stack
pattern: Backtracking on open/close counts
link: https://leetcode.com/problems/generate-parentheses/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0020 Valid Parentheses", "0301 Remove Invalid Parentheses", "0078 Subsets"]
---

# 0022. Generate Parentheses

## ⚡ 30-Second Summary
**Pattern:** Backtracking on open/close counts
**Key insight:** A prefix can still become valid iff `open ≤ n` and `close ≤ open`. Only extend with characters that keep that true, so every leaf is a valid answer and no time is wasted on dead branches.
**Go-to:** Backtracking with counts, O(4ⁿ/√n) time (the Catalan number of answers × length n each), O(n) recursion depth

## Problem
Given n, return every string of n pairs of parentheses that is well-formed. Any order is accepted. [LeetCode](https://leetcode.com/problems/generate-parentheses/)

**Examples:**
```
Input:  n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Why:    These are all 5 ways to arrange 3 balanced pairs.

Input:  n = 1
Output: ["()"]
Why:    The only one.
```

**Constraints:**
- 1 ≤ n ≤ 8, so the output is small (C(8) = 1430) but 2¹⁶ blind strings is wasteful.

## Hints
<details><summary>Hint 1</summary>
You could generate all 2²ⁿ strings and filter the valid ones. When does a prefix already doom a string?
</details>
<details><summary>Hint 2</summary>
A prefix is dead if it has more `)` than `(`, or more than n `(`. Can you avoid ever building a dead prefix?
</details>
<details><summary>Hint 3</summary>
Recurse with counts (open, close). Add `(` if open < n. Add `)` if close < open. Record when the length is 2n.
</details>

## Clarifying Questions
- Does output order matter? (No.)
- Range of n? (1 to 8.)
- Only `()`, not multiple bracket types? (Yes, only one type.)

## Example Walkthrough
n = 2. Start "".
- open < 2, so "(". Then "((" (open = 2). Only `)` is allowed now: "(()", "(())" → record.
- Back at "(": try `)` since close < open: "()". Then "()(" and "()()" → record.
- At "" we can't place `)` (close = open = 0). Done: ["(())", "()()"].

## Approaches

### 1. Generate All, Then Filter: O(2²ⁿ · n) time, O(n) depth
Build every string of length 2n from `(` and `)`, keep the ones whose running balance never goes negative and ends at 0.

### 2. Backtracking With Counts ⭐ Go-to: O(4ⁿ/√n) time, O(n) depth
Only add `(` while open < n and `)` while close < open. Every path reaches a valid answer.
**Why it's the go-to:** prunes all invalid work, the code is a 6-line recursion, and the two rules are easy to justify.

## Dry Run (Approach 2)
n = 2

| path | open | close | can add `(`? | can add `)`? | action |
|------|------|-------|--------------|--------------|--------|
| "" | 0 | 0 | yes | no | add ( |
| "(" | 1 | 0 | yes | yes | add ( first |
| "((" | 2 | 0 | no | yes | add ) |
| "(()" | 2 | 1 | no | yes | add ) |
| "(())" | 2 | 2 | | | **record** |
| "()" | 1 | 1 | yes | no | add ( |
| "()(" | 2 | 1 | no | yes | add ) |
| "()()" | 2 | 2 | | | **record** |

## Edge Case Check
- n = 1: ["()"]. ✅
- Output count matches Catalan numbers: 1, 2, 5, 14 for n = 1..4. ✅
- Strings in the output are distinct by construction (each is a distinct path). ✅

## ⚠️ Pitfalls
- **`close < n` instead of `close < open`**: produces `)(`-style invalid strings.
- **Python: building with `path + "("`** is fine (new string each call); with a list, remember to `pop()` after the recursive call.
- **C++: passing the string by value** copies at each level (fine for n ≤ 8); by reference requires `pop_back()` after the call.
- **Go: appending to a shared byte slice** across branches can alias. Convert with `string(path)` when recording.

## 🎯 What the Interviewer Wants
- The two pruning rules and why they're exactly the validity conditions.
- Complexity stated in terms of the Catalan number, not 2²ⁿ.
- Bonus: the closure-number DP: every answer is `(` + A + `)` + B, where A has i pairs and B has n-1-i.

## Follow-ups
- **Check one string:** [LC 0020 Valid Parentheses](../0020-valid-parentheses/)
- **Remove the fewest chars to make valid, all results:** BFS/backtracking: LC 0301 Remove Invalid Parentheses (not added yet)
- **Count only (not list):** the nth Catalan number, C(2n, n)/(n+1), or DP.
- **Multiple bracket types:** add a stack of open types to the state.
