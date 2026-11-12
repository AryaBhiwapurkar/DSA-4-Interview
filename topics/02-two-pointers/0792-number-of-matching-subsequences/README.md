---
number: 792
title: Number of Matching Subsequences
difficulty: Medium
topic: Two Pointers
pattern: Bucket words by next needed char (or binary search on positions)
link: https://leetcode.com/problems/number-of-matching-subsequences/
lists: [Interview Extras]
followup_of: ["0392 Is Subsequence"]
related: ["0392 Is Subsequence", "1055 Shortest Way to Form String", "0524 Longest Word in Dictionary through Deleting"]
---

# 0792. Number of Matching Subsequences

## ⚡ 30-Second Summary
**Pattern:** Advance all words together through s, using "waiting" buckets
**Key insight:** Checking each word separately with two pointers costs O(|s|) per word. Instead, put every word in a bucket keyed by the next character it needs. Scan s once. For each character c, take every word waiting on c and advance it one step, then re-bucket it by its new next character, or count it as finished. Each word character is handled once.
**Go-to:** Waiting buckets, O(|s| + total word length) time, O(number of words) space

## Problem
Count how many words in the list are subsequences of s: their letters appear in s in order, not necessarily next to each other. [LeetCode](https://leetcode.com/problems/number-of-matching-subsequences/)

**Examples:**
```
Input:  s = "abcde", words = ["a","bb","acd","ace"]
Output: 3
Why:    "a", "acd" and "ace" fit in order; "bb" needs two b's.

Input:  s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
Output: 2
Why:    "ahjpjau" and "ja" can be traced in order; the other two need letters s lacks.
```

**Constraints:**
- |s| ≤ 5·10⁴; up to 5000 words of length ≤ 50, so word-by-word two pointers can cost 5000 · 5·10⁴ = 2.5·10⁸.
- Duplicate words count separately.

## Hints
<details><summary>Hint 1</summary>
Checking one word is LC 392. Why is repeating it 5000 times wasteful?
</details>
<details><summary>Hint 2</summary>
Could all the words walk through s at the same time? What does each word need to know?
</details>
<details><summary>Hint 3</summary>
waiting[c] = list of (word, index) pointers whose next needed char is c. For each c in s: take waiting[c], clear it, advance each pointer; if done, count it, else append to waiting[word[idx]].
</details>

## Clarifying Questions
- Do duplicate words count twice? (Yes.)
- Lowercase only? (Yes, so 26 buckets.)
- Is the empty word possible? (No, length ≥ 1.)

## Example Walkthrough
`s = "abcde"`. The buckets start as a: [a, acd, ace] and b: [bb]. Reading 'a': "a" is finished (count 1), "acd" moves to c, "ace" moves to c. Reading 'b': "bb" now waits on b again, but this 'b' was already consumed. Reading 'c': "acd" → d, "ace" → e. 'd' finishes "acd" (2). 'e' finishes "ace" (3). "bb" never finishes.

## Approaches

### 1. Two Pointers per Word: O(W · |s|) worst time, O(1) space
LC 392 for each word. Simple; with caching of duplicate words it's often enough.

### 2. Binary Search on Positions: O(|s| + Σ L · log |s|) time, O(|s|) space
Precompute the sorted index list for each character. For each word, jump to the next index greater than the current one with `upper_bound`.

### 3. Waiting Buckets ⭐ Go-to: O(|s| + Σ L) time, O(W) space
**Why it's the go-to:** linear in the input, with no binary search, and the "process all queries in one pass" idea is reusable.

## Dry Run (Approach 3)
`s = "abcde"`, words ["a","bb","acd","ace"] (shown as word@nextIndex)

| char | taken from bucket | moved to | done count |
|------|-------------------|----------|------------|
| start | | a: [a@0, acd@0, ace@0], b: [bb@0] | 0 |
| a | a@0, acd@0, ace@0 | a done; c: [acd@1, ace@1] | 1 |
| b | bb@0 | b: [bb@1] | 1 |
| c | acd@1, ace@1 | d: [acd@2], e: [ace@2] | 1 |
| d | acd@2 | done | 2 |
| e | ace@2 | done | **3** |

## Edge Case Check
- A word longer than s → never finishes. ✅
- A word with a letter missing from s → stuck in its bucket. ✅
- Duplicate words → each pointer advances separately. ✅

## ⚠️ Pitfalls
- **Re-bucketing into the bucket you're iterating** (a word needing the same char again, like "bb"). Swap the bucket out first, so the same s-character isn't reused.
- **Copying word strings** into buckets is costly. Store (word index, position) pairs.
- **Binary search with `lower_bound`** instead of `upper_bound` reuses the same position for a repeated letter.

## 🎯 What the Interviewer Wants
- Start from LC 392, then spot the repeated work.
- Either the bucket or the binary-search optimisation, with complexity.
- Correct handling of repeated letters.

## Follow-ups
- **Single word:** [LC 0392 Is Subsequence](../0392-is-subsequence/)
- **Fewest copies of s to form a target:** LC 1055 Shortest Way to Form String (not added yet). Same next-position table.
- **Longest dictionary word that's a subsequence:** LC 0524 Longest Word in Dictionary through Deleting (not added yet)
