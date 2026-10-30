---
number: 224
title: Basic Calculator
difficulty: Hard
topic: Stack
pattern: Stack for sign/paren context
link: https://leetcode.com/problems/basic-calculator/
lists: [LC Top Interview 150]
followup_of: []
related: ["0150 Evaluate Reverse Polish Notation", "0227 Basic Calculator II", "0772 Basic Calculator III", "0020 Valid Parentheses"]
---

# 0224. Basic Calculator

## ⚡ 30-Second Summary
**Pattern:** Stack for sign/paren context
**Key insight:** With only `+`, `-` and parentheses, every number ends up added with a sign of ±1. Keep a running `result` and the `sign` of the next number. On `(`, save (result, sign) on a stack and start fresh; on `)`, finish the inner result, multiply by the saved sign, add to the saved result.
**Go-to:** Iterative stack of (result, sign), O(n) time, O(n) space

## Problem
Evaluate a valid expression string containing non-negative integers, `+`, `-`, parentheses and spaces. `-` can be unary (`-(2+3)`, `1-(-2)`), but `+` is never unary. No `eval`.

**Examples:**
```
Input:  s = "1 + 1"
Output: 2
Why:    Plain addition; spaces are ignored.

Input:  s = " 2-1 + 2 "
Output: 3
Why:    Left to right: 2 - 1 = 1, then + 2.

Input:  s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
Why:    Inner (4+5+2) = 11, so the first group is 1 + 11 - 3 = 9. Then 9 + 14.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁵, so recursion depth could be large on deep nesting (iterative is safer).
- Every number and intermediate result fits in a 32-bit int.
- The expression is valid.

## Hints
<details><summary>Hint 1</summary>
Without parentheses, how would you evaluate "1 - 2 + 3" in one pass?
</details>
<details><summary>Hint 2</summary>
Track `result` and the `sign` (+1/-1) to apply to the next number. A parenthesized group is just a "number" whose value you compute first.
</details>
<details><summary>Hint 3</summary>
On `(`: push result and sign, reset result = 0, sign = 1. On `)`: flush the pending number, then result = popped_result + popped_sign × result.
</details>

## Clarifying Questions
- Which operators? (Only `+` and `-`; no `*` or `/`.)
- Is unary minus allowed? (Yes, before a number or a parenthesis. Unary plus, no.)
- Can I use eval? (No.)
- Multi-digit numbers? (Yes, parse them fully.)

## Example Walkthrough
`"1-(     -2)"`
- 1 → pending number. `-`: result = 1, sign = -1.
- `(`: push (1, -1), reset result 0, sign +1.
- `-`: result += 0, sign = -1. Then 2 pending.
- `)`: result = 0 + (-1)(2) = -2. Pop: result = 1 + (-1)(-2) = 3.

## Approaches

### 1. Recursive Descent: O(n) time, O(depth) space
Parse left to right; on `(` call the parser recursively and treat its return value as a number; on `)` return. Elegant, but deep nesting (n up to 3·10⁵) risks stack overflow.

### 2. Stack of (result, sign) ⭐ Go-to: O(n) time, O(depth) space
Same logic, but saves the outer context explicitly instead of on the call stack.
**Why it's the go-to:** no recursion limit, and the state (result, sign, num) is small and easy to explain.

## Dry Run (Approach 2)
`"(1+(4+5+2)-3)+(6+8)"` (num is flushed into result on each operator or `)`)

| char | action | result | sign | stack |
|------|--------|--------|------|-------|
| ( | push (0,+1), reset | 0 | + | (0,+) |
| 1, + | result += 1 | 1 | + | (0,+) |
| ( | push (1,+1), reset | 0 | + | (0,+) (1,+) |
| 4+5+2 | result = 11 | 11 | + | (0,+) (1,+) |
| ) | 1 + (+1)·11 | 12 | + | (0,+) |
| -, 3 | 12 - 3 | 9 | - | (0,+) |
| ) | 0 + (+1)·9 | 9 | + | |
| +, ( | push (9,+1), reset | 0 | + | (9,+) |
| 6+8, ) | 9 + 14 | 23 | + | |

## Edge Case Check
- Leading unary minus `"-(2+3)"`: `-` sets sign = -1 with result 0, so -5. ✅
- Unary minus inside parens `"1-(     -2)"`: 3. ✅
- Big single number `"2147483647"`: parsed digit by digit, fits int. ✅
- Spaces everywhere: skipped. ✅

## ⚠️ Pitfalls
- **Forgetting to flush the last number** after the loop: `result + sign * num`.
- **Not resetting num to 0** after adding it.
- **Order of pops on `)`**: the sign is pushed after the result, so pop the sign first.
- **Parsing digit by digit** in Python with `int(c)` is fine; in C++ use `c - '0'`. Watch `num * 10` overflow if constraints weren't guaranteed (use `long long`).

## 🎯 What the Interviewer Wants
- Recognize that `+/-` only expressions reduce to "signed sum of numbers".
- Clean handling of unary minus without special cases.
- Explain why the iterative stack is safer than recursion for deep nesting.

## Follow-ups
- **Add * and / (precedence, no parens):** keep the last term separate: LC 0227 Basic Calculator II (not added yet)
- **All four operators + parens:** recursion or two stacks (shunting-yard): LC 0772 Basic Calculator III (not added yet)
- **Postfix input:** [LC 0150 Evaluate Reverse Polish Notation](../0150-evaluate-reverse-polish-notation/)
