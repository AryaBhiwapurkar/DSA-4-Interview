---
number: 772
title: Basic Calculator III
difficulty: Hard
topic: Stack
pattern: 0227's stack + recursion for parentheses
link: https://leetcode.com/problems/basic-calculator-iii/
lists: [Interview Extras]
followup_of: ["0227 Basic Calculator II", "0224 Basic Calculator"]
related: ["0224 Basic Calculator", "0227 Basic Calculator II", "0150 Evaluate Reverse Polish Notation"]
---

# 0772. Basic Calculator III

## ⚡ 30-Second Summary
**Pattern:** Treat a parenthesised group as one number, computed recursively
**Key insight:** Basic Calculator II already handles + − * / precedence with a previous-operator stack. Parentheses only add one rule. On `(`, recursively evaluate up to the matching `)` and use the result as `num`. On `)`, flush the pending operator and return to the caller. Pass a shared index so the outer call resumes right after the `)`.
**Go-to:** Recursive previous-operator stack, O(n) time, O(n) space (recursion depth plus stacks)

## Problem
Evaluate an expression with non-negative integers, + − * /, parentheses and spaces. Integer division truncates toward zero, the expression is valid, and eval-style built-ins aren't allowed. LeetCode Premium. [LeetCode](https://leetcode.com/problems/basic-calculator-iii/)

**Examples:**
```
Input:  s = "1+1"
Output: 2
Why:    Plain addition.

Input:  s = "6-4/2"
Output: 4
Why:    Division first: 6 - 2.

Input:  s = "2*(5+5*2)/3+(6/2+8)"
Output: 21
Why:    The groups give 15 and 11; 2*15/3 = 10; 10 + 11 = 21.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; valid expression; intermediate results fit in a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
Can you solve it without parentheses first? (That's 227.)
</details>
<details><summary>Hint 2</summary>
From the outside, a parenthesised group behaves like a single number. How do you get that number?
</details>
<details><summary>Hint 3</summary>
eval(i): run 227's loop; if c == '(' then num = eval(i+1) and continue after the matching ')'; if c == ')' or the end, flush the pending operator and return (sum, index).
</details>

## Clarifying Questions
- Unary minus? (No; LC 772 guarantees none.)
- Division rounding? (Toward zero.)
- Spaces? (Anywhere; skip them.)

## Example Walkthrough
`"2*(5+5*2)/3"`: 2 is pending with op '*'. The `(` recurses: 5 + 5*2 → returns 15 at the `)`. Back outside, num = 15, and the next operator '/' flushes '*': top = 2·15 = 30. Then 3 with op '/' gives 30/3 = 10.

## Approaches

### 1. Two Stacks (Shunting-yard): O(n) time, O(n) space
A value stack and an operator stack. Pop and apply while the top operator has precedence ≥ the incoming one; `(` and `)` act as barriers. It's general and handles more operators, but has more moving parts.

### 2. Recursive Previous-operator Stack ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** it's literally 227 plus two lines for parentheses, which makes it easy to write correctly under pressure.

## Dry Run (Approach 2)
`"2*(5+5*2)/3+(6/2+8)"` (outer call)

| token | num | op flushed | stack |
|-------|-----|------------|-------|
| 2 | 2 | – | [] |
| * | | '+' push 2 | [2] |
| ( … ) | 15 (recursive) | – | |
| / | | '*' top·15 | [30] |
| 3 | 3 | | |
| + | | '/' 30/3 | [10] |
| ( … ) | 11 (recursive: 6/2 + 8) | | |
| end | | '+' push 11 | [10,11] |

Sum **21**.

## Edge Case Check
- Nested parentheses `"((2))"` → 2. ✅
- A group first `"(1+2)*3"` → 9. ✅
- Division of a negative group `"(0-3)/2"` → −1 (truncation). ✅

## ⚠️ Pitfalls
- **Not returning the index** from the recursive call: the outer loop re-reads the inside of the group.
- **Python `//`** floors negatives. Use `int(a / b)`.
- **Applying the operator when you see `(`:** the group's value is the operand, so apply only when the next operator or `)` arrives.

## 🎯 What the Interviewer Wants
- Reuse 227 and treat a group as an operand.
- Correct index passing, or a clean two-stack implementation.
- Truncation semantics.

## Follow-ups
- **Only + − and parentheses:** [LC 0224 Basic Calculator](../0224-basic-calculator/)
- **No parentheses:** [LC 0227 Basic Calculator II](../0227-basic-calculator-ii/)
- **Variables and expressions:** LC 0770 Basic Calculator IV (not added yet). Polynomial arithmetic, a big step up.
