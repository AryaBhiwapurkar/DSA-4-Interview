---
number: 921
title: Minimum Add to Make Parentheses Valid
difficulty: Medium
topic: Stack
pattern: Balance counter (stack collapsed to an int)
link: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
lists: [Interview Extras]
followup_of: ["0020 Valid Parentheses"]
related: ["1249 Minimum Remove to Make Valid Parentheses", "0020 Valid Parentheses", "1541 Minimum Insertions to Balance a Parentheses String"]
---

# 0921. Minimum Add to Make Parentheses Valid

## ⚡ 30-Second Summary
**Pattern:** Count unmatched opens and unmatched closes in one scan
**Key insight:** With a single bracket type, the stack only ever holds `(`, so an integer `open` can replace it. A `)` with open > 0 matches; otherwise it's unmatched and needs one inserted `(` before it (`add++`). At the end, each leftover open needs a `)`. Answer = add + open.
**Go-to:** Two counters, O(n) time, O(1) space

## Problem
Return the minimum number of `(` or `)` insertions, at any positions, that make a parentheses string valid. [LeetCode](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/)

**Examples:**
```
Input:  s = "())"
Output: 1
Why:    The second ')' needs a partner '('.

Input:  s = "((("
Output: 3
Why:    Each '(' needs a ')'.
```

**Constraints:**
- 1 ≤ n ≤ 1000; only '(' and ')'.

## Hints
<details><summary>Hint 1</summary>
Each unmatched bracket needs exactly one insertion. How do you count the unmatched ones?
</details>
<details><summary>Hint 2</summary>
With one bracket type, what does the stack actually store? Could a number replace it?
</details>
<details><summary>Hint 3</summary>
open = add = 0. '(' → open++. ')' → if open: open−− else add++. Return add + open.
</details>

## Clarifying Questions
- Insertions anywhere? (Yes.)
- Only one bracket type? (Yes; with several types you'd need a real stack.)
- Count only? (Yes.)

## Example Walkthrough
`")(("`: ')' with open 0 → add 1. '(' twice → open 2. Total 1 + 2 = 3.

## Approaches

### 1. Remove Matched Pairs Repeatedly: O(n²) time
Delete "()" substrings until none remain; the leftover length is the answer. Simple, but slow.

### 2. Stack: O(n) time, O(n) space
Push '(', pop on a matching ')', count the unmatched ')'. The answer is the stack size plus that count.

### 3. Two Counters ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** the stack collapses to a number, which is the observation the interviewer is looking for.

## Dry Run (Approach 3)
`"())"`

| ch | open | add |
|----|------|-----|
| ( | 1 | 0 |
| ) | 0 | 0 |
| ) | 0 | 1 |

Answer 1 + 0 = **1**.

## Edge Case Check
- Already valid → 0. ✅
- `")))"` → 3. ✅
- `"((("` → 3. ✅

## ⚠️ Pitfalls
- **Returning |opens − closes|:** wrong for `")("` (that gives 0; the answer is 2).
- **Letting `open` go negative** instead of counting an insertion.

## 🎯 What the Interviewer Wants
- Reduce the stack to a counter.
- Order matters, so the |difference| shortcut fails.

## Follow-ups
- **Removals instead of insertions, return the string:** [LC 1249 Minimum Remove to Make Valid Parentheses](../1249-minimum-remove-to-make-valid-parentheses/)
- **Each '(' needs "))":** LC 1541 Minimum Insertions to Balance a Parentheses String (not added yet)
