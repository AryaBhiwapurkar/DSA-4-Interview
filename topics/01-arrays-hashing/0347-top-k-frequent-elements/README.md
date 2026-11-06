---
number: 347
title: Top K Frequent Elements
difficulty: Medium
topic: Arrays & Hashing
pattern: Counting + bucket sort / heap
link: https://leetcode.com/problems/top-k-frequent-elements/
lists: [NeetCode 150]
followup_of: []
related: ["0692 Top K Frequent Words", "0215 Kth Largest Element in an Array", "0973 K Closest Points to Origin"]
---

# 0347. Top K Frequent Elements

## ⚡ 30-Second Summary
**Pattern:** Count frequencies, then select the top k (bucket sort or heap)
**Key insight:** A frequency is at most n, so you can bucket values by frequency (index = count) and read buckets from high to low. No comparison sort needed.
**Go-to:** Hashmap + bucket sort, O(n) time, O(n) space

## Problem
Given an integer array and k, return the k values that occur most often, in any order. The answer is guaranteed to be unique. [LeetCode](https://leetcode.com/problems/top-k-frequent-elements/)

**Examples:**
```
Input:  nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Why:    1 appears 3 times, 2 appears twice, 3 once; take the top two.

Input:  nums = [1], k = 1
Output: [1]
Why:    Only one distinct value.

Input:  nums = [1,2,1,2,1,2,3,1,3,2], k = 2
Output: [1,2]
Why:    1 and 2 appear four times each, 3 only twice.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; -10⁴ ≤ nums[i] ≤ 10⁴.
- 1 ≤ k ≤ number of distinct values, and the answer is unique.
- Follow-up: do better than O(n log n).

## Hints
<details><summary>Hint 1</summary>
First get each value's frequency. Then what?
</details>
<details><summary>Hint 2</summary>
Sorting by frequency is O(n log n). To pick only the top k, a heap of size k is O(n log k).
</details>
<details><summary>Hint 3</summary>
Frequencies range from 1 to n. Make n+1 buckets where bucket[f] holds values with frequency f, then walk from the end.
</details>

## Clarifying Questions
- Any output order? (Yes.)
- Can there be ties at the k-th position? (Guaranteed not here; ask how to break ties otherwise.)
- Is k always valid? (Yes, 1 ≤ k ≤ distinct count.)

## Example Walkthrough
`nums = [1,1,1,2,2,3], k = 2`
- Counts: {1:3, 2:2, 3:1}.
- Buckets by frequency: bucket[3] = [1], bucket[2] = [2], bucket[1] = [3].
- Walk down from 6: bucket[3] gives 1, bucket[2] gives 2. Have k = 2, stop.

## Approaches

### 1. Sort by Frequency: O(n log n) time, O(n) space
Count, sort distinct values by count descending, take the first k.

### 2. Min-Heap of Size k: O(n log k) time, O(n) space
Push (count, value) into a min-heap; pop when its size exceeds k. What's left is the top k. Great when k ≪ n or the data streams in.

### 3. Bucket Sort ⭐ Go-to: O(n) time, O(n) space
Count, then `buckets[count].push(value)`, then collect from the highest bucket down until k values.
**Why it's the go-to:** it answers the "better than O(n log n)" follow-up directly and is short to code. Mention the heap as the streaming-friendly alternative.

## Dry Run (Approach 3)
`nums = [1,2,1,2,1,2,3,1,3,2], k = 2`

| step | state |
|------|-------|
| count | {1:4, 2:4, 3:2} |
| buckets | b[4] = [1,2], b[2] = [3] |
| f = 10..5 | empty |
| f = 4 | take 1, 2: res = [1,2], size 2 = k, stop |

## Edge Case Check
- k equals the number of distinct values: return all of them. ✅
- All values the same: one bucket at index n. ✅
- Negative values: they're hashmap keys, no issue. ✅

## ⚠️ Pitfalls
- **Bucket array of size n, not n+1:** a value appearing n times indexes `buckets[n]`.
- **Stopping mid-bucket:** a bucket can hold several values; stop as soon as you have k.
- **C++ heap direction:** `priority_queue` is a max-heap; use `greater<>` for the size-k min-heap.
- **Go:** `container/heap` needs the five-method interface; bucket sort avoids it.

## 🎯 What the Interviewer Wants
- Count first, then select: name all three selection options with complexities.
- Hit O(n) with buckets when asked for better than n log n.
- Know when the heap is better (streaming, k ≪ n, memory).

## Follow-ups
- **Top k words with alphabetical tie-break:** heap with custom comparator: LC 0692 Top K Frequent Words (not added yet)
- **Data arrives as a stream:** size-k min-heap, O(log k) per update.
- **Kth largest value instead of frequency:** [LC 0215 Kth Largest Element in an Array](../../09-heap-priority-queue/0215-kth-largest-element-in-an-array/)
- **Average O(n) without extra buckets:** quickselect on the distinct values by count.
