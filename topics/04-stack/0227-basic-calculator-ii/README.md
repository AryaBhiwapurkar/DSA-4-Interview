---
number: 227
title: Basic Calculator II
difficulty: Medium
topic: Stack
pattern: Stack of signed terms, apply * and / immediately
link: https://leetcode.com/problems/basic-calculator-ii/
lists: [Interview Extras]
followup_of: []
related: ["0224 Basic Calculator", "0772 Basic Calculator III", "0150 Evaluate Reverse Polish Notation"]
---

# 0227. Basic Calculator II

## ⚡ 30-Second Summary
**Pattern:** Remember the previous operator; finish each number when the next operator (or the end) arrives
**Key insight:** + and − start a new term, while * and / modify the current one. Read digits into `num`. When you reach an operator or the end, apply the **previous** operator: + pushes num, − pushes −num, * and / replace the top with `top op num` (truncating toward zero). The answer is the sum of the stack. That can be squeezed into O(1) space by keeping only `last` and `total`.
**Go-to:** Previous-operator stack, O(n) time, O(n) space (O(1) variant mentioned)

## Problem
Evaluate an expression string with non-negative integers, +, −, *, / and spaces. There are no parentheses. Integer division truncates toward zero, and eval-style built-ins are not allowed. [LeetCode](https://leetcode.com/problems/basic-calculator-ii/)

**Examples:**
```
Input:  s = "3+2*2"
Output: 7
Why:    Multiplication first: 3 + 4.

Input:  s = " 3/2 "
Output: 1
Why:    Integer division truncates 1.5 to 1.

Input:  s = " 3+5 / 2 "
Output: 5
Why:    5 / 2 = 2, then 3 + 2.
```

**Constraints:**
- 1 ≤ n ≤ 3·10⁵; the expression is valid; all results fit in a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
Which operators bind tighter, and how could you evaluate them as soon as you see their second operand?
</details>
<details><summary>Hint 2</summary>
When you finish reading a number, you know the operator before it. What should + − * / each do with it?
</details>
<details><summary>Hint 3</summary>
op = '+'. For each char (and once more at the end): build num from digits; on an operator or the end, apply op: '+' push num, '−' push −num, '*' top *= num, '/' top = trunc(top / num); then op = this char, num = 0. Answer = sum(stack).
</details>

## Clarifying Questions
- Parentheses? (No; see 224 / 772.)
- Unary minus? (No.)
- Division rounding? (Truncate toward zero.)

## Example Walkthrough
`"14-3/2"`: 14 with op + → [14]. 3 with op − → [14, −3]. 2 with op / → top = trunc(−3 / 2) = −1 → [14, −1]. Sum 13. (Truncation toward zero matters here: floor would give −2.)

## Approaches

### 1. Two Passes (Tokens, then Precedence): O(n) time, O(n) space
Tokenise; collapse * and / left to right into a new list; then sum the + and − terms. Clear but verbose.

### 2. Stack with Previous Operator ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** one pass, four cases, and it extends naturally to parentheses (772).

(An O(1) space variant keeps `last` (the current term) and `total` instead of a stack: on + or −, add last to total and start a new term.)

## Dry Run (Approach 2)
`" 3+5 / 2 "`

| char | num | op applied | stack |
|------|-----|------------|-------|
| 3 | 3 | – | [] |
| + | 3 | '+' push 3 | [3] |
| 5 | 5 | – | |
| / | 5 | '+' push 5 | [3,5] |
| 2 | 2 | – | |
| end | 2 | '/' 5/2 = 2 | [3,2] |

Sum **5**.

## Edge Case Check
- A single number `"42"` → 42. ✅
- Spaces everywhere → skipped. ✅
- Negative intermediate with / → truncation toward zero. ✅

## ⚠️ Pitfalls
- **Python `//` floors:** −3 // 2 = −2. Use `int(a / b)` (or handle the sign) to truncate.
- **Forgetting the last number:** apply the pending operator at the end of the string.
- **Treating spaces as operators:** only trigger on + − * / or the end.
- **Multi-digit numbers:** accumulate `num = num·10 + d`.

## 🎯 What the Interviewer Wants
- Precedence handled in one pass.
- Correct truncation semantics.
- Optional: the O(1)-space version.

## Follow-ups
- **Parentheses with + and − only:** [LC 0224 Basic Calculator](../0224-basic-calculator/)
- **All four operators plus parentheses:** [LC 0772 Basic Calculator III](../0772-basic-calculator-iii/)
- **Postfix input:** [LC 0150 Evaluate Reverse Polish Notation](../0150-evaluate-reverse-polish-notation/)
