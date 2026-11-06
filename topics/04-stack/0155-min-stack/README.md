---
number: 155
title: Min Stack
difficulty: Medium
topic: Stack
pattern: Stack of (value, min so far)
link: https://leetcode.com/problems/min-stack/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0239 Sliding Window Maximum", "0716 Max Stack", "0232 Implement Queue using Stacks"]
---

# 0155. Min Stack

## ⚡ 30-Second Summary
**Pattern:** Stack of (value, min so far)
**Key insight:** A stack only ever changes at the top, so the minimum of everything *below and including* each element never changes while that element is on the stack. Store that minimum next to each value.
**Go-to:** Stack of pairs, O(1) for every operation, O(n) space

## Problem
Design a stack that supports `push`, `pop`, `top` and `getMin`, all in O(1) time. `pop`, `top` and `getMin` are only called on a non-empty stack. [LeetCode](https://leetcode.com/problems/min-stack/)

**Examples:**
```
Input:  ["MinStack","push","push","push","getMin","pop","top","getMin"]
        [[],[-2],[0],[-3],[],[],[],[]]
Output: [null,null,null,null,-3,null,0,-2]
Why:    After pushing -2, 0, -3 the min is -3. Popping -3 leaves 0 on top,
        and the min falls back to -2.
```

**Constraints:**
- Values fit in a 32-bit int.
- At most 3·10⁴ calls in total, so O(n) per `getMin` might pass but isn't what's asked.
- `pop`, `top`, `getMin` are never called on an empty stack.

## Hints
<details><summary>Hint 1</summary>
A single "current min" variable breaks on pop: if you pop the min, what's the new one?
</details>
<details><summary>Hint 2</summary>
When an element is on top, the elements below it are fixed. So the min of the stack at that moment is fixed too.
</details>
<details><summary>Hint 3</summary>
Push (val, min(val, previous min)) together. getMin reads the second field of the top.
</details>

## Clarifying Questions
- Can operations be called on an empty stack? (No, guaranteed.)
- Duplicates allowed? (Yes, which matters for the two-stack variant.)
- Value range? (32-bit; no arithmetic on values, so overflow doesn't apply.)

## Example Walkthrough
Push -2, 0, -3 storing (val, minSoFar): (-2,-2), (0,-2), (-3,-3).
- getMin reads the top's min: -3.
- pop removes (-3,-3). Top is now (0,-2).
- top returns 0, getMin returns -2. No recomputation needed.

## Approaches

### 1. Plain Stack, Scan for Min: O(1) push/pop/top, O(n) getMin, O(n) space
Simple, but getMin breaks the O(1) requirement.

### 2. Stack of (value, min so far) ⭐ Go-to: O(1) all ops, O(n) space
Each entry carries the min of itself and everything below it.
**Why it's the go-to:** every operation is one line, and there's no duplicate-handling trap.

### 3. Two Stacks: O(1) all ops, O(n) space worst case, less in practice
Main stack plus a min stack that only gets a push when `val <= minStack.top()`. On pop, if the popped value equals the min stack's top, pop that too. Saves space when the min rarely changes.

## Dry Run (Approach 2)
Ops: push 0, push 1, push 0, getMin, pop, getMin (duplicate min on purpose)

| op | stack (val, min) after | output |
|----|------------------------|--------|
| push 0 | (0,0) | null |
| push 1 | (0,0) (1,0) | null |
| push 0 | (0,0) (1,0) (0,0) | null |
| getMin | unchanged | 0 |
| pop | (0,0) (1,0) | null |
| getMin | unchanged | 0 |

## Edge Case Check
- Duplicate minimums (above): pairs handle them naturally. In the two-stack version, `<` instead of `<=` would lose the second 0 and getMin would break after the pop. ✅
- Single element: its own min. ✅
- Strictly decreasing pushes: every entry has min = val. ✅

## ⚠️ Pitfalls
- **One `min` variable**: you can't restore it after popping the min.
- **Two stacks with `<` instead of `<=`**: duplicates of the min break pop.
- **C++ `stack::pop()` returns void**: read `top()` first if you need the value.
- **Go**: LeetCode expects `Constructor()` returning the struct and pointer-receiver methods.

## 🎯 What the Interviewer Wants
- Spot that a single min variable fails on pop, before being told.
- O(1) for all four operations, with a clear invariant.
- Mention the two-stack space optimization and its `<=` subtlety.

## Follow-ups
- **Max stack with popMax:** needs a sorted structure or heap + lazy deletion: LC 0716 Max Stack (not added yet)
- **O(1) extra space trick:** store `2·val - min` encodings when a new min arrives (needs 64-bit to avoid overflow).
- **Min of a sliding window (queue, not stack):** monotonic deque: [LC 0239 Sliding Window Maximum](../../03-sliding-window/0239-sliding-window-maximum/)
- **Queue with O(1) min:** two min-stacks (an input and an output stack).
