---
number: 703
title: Kth Largest Element in a Stream
difficulty: Easy
topic: Heap / Priority Queue
pattern: Min-heap of size k
link: https://leetcode.com/problems/kth-largest-element-in-a-stream/
lists: [NeetCode 150]
followup_of: []
related: ["0215 Kth Largest Element in an Array", "0295 Find Median from Data Stream", "0347 Top K Frequent Elements"]
---

# 0703. Kth Largest Element in a Stream

## ⚡ 30-Second Summary
**Pattern:** Min-heap holding the k largest values seen so far
**Key insight:** Keep only the top k values in a min-heap. Its smallest element (the top) is exactly the k-th largest overall. A new value smaller than the top can never matter; otherwise push it and pop the old top.
**Go-to:** Min-heap of size k, O(log k) per add, O(k) space

## Problem
Design a class built from k and an initial array; `add(val)` inserts a value into the stream and returns the current k-th largest value.

**Examples:**
```
Input:  ["KthLargest","add","add","add","add","add"]
        [[3,[4,5,8,2]],[3],[5],[10],[9],[4]]
Output: [null,4,5,5,8,8]
Why:    After adding 3 the values are 2,3,4,5,8 and the 3rd largest is 4;
        each later add shifts the top three.

Input:  ["KthLargest","add","add","add","add"]
        [[4,[7,7,7,7,8,3]],[2],[10],[9],[9]]
Output: [null,7,7,7,8]
Why:    Duplicates count separately: the top four start as 8,7,7,7.
```

**Constraints:**
- 1 ≤ k ≤ 10⁴; up to 10⁴ initial values and 10⁴ adds.
- When add is called there are at least k values (the initial array may have k - 1).

## Hints
<details><summary>Hint 1</summary>
Do you need to remember values that are smaller than the current k-th largest?
</details>
<details><summary>Hint 2</summary>
You only need the k largest. Which of those is the answer?
</details>
<details><summary>Hint 3</summary>
Min-heap of size k: push the new value, and if size > k, pop. The top is the answer.
</details>

## Clarifying Questions
- Duplicates count as separate values? (Yes.)
- Can the initial array have fewer than k elements? (k - 1 at most; the first add fills it.)

## Example Walkthrough
k = 3, initial [4,5,8,2] → heap keeps {4,5,8}. add 3 → 3 < 4, discarded → 4. add 5 → push, pop 4 → {5,5,8} → 5. add 10 → {5,8,10} → 5. add 9 → {8,9,10} → 8. add 4 → 8.

## Approaches

### 1. Sorted List With Insertion: O(n) per add, O(n) space
Insert into a sorted list (binary search for the position, then shift) and read index len - k.

### 2. Min-Heap of Size k ⭐ Go-to: O(log k) per add, O(k) space
**Why it's the go-to:** constant memory in k and log time per add, the classic streaming top-k structure.

## Dry Run (Approach 2)
k = 3, heap {4,5,8}

| add | push | pop (size > 3) | heap | answer |
|-----|------|----------------|------|--------|
| 3 | 3 | 3 | {4,5,8} | 4 |
| 5 | 5 | 4 | {5,5,8} | 5 |
| 10 | 10 | 5 | {5,8,10} | 5 |
| 9 | 9 | 5 | {8,9,10} | 8 |
| 4 | 4 | 4 | {8,9,10} | 8 |

## Edge Case Check
- Initial array of size k - 1: the first add brings the heap to size k. ✅
- Duplicates: kept as separate heap entries. ✅
- k = 1: the heap holds the maximum. ✅

## ⚠️ Pitfalls
- **Max-heap of everything**: popping k times per add is O(k log n).
- **C++ default priority_queue is a max-heap**: use `greater<int>`.
- **Python heapq is a min-heap**: good here, no negation needed.

## 🎯 What the Interviewer Wants
- "Top k largest → min-heap of size k" stated with the reasoning.
- Per-operation complexity.

## Follow-ups
- **Static array version:** [LC 0215 Kth Largest Element in an Array](../0215-kth-largest-element-in-an-array/)
- **Median instead of k-th:** two heaps: [LC 0295 Find Median from Data Stream](../0295-find-median-from-data-stream/)
- **Top k by frequency:** [LC 0347 Top K Frequent Elements](../../01-arrays-hashing/0347-top-k-frequent-elements/)
