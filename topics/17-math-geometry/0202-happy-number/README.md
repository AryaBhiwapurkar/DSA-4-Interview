---
number: 202
title: Happy Number
difficulty: Easy
topic: Math & Geometry
pattern: Cycle detection (fast/slow)
link: https://leetcode.com/problems/happy-number/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0141 Linked List Cycle", "0142 Linked List Cycle II", "0287 Find the Duplicate Number"]
---

# 0202. Happy Number

## ⚡ 30-Second Summary
**Pattern:** Treat "sum of squared digits" as a next-pointer and detect a cycle
**Key insight:** The sequence can't grow forever. Any number with 4 or more digits maps to something smaller, and anything up to 999 maps to at most 243. So it either reaches 1 or loops. Find out which with a seen-set, or with Floyd's slow/fast pointers in O(1) space.
**Go-to:** Hash set of seen values, O(log n) per step, O(k) space. Mention Floyd for O(1) space.

## Problem
Repeatedly replace a positive integer with the sum of the squares of its digits. It's "happy" if the process eventually reaches 1. Otherwise it loops forever without reaching 1. Decide which. [LeetCode](https://leetcode.com/problems/happy-number/)

**Examples:**
```
Input:  n = 19
Output: true
Why:    19 → 82 → 68 → 100 → 1.

Input:  n = 2
Output: false
Why:    2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4, a loop that never hits 1.
```

**Constraints:**
- 1 ≤ n ≤ 2³¹ − 1. Its digit-square sum is at most 10 · 81 = 810, so after one step every value is small.

## Hints
<details><summary>Hint 1</summary>
If the sequence never reaches 1, what must it eventually do? Can it grow without bound?
</details>
<details><summary>Hint 2</summary>
"Keeps going until it repeats" is cycle detection. Which structures or pointer tricks detect a cycle?
</details>
<details><summary>Hint 3</summary>
Write next(n) = sum of squared digits. Keep a set: loop while n ≠ 1 and n is not in the set, adding n and moving to next(n). Return n == 1. (Or slow = next(slow), fast = next(next(fast)) until they meet; happy iff they meet at 1.)
</details>

## Clarifying Questions
- Is n always positive? (Yes, n ≥ 1.)
- Is 1 itself happy? (Yes, zero steps.)
- Is O(1) space required? (Not by default; Floyd is the follow-up.)

## Example Walkthrough
`n = 7`: 7 → 49 → 97 → 130 → 10 → 1. Happy. `n = 4` sits inside the unhappy cycle 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4. Every unhappy number falls into that same 8-number cycle.

## Approaches

### 1. Hash Set ⭐ Go-to: O(log n) per step, O(k) space
Remember every value. Stop at 1 (happy) or at a repeat (cycle).
**Why it's the go-to:** obviously correct, three lines, and the bounded-growth argument is all the justification it needs.

### 2. Floyd's Slow/Fast: O(log n) per step, O(1) space
Slow takes one step and fast takes two. They meet inside any cycle, and 1 is a fixed point (1 → 1), so check whether the meeting point is 1. Same idea as [LC 0141](../../06-linked-list/0141-linked-list-cycle/).

## Dry Run (Approach 1)
`n = 2`

| step | n | in seen? | seen after |
|------|---|----------|------------|
| 1 | 2 | no | {2} |
| 2 | 4 | no | {2,4} |
| 3 | 16 | no | {2,4,16} |
| … | 37, 58, 89, 145, 42, 20 | no | +6 |
| 10 | 4 | **yes** | stop |

The loop stopped at 4 ≠ 1 → **false**.

## Edge Case Check
- `n = 1` → true at once. ✅
- `n = 2³¹ − 1` → the first step drops it to a small number (2147483647 → 260). ✅
- `n = 10` → 1 → true (zeros contribute nothing). ✅

## ⚠️ Pitfalls
- **No stopping condition:** a plain `while n != 1` loops forever on unhappy numbers.
- **Floyd: checking `slow == fast` before the first move** exits at once. Move first, then compare.
- **Hardcoding "4 means unhappy"** works, but you have to justify it. Interviewers want the general cycle argument.

## 🎯 What the Interviewer Wants
- See that this is cycle detection on an implicit sequence.
- Argue that it can't diverge (the digit-square sum is bounded).
- Offer Floyd as the O(1)-space upgrade.

## Follow-ups
- **Same cycle detection on a linked list:** [LC 0141 Linked List Cycle](../../06-linked-list/0141-linked-list-cycle/)
- **Where does the cycle start?** LC 0142 Linked List Cycle II (not added yet)
- **Floyd on array indices:** [LC 0287 Find the Duplicate Number](../../06-linked-list/0287-find-the-duplicate-number/)
