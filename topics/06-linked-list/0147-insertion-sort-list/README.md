---
number: 147
title: Insertion Sort List
difficulty: Medium
topic: Linked List
pattern: Dummy-headed sorted list + splice each node in
link: https://leetcode.com/problems/insertion-sort-list/
lists: [Interview Extras]
followup_of: []
related: ["0148 Sort List", "0021 Merge Two Sorted Lists", "0912 Sort an Array"]
---

# 0147. Insertion Sort List

## ⚡ 30-Second Summary
**Pattern:** Grow a sorted list behind a dummy; take nodes from the input one by one
**Key insight:** Unlike arrays, inserting into a linked list costs O(1) once you've found the spot. So for each input node, walk the sorted list from the dummy to the last node with value ≤ it, and splice it in after that node. Inserting after equal values keeps the sort stable.
**Go-to:** Insertion into a dummy-headed list, O(n²) time, O(1) space

## Problem
Sort a singly linked list using insertion sort (relink the nodes; don't sort values elsewhere) and return the new head. [LeetCode](https://leetcode.com/problems/insertion-sort-list/)

**Examples:**
```
Input:  head = [4,2,1,3]
Output: [1,2,3,4]
Why:    Ascending order.

Input:  head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
Why:    Negative values sort like any others.
```

**Constraints:**
- 1 ≤ n ≤ 5000 (so O(n²) ≈ 2.5 · 10⁷ comparisons is fine); values in [−5000, 5000].

## Hints
<details><summary>Hint 1</summary>
In array insertion sort you shift elements right. What replaces shifting in a linked list?
</details>
<details><summary>Hint 2</summary>
Splicing: once you know the node to insert after, it's two pointer assignments. The new head may change; what helps with that?
</details>
<details><summary>Hint 3</summary>
Dummy → sorted part. For each node cur (save cur.next first): walk prev from the dummy while prev.next.val ≤ cur.val, then cur.next = prev.next; prev.next = cur.
</details>

## Clarifying Questions
- Must it be insertion sort? (Yes, that's the exercise; LC 148 asks for O(n log n).)
- Relink nodes rather than change values? (Yes.)
- Stability matters? (Not tested, but inserting after equal values keeps it stable.)

## Example Walkthrough
`[4,2,1,3]`: sorted = []. Insert 4 → [4]. Insert 2 → before 4 → [2,4]. Insert 1 → front → [1,2,4]. Insert 3 → after 2 → [1,2,3,4].

## Approaches

### 1. Copy Values, Sort, Write Back: O(n log n) time, O(n) space
Works, but it isn't insertion sort and it changes values rather than links. Mention it only as a baseline.

### 2. Insertion into a Dummy-headed List ⭐ Go-to: O(n²) time, O(1) space
Each node is spliced into the sorted list behind a dummy.
**Why it's the go-to:** it's exactly what's asked, and the dummy removes every head special case.

### 3. With a Sorted-tail Shortcut: O(n²) worst, O(n) on sorted input, O(1) space
Keep the input in place and track the last sorted node. If the next node is ≥ it, just extend the sorted part. Otherwise unlink the node and insert it from the dummy. Nice optimisation to mention, but a bit more pointer juggling.

## Dry Run (Approach 2)
`[-1,5,3,4,0]` (the sorted list is shown after each insert).

| take | walk prev from dummy while next ≤ take | sorted list |
|------|----------------------------------------|-------------|
| −1 | stays at dummy | [−1] |
| 5 | → −1 | [−1,5] |
| 3 | → −1 (5 > 3) | [−1,3,5] |
| 4 | → −1 → 3 (5 > 4) | [−1,3,4,5] |
| 0 | → −1 (3 > 0) | **[−1,0,3,4,5]** |

## Edge Case Check
- One node → returned as is. ✅
- Already sorted → approach 2 is still O(n²) (scans from the front each time); approach 3 is O(n). ✅
- Reverse sorted → each insert lands right after the dummy. ✅
- Duplicates `[3,3,1]` → [1,3,3], stable. ✅

## ⚠️ Pitfalls
- **Losing the rest of the input:** save `cur.next` before splicing cur into the sorted list.
- **Walking with `prev.next.val < cur.val`** (strict) still sorts, but loses stability; `≤` inserts after equal values.
- **Forgetting the null check** `prev.next && …` when cur belongs at the end.

## 🎯 What the Interviewer Wants
- Clean splicing with a dummy and no head special cases.
- Correct O(n²) analysis, and when insertion sort is actually good (nearly sorted input, approach 3).
- Know that LC 148 (merge sort) is the O(n log n) answer.

## Follow-ups
- **O(n log n) linked-list sort:** [LC 0148 Sort List](../0148-sort-list/)
- **The merge step:** [LC 0021 Merge Two Sorted Lists](../0021-merge-two-sorted-lists/)
- **Array sorting from scratch:** LC 0912 Sort an Array (not added yet)
