---
number: 32
title: Longest Valid Parentheses
difficulty: Hard
topic: Stack
pattern: Stack of indices with a base marker (or two-direction counters)
link: https://leetcode.com/problems/longest-valid-parentheses/
lists: [Interview Extras]
followup_of: ["0020 Valid Parentheses"]
related: ["0020 Valid Parentheses", "1249 Minimum Remove to Make Valid Parentheses", "0678 Valid Parenthesis String"]
---

# 0032. Longest Valid Parentheses

## ⚡ 30-Second Summary
**Pattern:** Keep the index of the last unmatched position at the bottom of the stack
**Key insight:** Push −1 first as a "base". Push the index of every `(`. On `)`, pop. If the stack is now empty, this `)` is unmatched, so push its index as the new base. Otherwise the current valid run started right after the new top, so its length is `i − top`. The base trick handles back-to-back valid runs like "()()" without extra bookkeeping.
**Go-to:** Index stack with base, O(n) time, O(n) space (mention the O(1) two-pass counters)

## Problem
Given a string of `(` and `)`, return the length of the longest contiguous substring that is well-formed (balanced and properly nested). [LeetCode](https://leetcode.com/problems/longest-valid-parentheses/)

**Examples:**
```
Input:  s = "(()"
Output: 2
Why:    "()" at the end; the first '(' is never closed.

Input:  s = ")()())"
Output: 4
Why:    "()()" in the middle.

Input:  s = ""
Output: 0
Why:    Empty string, no valid substring.
```

**Constraints:**
- 0 ≤ n ≤ 3·10⁴, so checking every substring is far too slow.

## Hints
<details><summary>Hint 1</summary>
A stack matches each ')' with its '('. What extra index would tell you where the current valid run started?
</details>
<details><summary>Hint 2</summary>
Keep indices, not characters. When a ')' has nothing to match, what does that mean for every later run?
</details>
<details><summary>Hint 3</summary>
st = [−1]. '(' → push i. ')' → pop; if empty, push i (new base); else best = max(best, i − st.top).
</details>

## Clarifying Questions
- Only '(' and ')'? (Yes.)
- Substring, not subsequence? (Yes, contiguous.)
- Empty input? (0.)

## Example Walkthrough
`")()())"`: st = [−1]. i0 ')' pops −1, so the stack is empty → push 0 as the base. i1 '(' → [0,1]. i2 ')' pops 1 → length 2 − 0 = 2. i3 '(' → [0,3]. i4 ')' → length 4 − 0 = 4. i5 ')' pops 0, empty → push 5. Best 4.

## Approaches

### 1. Check Every Even-length Substring: O(n³) / O(n²) time
Test each substring with a balance counter. Far too slow.

### 2. DP: O(n) time, O(n) space
dp[i] = length of the longest valid substring ending at i. For a `)`:
- If s[i−1] is `(`: dp[i] = dp[i−2] + 2.
- Otherwise, if the character just before the block that ends at i−1 is `(`: dp[i] = dp[i−1] + 2 + dp[before that].

It works, but the indices are fiddly.

### 3. Index Stack with Base ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** five lines, and the base-marker idea is easy to justify.

(O(1) space: scan left to right counting opens and closes. Record 2·closes when they're equal, and reset when closes > opens. Then repeat right to left with the roles swapped, which catches cases like "(()".)

## Dry Run (Approach 3)
`"(()"`

| i | ch | action | stack | best |
|---|----|--------|-------|------|
| – | | init | [−1] | 0 |
| 0 | ( | push 0 | [−1,0] | 0 |
| 1 | ( | push 1 | [−1,0,1] | 0 |
| 2 | ) | pop 1; len 2 − 0 | [−1,0] | **2** |

## Edge Case Check
- `""` → 0. ✅
- `"()()"` → 4 (the base stays −1). ✅
- `"())(())"` → the unmatched ')' at index 2 becomes the base, so the later "(())" gives 4. ✅

## ⚠️ Pitfalls
- **No initial −1:** a valid run starting at index 0 gets the wrong length.
- **Pushing characters instead of indices.**
- **One-direction counters only:** they miss "(()" (opens never drop to equal closes). Scan both ways.

## 🎯 What the Interviewer Wants
- The index stack with a base, plus a clear explanation.
- Optional: the DP and the O(1) two-pass.

## Follow-ups
- **Just validate:** [LC 0020 Valid Parentheses](../0020-valid-parentheses/)
- **Fewest removals to make it valid:** [LC 1249 Minimum Remove to Make Valid Parentheses](../1249-minimum-remove-to-make-valid-parentheses/)
- **Wildcards:** [LC 0678 Valid Parenthesis String](../../15-greedy/0678-valid-parenthesis-string/)
