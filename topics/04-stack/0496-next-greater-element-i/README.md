---
number: 496
title: Next Greater Element I
difficulty: Easy
topic: Stack
pattern: Monotonic decreasing stack + hashmap
link: https://leetcode.com/problems/next-greater-element-i/
lists: [Interview Extras]
followup_of: []
related: ["0503 Next Greater Element II", "0739 Daily Temperatures", "0901 Online Stock Span"]
---

# 0496. Next Greater Element I

## ⚡ 30-Second Summary
**Pattern:** Monotonic stack over nums2, answers stored in a map
**Key insight:** Scan nums2 once, keeping a stack of values that haven't found a bigger value yet (decreasing from bottom to top). When x arrives, it is the next greater element of every smaller value on top, so pop those and record `next[v] = x`. Values left at the end get −1. Then answer each nums1 query with a map lookup.
**Go-to:** Monotonic stack + map, O(n2 + n1) time, O(n2) space

## Problem
nums1 is a subset of nums2, and all values are distinct. For each value in nums1, find where it sits in nums2 and return the first larger value to its right, or −1 if there isn't one. [LeetCode](https://leetcode.com/problems/next-greater-element-i/)

**Examples:**
```
Input:  nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Why:    Nothing bigger follows 4; 3 follows 1; nothing bigger follows 2.

Input:  nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Why:    3 is right after 2; 4 is last.
```

**Constraints:**
- 1 ≤ n1 ≤ n2 ≤ 1000; values distinct; follow-up asks for O(n1 + n2).

## Hints
<details><summary>Hint 1</summary>
Brute force: for each query, find it in nums2 and scan right. Can you compute the answer for every value of nums2 at once?
</details>
<details><summary>Hint 2</summary>
While scanning left to right, which earlier values are still waiting for a bigger one? What order are they in?
</details>
<details><summary>Hint 3</summary>
For x in nums2: while stack and stack.top &lt; x: next[pop()] = x. Push x. Answer = [next.get(v, −1) for v in nums1].
</details>

## Clarifying Questions
- Are values distinct? (Yes, so values can be map keys.)
- Strictly greater? (Yes.)
- Is nums1 always a subset of nums2? (Yes.)

## Example Walkthrough
nums2 = [1,3,4,2]: push 1. 3 pops 1 (next[1] = 3), push 3. 4 pops 3 (next[3] = 4), push 4. 2 < 4, push 2. Left over: 4, 2 → −1. Queries [4,1,2] → [−1,3,−1].

## Approaches

### 1. Scan Right per Query: O(n1 · n2) time, O(1) space
Find each value, then scan forward. Fine for n ≤ 1000.

### 2. Monotonic Stack + Map ⭐ Go-to: O(n1 + n2) time, O(n2) space
**Why it's the go-to:** the canonical next-greater template, and it meets the follow-up.

## Dry Run (Approach 2)
nums2 = [1,3,4,2]

| x | pops (next[v] = x) | stack after |
|---|--------------------|-------------|
| 1 | – | [1] |
| 3 | 1 → 3 | [3] |
| 4 | 3 → 4 | [4] |
| 2 | – | [4,2] |

Map {1:3, 3:4}; queries [4,1,2] → **[−1,3,−1]**.

## Edge Case Check
- Strictly decreasing nums2 → all −1. ✅
- Increasing nums2 → each value's next is its right neighbour. ✅
- Last element → −1. ✅

## ⚠️ Pitfalls
- **Popping on `<=`:** with distinct values it doesn't matter; for duplicates (as in 0503), think about strictness.
- **C++ `map[v]` for queries** inserts zeros for missing keys; use `find` or a default.
- **Scanning nums1 instead of nums2** with the stack: the order that matters is nums2's.

## 🎯 What the Interviewer Wants
- Recognise the next-greater pattern and the monotonic stack.
- The amortised O(n) argument (each value is pushed and popped once).

## Follow-ups
- **Circular array:** [LC 0503 Next Greater Element II](../0503-next-greater-element-ii/)
- **Distance instead of value:** [LC 0739 Daily Temperatures](../0739-daily-temperatures/)
- **Online, look backward:** [LC 0901 Online Stock Span](../0901-online-stock-span/)
