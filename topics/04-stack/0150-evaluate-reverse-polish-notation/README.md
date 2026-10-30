---
number: 150
title: Evaluate Reverse Polish Notation
difficulty: Medium
topic: Stack
pattern: Operand stack
link: https://leetcode.com/problems/evaluate-reverse-polish-notation/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0224 Basic Calculator", "0227 Basic Calculator II", "0020 Valid Parentheses"]
---

# 0150. Evaluate Reverse Polish Notation

## ⚡ 30-Second Summary
**Pattern:** Operand stack
**Key insight:** In postfix, an operator always applies to the two most recent values not yet consumed. Push numbers; on an operator, pop two, push the result.
**Go-to:** Stack, O(n) time, O(n) space

## Problem
Evaluate an arithmetic expression given as tokens in Reverse Polish (postfix) notation, with `+ - * /` on integers. Division truncates toward zero. The expression is always valid, with no division by zero.

**Examples:**
```
Input:  tokens = ["2","1","+","3","*"]
Output: 9
Why:    (2 + 1) * 3.

Input:  tokens = ["4","13","5","/","+"]
Output: 6
Why:    13 / 5 = 2 (truncated), then 4 + 2.

Input:  tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Why:    9+3 = 12, 12 * -11 = -132, 6 / -132 = 0 (toward zero), 10 * 0 = 0,
        then + 17 + 5.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; tokens are operators or integers in [-200, 200].
- Every intermediate result fits in a 32-bit int.
- The expression is valid.

## Hints
<details><summary>Hint 1</summary>
When you read an operator, which two numbers does it apply to?
</details>
<details><summary>Hint 2</summary>
They're the two most recently produced values that haven't been used yet. That's LIFO.
</details>
<details><summary>Hint 3</summary>
Push numbers. On an operator, pop b (top) then a, push a op b. Order matters for `-` and `/`. The answer is the single value left.
</details>

## Clarifying Questions
- Is the expression always valid? (Yes.)
- How does division round? (Toward zero, so -7/2 = -3, not -4.)
- Can tokens be negative numbers like "-11"? (Yes. Don't treat them as operators.)

## Example Walkthrough
`["4","13","5","/","+"]`
- Push 4, 13, 5. Stack: 4 13 5.
- `/`: pop b=5, a=13, push 13/5 = 2. Stack: 4 2.
- `+`: pop 2 and 4, push 6. The answer is 6.

## Approaches

### 1. Repeated Collapse: O(n²) time, O(n) space
Find the first operator, replace it and its two preceding numbers with the result, repeat. Each collapse shifts the array.

### 2. Stack ⭐ Go-to: O(n) time, O(n) space
One pass with an operand stack.
**Why it's the go-to:** it's what postfix was designed for; one pass, no parsing tricks.

## Dry Run (Approach 2)
`["10","6","9","3","+","-11","*","/","*","17","+","5","+"]`

| token | action | stack after |
|-------|--------|-------------|
| 10, 6, 9, 3 | push | 10 6 9 3 |
| + | 9 + 3 | 10 6 12 |
| -11 | push (a number, not `-`) | 10 6 12 -11 |
| * | 12 * -11 | 10 6 -132 |
| / | 6 / -132 = 0 (toward zero) | 10 0 |
| * | 10 * 0 | 0 |
| 17, + | 0 + 17 | 17 |
| 5, + | 17 + 5 | **22** |

## Edge Case Check
- Single number `["18"]`: return 18. ✅
- Negative division `["4","-3","/"]`: -1, not -2 (Python `//` would give -2). ✅
- Negative literal "-11": length > 1, so it's a number. ✅

## ⚠️ Pitfalls
- **Operand order**: the first pop is the right operand. `a - b`, not `b - a`.
- **Python `//` floors** (-4 // 3 == -2). Use `int(a / b)` to truncate toward zero.
- **Detecting operators by first char** misreads "-11". Check the whole token.
- **C++ `stoi` / Go `strconv.Atoi`** for parsing; Go's Atoi returns an error you must handle or discard.

## 🎯 What the Interviewer Wants
- Immediately map postfix to a stack.
- Correct operand order and truncating division.
- Know the link to infix: the shunting-yard algorithm converts infix to postfix.

## Follow-ups
- **Infix with +, -, parentheses:** [LC 0224 Basic Calculator](../0224-basic-calculator/)
- **Infix with + - * / (precedence, no parens):** LC 0227 Basic Calculator II (not added yet)
- **Prefix (Polish) notation:** scan right to left with the same stack.
- **Build the expression tree:** the same stack, but push nodes instead of values.
