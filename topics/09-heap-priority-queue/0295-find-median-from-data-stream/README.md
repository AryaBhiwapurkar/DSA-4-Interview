---
number: 295
title: Find Median from Data Stream
difficulty: Hard
topic: Heap / Priority Queue
pattern: Two heaps
link: https://leetcode.com/problems/find-median-from-data-stream/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0480 Sliding Window Median", "0703 Kth Largest Element in a Stream", "0004 Median of Two Sorted Arrays"]
---

# 0295. Find Median from Data Stream

## ⚡ 30-Second Summary
**Pattern:** Two heaps split the stream into a lower and an upper half
**Key insight:** Keep the smaller half in a max-heap and the larger half in a min-heap, with sizes equal or the lower half one bigger. Then the median is the lower top (odd count) or the average of both tops (even). Each add is two heap moves.
**Go-to:** Max-heap (low) + min-heap (high), O(log n) add, O(1) median

## Problem
Design `addNum(num)` and `findMedian()` over a stream of integers. The median of an even count is the mean of the two middle values. [LeetCode](https://leetcode.com/problems/find-median-from-data-stream/)

**Examples:**
```
Input:  ["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
        [[],[1],[2],[],[3],[]]
Output: [null,null,null,1.5,null,2.0]
Why:    After 1, 2 the median is 1.5; after adding 3 it's 2.
```

**Constraints:**
- Values in ±10⁵; up to 5·10⁴ calls; findMedian is only called on a non-empty stream.
- Follow-ups: what if all values are in [0, 100]? What if 99% are?

## Hints
<details><summary>Hint 1</summary>
Keeping everything sorted makes each insert O(n). Do you need the whole order to know the middle?
</details>
<details><summary>Hint 2</summary>
You only need the largest value of the lower half and the smallest of the upper half.
</details>
<details><summary>Hint 3</summary>
Push into low (max-heap), move low's top to high, and if high is bigger than low, move high's top back. Median from the tops.
</details>

## Clarifying Questions
- Return type? (Double.)
- Duplicates and negatives? (Yes, both.)

## Example Walkthrough
add 1: low {1}. add 2: push to low → move 2 to high → low {1}, high {2}; median (1 + 2)/2 = 1.5. add 3: push to low {3,1} → move 3 to high {2,3} → high bigger → move 2 back → low {2,1}, high {3}; median 2.

## Approaches

### 1. Sorted List With Insertion: O(n) add, O(1) median, O(n) space
Binary search for the position, insert (shifting), read the middle.

### 2. Two Heaps ⭐ Go-to: O(log n) add, O(1) median, O(n) space
**Why it's the go-to:** the standard answer; the three-step add keeps the invariant without case analysis.

## Dry Run (Approach 2)
adds -1, -2, -3

| add | low (max) after | high (min) after | median |
|-----|-----------------|------------------|--------|
| -1 | -1 | - | -1 |
| -2 | -2 | -1 | -1.5 |
| -3 | -2, -3 | -1 | -2 |

## Edge Case Check
- Single value: low has it, median = that value. ✅
- Negatives / duplicates: heaps don't care. ✅

## ⚠️ Pitfalls
- **Python max-heap**: store negatives in `low`.
- **Integer average**: (a + b) / 2.0, not integer division.
- **Wrong balancing rule**: decide which heap holds the extra element and stick to it.

## 🎯 What the Interviewer Wants
- The two-heap invariant stated clearly.
- Follow-up answers: values in [0, 100] → counting array with a running count, O(100) median; 99% in range → counts for the range plus small heaps / lists for outliers.

## Follow-ups
- **Median of a sliding window:** two heaps with lazy deletion, or a balanced BST: LC 0480 Sliding Window Median (not added yet)
- **k-th largest instead:** [LC 0703 Kth Largest Element in a Stream](../0703-kth-largest-element-in-a-stream/)
- **Median of two sorted arrays:** [LC 0004 Median of Two Sorted Arrays](../../05-binary-search/0004-median-of-two-sorted-arrays/)
