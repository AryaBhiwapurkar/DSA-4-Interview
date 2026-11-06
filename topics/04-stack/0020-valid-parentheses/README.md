---
number: 20
title: Valid Parentheses
difficulty: Easy
topic: Stack
pattern: Stack matching
link: https://leetcode.com/problems/valid-parentheses/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0022 Generate Parentheses", "0032 Longest Valid Parentheses", "0921 Minimum Add to Make Parentheses Valid", "1249 Minimum Remove to Make Valid Parentheses"]
---

# 0020. Valid Parentheses

## ⚡ 30-Second Summary
**Pattern:** Stack matching
**Key insight:** The most recent unclosed opener is the only one the next closer may close. "Most recent" means LIFO, so a stack of open brackets solves it.
**Go-to:** Stack of openers, O(n) time, O(n) space

## Problem
Given a string made only of `()[]{}`, decide whether every bracket is closed by the same type, in the correct order, and every closer has a matching opener. [LeetCode](https://leetcode.com/problems/valid-parentheses/)

**Examples:**
```
Input:  s = "()"
Output: true
Why:    One pair, opened and closed.

Input:  s = "()[]{}"
Output: true
Why:    Three pairs side by side, each closed before the next opens.

Input:  s = "(]"
Output: false
Why:    The closer type doesn't match the opener.

Input:  s = "([])"
Output: true
Why:    Nesting is fine as long as the inner pair closes first.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴.
- Only the six bracket characters appear.

## Hints
<details><summary>Hint 1</summary>
When you see a closer, which opener must it match: the first one, or a specific other one?
</details>
<details><summary>Hint 2</summary>
The opener it must match is the most recent one that hasn't been closed. What structure gives you "most recent" in O(1)?
</details>
<details><summary>Hint 3</summary>
Push openers. On a closer, the stack must be non-empty and its top must be the matching opener; pop it. At the end the stack must be empty.
</details>

## Clarifying Questions
- Only brackets, or other characters too? (Only brackets.)
- Is the empty string valid? (Yes, but n ≥ 1 here.)
- Does `([)]` count as valid? (No: order matters, not just counts.)

## Example Walkthrough
`s = "([)]"`
- `(` push, `[` push. Stack: `( [`.
- `)` arrives, but the top is `[`. Mismatch, so return false.

Counting brackets per type would wrongly say this is valid (one of each). The stack catches the crossing.

## Approaches

### 1. Repeated Removal: O(n²) time, O(n) space
Keep deleting `()`, `[]`, `{}` substrings until nothing changes. Valid iff the string becomes empty. Correct but each pass is O(n) and there can be n/2 passes.

### 2. Stack ⭐ Go-to: O(n) time, O(n) space
Push openers; on a closer, check and pop the top. Valid iff no mismatch and the stack ends empty.
**Why it's the go-to:** one pass, a few lines, and it's the canonical stack problem.

## Dry Run (Approach 2)
`s = "{[]}("`

| i | char | action | stack after |
|---|------|--------|-------------|
| 0 | `{` | push | `{` |
| 1 | `[` | push | `{ [` |
| 2 | `]` | top `[` matches, pop | `{` |
| 3 | `}` | top `{` matches, pop | (empty) |
| 4 | `(` | push | `(` |
| end | | stack not empty | **false** |

## Edge Case Check
- `"]"`: closer with an empty stack, false. ✅
- `"(("`: no mismatch, but the stack isn't empty, false. ✅
- `"([)]"`: crossing pairs, false. ✅
- Odd length: always false (a quick early exit, optional).

## ⚠️ Pitfalls
- **Forgetting the final `empty()` check**: `"(("` would pass.
- **Popping or reading the top of an empty stack**: undefined behaviour in C++ (`st.top()` on empty), IndexError in Python, panic in Go.
- **Counting per type instead of a stack**: misses `([)]`.
- **C++ `match[c]` on an opener** inserts a default entry. Check `count(c)` first.

## 🎯 What the Interviewer Wants
- Recognize LIFO immediately and explain why the latest opener matters.
- Clean closer-to-opener map instead of a chain of ifs.
- Both failure modes: mismatch/empty-stack on a closer, and leftovers at the end.

## Follow-ups
- **Generate all valid strings of n pairs:** [LC 0022 Generate Parentheses](../0022-generate-parentheses/)
- **Longest valid substring:** stack of indices: LC 0032 Longest Valid Parentheses (not added yet)
- **Min insertions to make it valid (one type):** a counter instead of a stack: LC 0921 Minimum Add to Make Parentheses Valid (not added yet)
- **Min removals to make it valid, with letters present:** LC 1249 Minimum Remove to Make Valid Parentheses (not added yet)
- **Only one bracket type?** A single counter that must never go negative replaces the stack, O(1) space.
