---
number: 678
title: Valid Parenthesis String
difficulty: Medium
topic: Greedy
pattern: Track min/max open count
link: https://leetcode.com/problems/valid-parenthesis-string/
lists: [NeetCode 150]
followup_of: ["0020 Valid Parentheses"]
related: ["0032 Longest Valid Parentheses", "1249 Minimum Remove to Make Valid Parentheses"]
---

# 0678. Valid Parenthesis String

## ⚡ 30-Second Summary
**Pattern:** Greedy over the range of possible open counts
**Key insight:** You don't need to decide what each `*` is. Track `lo` and `hi`, the fewest and most unmatched `(` possible so far. `(` raises both, `)` lowers both, `*` lowers lo and raises hi. If hi < 0, fail. Clamp lo at 0. At the end it's valid iff lo == 0.
**Go-to:** lo/hi counters, O(n) time, O(1) space

## Problem
A string has `(`, `)` and `*`, where each `*` may act as `(`, `)` or nothing. Decide whether some choice makes it a balanced parentheses string. [LeetCode](https://leetcode.com/problems/valid-parenthesis-string/)

**Examples:**
```
Input:  s = "()"
Output: true
Why:    Already balanced.

Input:  s = "(*)"
Output: true
Why:    Treat * as empty.

Input:  s = "(*))"
Output: true
Why:    Treat * as '(' to get "(())".
```

**Constraints:**
- 1 ≤ n ≤ 100, so even the O(n²) memo is fine; O(n) is the expected answer.

## Hints
<details><summary>Hint 1</summary>
Without stars, you'd track a single open count. With stars, the count isn't one number any more. What is it instead?
</details>
<details><summary>Hint 2</summary>
The set of possible open counts is a contiguous range [lo, hi]. How does each character move the ends?
</details>
<details><summary>Hint 3</summary>
'(' → lo++, hi++. ')' → lo--, hi--. '*' → lo--, hi++. If hi < 0 return false; set lo = max(lo, 0). Return lo == 0.
</details>

## Clarifying Questions
- Can `*` be empty? (Yes, plus `(` or `)`.)
- Only these three characters? (Yes.)
- Empty string? (Valid, though n ≥ 1 here.)

## Example Walkthrough
`"*("`: after `*` the range is [0, 1] (lo clamped). After `(` it's [1, 2]. The final lo = 1 means at least one `(` is always left open → false. A star *before* an open paren can't close it.

## Approaches

### 1. Memo on (index, open count): O(n²) time, O(n²) space
Try all three meanings of `*`, pruning when the count goes negative. Direct translation of the rules.

### 2. Two Stacks: O(n) time, O(n) space
Push indices of `(` and `*`. A `)` pops a `(` first, else a `*`. Afterwards, pair each leftover `(` with a later `*` (compare indices).

### 3. Open-count Range ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** constant space and four lines; the "range of possible counts" idea is the key insight interviewers look for.

## Dry Run (Approach 3)
`"(*))"`

| ch | lo | hi | note |
|----|----|----|------|
| ( | 1 | 1 | |
| * | 0 | 2 | |
| ) | -1 → 0 | 1 | clamp |
| ) | -1 → 0 | 0 | clamp |

hi never went negative and the final lo = 0 → **true**. For `"(((*)"` the end state is lo = 1, hi = 3 → false.

## Edge Case Check
- `")*"` → hi = -1 at once → false. ✅
- `"*("` → final lo = 1 → false. ✅
- All stars → lo stays 0 → true. ✅

## ⚠️ Pitfalls
- **Not clamping lo at 0:** a negative minimum would let `)` "borrow" from the future.
- **Checking hi < 0 only at the end** instead of after every character: `")*"` ends with lo = hi = 0 and would wrongly pass.
- **Two stacks:** a leftover `(` must have its matching `*` at a larger index.
- **Counting stars without positions** (e.g. "#( ≤ #) + #*") ignores order.

## 🎯 What the Interviewer Wants
- A correct baseline (memo or stacks), then the lo/hi greedy.
- Explain why clamping is valid (choose a different `*` meaning).
- Order matters: show `"*("`.

## Follow-ups
- **No wildcards:** [LC 0020 Valid Parentheses](../../04-stack/0020-valid-parentheses/)
- **Longest valid substring:** LC 0032 Longest Valid Parentheses (not added yet). Stack of indices or DP.
- **Fewest removals to make it valid:** LC 1249 Minimum Remove to Make Valid Parentheses (not added yet)
