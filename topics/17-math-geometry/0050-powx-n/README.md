---
number: 50
title: Pow(x, n)
difficulty: Medium
topic: Math & Geometry
pattern: Fast exponentiation
link: https://leetcode.com/problems/powx-n/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0069 Sqrt(x)", "0372 Super Pow", "0029 Divide Two Integers"]
---

# 0050. Pow(x, n)

## ⚡ 30-Second Summary
**Pattern:** Binary exponentiation (exponentiation by squaring)
**Key insight:** `x^n = (x²)^(n/2)`, times one extra x when n is odd. Halving n each step needs only O(log n) multiplications. For negative n, compute `(1/x)^|n|`. Take |n| in a 64-bit integer, because `-INT_MIN` overflows.
**Go-to:** Iterative squaring over the bits of n, O(log n) time, O(1) space

## Problem
Compute x raised to an integer power n, where n can be negative, without calling the built-in power function. [LeetCode](https://leetcode.com/problems/powx-n/)

**Examples:**
```
Input:  x = 2.00000, n = 10
Output: 1024.00000
Why:    2 multiplied by itself ten times.

Input:  x = 2.10000, n = 3
Output: 9.26100
Why:    2.1 · 2.1 · 2.1.

Input:  x = 2.00000, n = -2
Output: 0.25000
Why:    A negative power is the reciprocal: 1 / 2².
```

**Constraints:**
- −2³¹ ≤ n ≤ 2³¹ − 1, so O(n) multiplication is too slow, and `-n` overflows for n = INT_MIN.
- −100 < x < 100, and either x ≠ 0 or n > 0 (no 0 to a negative power).
- The answer fits comfortably in a double (−10⁴ ≤ xⁿ ≤ 10⁴).

## Hints
<details><summary>Hint 1</summary>
Multiplying n times is up to 2·10⁹ steps. If you know x^(n/2), how quickly can you get xⁿ?
</details>
<details><summary>Hint 2</summary>
Write n in binary: x^13 = x^8 · x^4 · x^1. How do you get x, x², x⁴, x⁸ … cheaply?
</details>
<details><summary>Hint 3</summary>
N = |n| as a 64-bit integer; if n &lt; 0, set x = 1/x. Loop while N &gt; 0: if N is odd, result *= x; x *= x; N /= 2.
</details>

## Clarifying Questions
- Can n be negative? (Yes, so take the reciprocal.)
- Can x be 0? (Only with n > 0.)
- How precise must the answer be? (Within about 10⁻⁵ of the true value.)

## Example Walkthrough
`x = 3, n = 5` (binary 101). Bit 0 = 1: result = 3, base → 9. Bit 1 = 0: skip, base → 81. Bit 2 = 1: result = 3 · 81 = 243. Three steps instead of five multiplications, and the gap widens fast as n grows.

## Approaches

### 1. Multiply n Times: O(|n|) time, O(1) space
Correct, but too slow for |n| near 2³¹. Mention it, then optimise.

### 2. Recursive Halving: O(log n) time, O(log n) space
`half = pow(x, n/2)`, then return `half·half` or `half·half·x`. Clear, but it uses stack space.

### 3. Iterative Squaring ⭐ Go-to: O(log n) time, O(1) space
**Why it's the go-to:** no recursion, a few lines, and it doubles as the modular-pow template used in many math problems.

## Dry Run (Approach 3)
`x = 2, n = 10` (binary 1010)

| N (bin) | N odd? | result | base after |
|---------|--------|--------|------------|
| 1010 | no | 1 | 4 |
| 101 | yes | 4 | 16 |
| 10 | no | 4 | 256 |
| 1 | yes | 4 · 256 = **1024** | 65536 |

## Edge Case Check
- `n = 0` → 1 (the loop never runs). ✅
- `n = −2³¹` with x = 1 or −1 → 64-bit N avoids the overflow; the answer is 1. ✅
- `x = 2, n = −2³¹` → underflows to 0.0, which is accepted. ✅
- Negative x with odd n → stays negative. ✅

## ⚠️ Pitfalls
- **`n = -n` in a C++ `int`** overflows for INT_MIN. Copy into `long long` first.
- **Recursing on `pow(x, n-1)`** is still O(n) deep and overflows the stack.
- **Calling `pow(x, n/2)` twice** in the recursive version makes it O(n) again. Store `half`.
- **Python `n // 2` for negative n** rounds towards −∞. Convert to |n| first.

## 🎯 What the Interviewer Wants
- O(log n) by squaring, recursive or iterative.
- Negative exponents and the INT_MIN overflow.
- Optional: the same loop with `% MOD` for modular exponentiation.

## Follow-ups
- **Inverse problem (integer root):** [LC 0069 Sqrt(x)](../../05-binary-search/0069-sqrtx/)
- **Modular power with a huge exponent:** LC 0372 Super Pow (not added yet)
- **Doubling trick without multiplication:** LC 0029 Divide Two Integers (not added yet)
- **Matrix power:** the same loop on 2×2 matrices gives Fibonacci in O(log n).
