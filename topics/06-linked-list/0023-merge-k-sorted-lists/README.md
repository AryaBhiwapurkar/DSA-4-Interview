---
number: 23
title: Merge k Sorted Lists
difficulty: Hard
topic: Linked List
pattern: Min-heap / divide & conquer
link: https://leetcode.com/problems/merge-k-sorted-lists/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0021 Merge Two Sorted Lists"]
related: ["0021 Merge Two Sorted Lists", "0378 Kth Smallest Element in a Sorted Matrix", "0373 Find K Pairs with Smallest Sums"]
---

# 0023. Merge k Sorted Lists

## ⚡ 30-Second Summary
**Pattern:** Min-heap of list heads (or pairwise divide & conquer)
**Key insight:** The next node of the merged list is always the smallest current head among the k lists. A min-heap of size k gives that in O(log k). Alternatively, merge lists in pairs like merge sort so each node is touched log k times.
**Go-to:** Min-heap of heads, O(N log k) time, O(k) space (N = total nodes)

## Problem
Given k sorted linked lists, merge them into one sorted linked list and return its head.

**Examples:**
```
Input:  lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Why:    All values from the three lists, in sorted order.

Input:  lists = []
Output: []
Why:    No lists at all.

Input:  lists = [[]]
Output: []
Why:    One list, and it's empty.
```

**Constraints:**
- 0 ≤ k ≤ 10⁴; total nodes N ≤ 10⁴.
- Lists can be empty (null entries).

## Hints
<details><summary>Hint 1</summary>
Merging two sorted lists is easy. Merging them one by one into an accumulator works, but how much repeated work does it do?
</details>
<details><summary>Hint 2</summary>
At each step you need the minimum of k heads. What structure maintains a minimum under insert/remove in O(log k)?
</details>
<details><summary>Hint 3</summary>
Push every non-null head into a min-heap keyed by value. Pop the smallest, append it, push its next if any. Or merge pairs (0,1), (2,3), … repeatedly, halving the count each round.
</details>

## Clarifying Questions
- Can k be 0, or lists be empty? (Yes, both.)
- Splice nodes or create new ones? (Splicing is fine.)
- Total size? (N ≤ 10⁴; k can be as large as N.)

## Example Walkthrough
Heap starts with heads 1 (list 0), 1 (list 1), 2 (list 2).
- Pop 1 (list 0), push 4. Pop 1 (list 1), push 3. Pop 2, push 6. Pop 3, push 4.
- Pop 4, push 5 … continue until the heap is empty: 1,1,2,3,4,4,5,6.

## Approaches

### 1. Collect, Sort, Rebuild: O(N log N) time, O(N) space
Dump all values, sort, build a new list. A fine opener. (Merging lists one by one into an accumulator is O(k·N): the early nodes get re-scanned k times.)

### 2. Min-Heap of Heads ⭐ Go-to: O(N log k) time, O(k) space
k entries in the heap at most; each of the N nodes is pushed and popped once.
**Why it's the go-to:** the most natural optimal answer, and it generalizes to streams (merge k sorted files).

### 3. Divide & Conquer Pairwise Merge: O(N log k) time, O(1) extra space
Merge lists i and i + step for step = 1, 2, 4, …; reuses the 0021 merge. Same complexity, no heap needed.

## Dry Run (Approach 2)
`[[1,4,5],[1,3,4],[2,6]]` (heap shows value(list))

| pop | append | push | heap after |
|-----|--------|------|------------|
| 1(0) | 1 | 4(0) | 1(1), 2(2), 4(0) |
| 1(1) | 1 | 3(1) | 2(2), 3(1), 4(0) |
| 2(2) | 2 | 6(2) | 3(1), 4(0), 6(2) |
| 3(1) | 3 | 4(1) | 4(0), 4(1), 6(2) |
| 4(0) | 4 | 5(0) | 4(1), 5(0), 6(2) |
| 4(1) | 4 | - | 5(0), 6(2) |
| 5(0), 6(2) | 5, 6 | - | empty |

## Edge Case Check
- `[]` and `[[]]`: nothing pushed, return null. ✅
- Mixed empty and non-empty lists `[[2],[],[1]]`: skip nulls when seeding the heap → [1,2]. ✅
- k = 1: returns that list. ✅

## ⚠️ Pitfalls
- **Pushing null heads** into the heap: crash on `.val`.
- **Python heapq comparing nodes on ties**: push (val, index, node) so ties never reach the node.
- **C++ `priority_queue` is a max-heap**: the comparator must be `a->val > b->val` for a min-heap.
- **Go `container/heap`**: implement Len/Less/Swap/Push/Pop and use `heap.Push`/`heap.Pop`, not the methods directly.

## 🎯 What the Interviewer Wants
- Progress from brute force (or one-by-one merging) to O(N log k), with the reason it's log k.
- Correct heap usage in your language, including tie handling.
- Mention divide & conquer as an equally optimal, heap-free alternative.

## Follow-ups
- **Two lists:** [LC 0021 Merge Two Sorted Lists](../0021-merge-two-sorted-lists/)
- **Kth smallest across sorted rows:** heap of row heads: LC 0378 Kth Smallest Element in a Sorted Matrix (not added yet)
- **k smallest pairs from two arrays:** heap of candidate pairs: LC 0373 Find K Pairs with Smallest Sums (not added yet)
- **External merge of k huge files:** the same heap, with buffered readers.
