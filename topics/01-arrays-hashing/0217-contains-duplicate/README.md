---
number: 217
title: Contains Duplicate
difficulty: Easy
topic: Arrays & Hashing
pattern: Hash set
link: https://leetcode.com/problems/contains-duplicate/
lists: [NeetCode 150]
followup_of: []
related: ["0219 Contains Duplicate II", "0220 Contains Duplicate III", "0001 Two Sum"]
---

# 0217. Contains Duplicate

## ⚡ 30-Second Summary
**Pattern:** Hash set membership
**Key insight:** A duplicate means "I've seen this value before". A hash set answers that in O(1), and I can stop at the first repeat.
**Go-to:** Hash set, O(n) time, O(n) space

## Problem
Given an integer array, return true if any value appears at least twice, and false if every element is distinct. [LeetCode](https://leetcode.com/problems/contains-duplicate/)

**Examples:**
```
Input:  nums = [1,2,3,1]
Output: true
Why:    1 shows up at index 0 and again at index 3.

Input:  nums = [1,2,3,4]
Output: false
Why:    All four values are different.

Input:  nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
Why:    Several values repeat; the first repeat is the second 1.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n²) is too slow.
- -10⁹ ≤ nums[i] ≤ 10⁹, so a counting array is out; use a hash set.

## Hints
<details><summary>Hint 1</summary>
Brute force compares every pair. What question are you really asking for each element?
</details>
<details><summary>Hint 2</summary>
If the array were sorted, where would two equal values end up?
</details>
<details><summary>Hint 3</summary>
Keep a set of values seen so far. The moment an insert finds the value already there, you're done.
</details>

## Clarifying Questions
- Return a boolean, or the duplicate value / its indices?
- Can I modify the input? (Sorting in place changes it.)
- Is memory tight? (Decides set vs sort.)
- Size and value range? (Large range rules out a counting array.)

## Example Walkthrough
`nums = [1,2,3,1]`
- 1: not seen, add. 2: not seen, add. 3: not seen, add.
- 1: already in the set, so return true.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
Compare every pair (i, j) with j > i. Fine for tiny inputs, too slow at 10⁵.

### 2. Sort + Adjacent Check: O(n log n) time, O(1) extra space
After sorting, equal values are neighbours, so one pass comparing `a[i]` and `a[i-1]` is enough. The O(1) space assumes in-place sort and that mutating the input is allowed.

### 3. Hash Set ⭐ Go-to: O(n) time, O(n) space
Walk the array; if the value is already in the set, return true, else insert it.
**Why it's the go-to:** linear time, three lines of code, and it exits early on the first repeat.

## Dry Run (Approach 3)
`nums = [1,2,3,1]`

| i | nums[i] | seen (before) | in set? | action |
|---|---------|---------------|---------|--------|
| 0 | 1 | {} | no | add 1 |
| 1 | 2 | {1} | no | add 2 |
| 2 | 3 | {1,2} | no | add 3 |
| 3 | 1 | {1,2,3} | yes | return true |

## Edge Case Check
- n = 1: nothing to compare, returns false. ✅
- All equal, `[5,5,5]`: caught at i = 1. ✅
- Negatives and large values: hashing handles any int. ✅

## ⚠️ Pitfalls
- **Sorting mutates the input.** If the caller needs the original order, sort a copy (then space is O(n) anyway).
- **C++:** `seen.insert(x).second` is false when x was already present, which gives the check and insert in one call.
- **Python:** `len(set(nums)) != len(nums)` is neat but always builds the whole set; the loop version exits early.
- **Go:** there is no set type; use `map[int]struct{}` (zero-byte values) or `map[int]bool`.

## 🎯 What the Interviewer Wants
- Brute force first, then the set.
- Name the time/space trade-off and offer sorting as the O(1)-space option.
- Mention early exit.

## Follow-ups
- **Duplicate within distance k:** sliding window of a set: [LC 0219 Contains Duplicate II](../../03-sliding-window/0219-contains-duplicate-ii/)
- **Values within t and indices within k:** buckets or an ordered set: LC 0220 Contains Duplicate III (not added yet)
- **O(1) extra space, can't modify input?** Not possible in general for arbitrary values; if values are in [1, n], use index marking or Floyd's cycle: [LC 0287 Find the Duplicate Number](../../06-linked-list/0287-find-the-duplicate-number/)
- **Return the duplicate values:** same set, collect instead of returning.
