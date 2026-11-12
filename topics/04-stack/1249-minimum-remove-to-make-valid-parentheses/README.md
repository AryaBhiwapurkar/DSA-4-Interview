---
number: 1249
title: Minimum Remove to Make Valid Parentheses
difficulty: Medium
topic: Stack
pattern: Stack of unmatched '(' indices + mark unmatched ')'
link: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
lists: [Interview Extras]
followup_of: ["0020 Valid Parentheses"]
related: ["0921 Minimum Add to Make Parentheses Valid", "0032 Longest Valid Parentheses", "0301 Remove Invalid Parentheses"]
---

# 1249. Minimum Remove to Make Valid Parentheses

## ⚡ 30-Second Summary
**Pattern:** Find the unmatched brackets, delete exactly those
**Key insight:** Scan left to right. Push the index of each `(`. A `)` either pops a match or, with an empty stack, is unmatched and gets marked for removal. At the end, every index still on the stack is an unmatched `(`, so mark those too. Every unmatched bracket must go and every matched one can stay, so this is the minimum number of removals.
**Go-to:** Index stack + removal set, O(n) time, O(n) space

## Problem
The string has lowercase letters plus `(` and `)`. Remove as few parentheses as possible so the result is valid, and return any such result. [LeetCode](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/)

**Examples:**
```
Input:  s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Why:    The final ')' has no partner. ("lee(t(co)de)" is also accepted.)

Input:  s = "a)b(c)d"
Output: "ab(c)d"
Why:    The first ')' comes before any '('.

Input:  s = "))(("
Output: ""
Why:    None of the four brackets can be matched.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; letters are kept untouched.

## Hints
<details><summary>Hint 1</summary>
Which brackets must be removed no matter what?
</details>
<details><summary>Hint 2</summary>
A ')' with no earlier unmatched '(' can never be matched. What about '(' that are left over at the end?
</details>
<details><summary>Hint 3</summary>
Stack of '(' indices. ')' with an empty stack → mark i. ')' otherwise → pop. After the scan, mark every index left on the stack. Build the string without the marked indices.
</details>

## Clarifying Questions
- Any valid answer accepted? (Yes.)
- Do letters stay? (Yes, untouched.)
- Empty result allowed? (Yes.)

## Example Walkthrough
`"a)b(c)d"`: ')' at 1 has an empty stack → mark 1. '(' at 3 is pushed. ')' at 5 pops 3. The stack ends empty. Remove index 1 → "ab(c)d".

## Approaches

### 1. Two Passes with a Counter: O(n) time, O(n) space
Left to right, drop each `)` that would push the balance below 0. Then right to left, drop the extra `(`. Neat, but it builds two intermediate strings.

### 2. Index Stack + Removal Set ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** one scan plus one build, and the "unmatched = must remove" argument is the whole proof.

## Dry Run (Approach 2)
`"lee(t(c)o)de)"`

| i | ch | action | stack | remove |
|---|----|--------|-------|--------|
| 3 | ( | push | [3] | {} |
| 5 | ( | push | [3,5] | |
| 7 | ) | pop 5 | [3] | |
| 9 | ) | pop 3 | [] | |
| 12 | ) | empty → mark | [] | {12} |

Result **"lee(t(c)o)de"**.

## Edge Case Check
- No brackets → unchanged. ✅
- All unmatched → letters only (or ""). ✅
- Already valid → unchanged. ✅

## ⚠️ Pitfalls
- **Forgetting the leftover `(`** at the end of the scan.
- **Erasing characters while scanning** shifts indices and costs O(n) each.
- **C++ `string += char` in a loop** is fine (amortised O(1)); avoid `insert` at the front.

## 🎯 What the Interviewer Wants
- Identify exactly which brackets are unmatched.
- An O(n) build of the result.
- A minimality argument.

## Follow-ups
- **Count additions instead of removals:** [LC 0921 Minimum Add to Make Parentheses Valid](../0921-minimum-add-to-make-parentheses-valid/)
- **All minimal results, not just one:** LC 0301 Remove Invalid Parentheses (not added yet). BFS or DFS over removals.
- **Longest valid substring:** [LC 0032 Longest Valid Parentheses](../0032-longest-valid-parentheses/)
