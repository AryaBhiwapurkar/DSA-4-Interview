---
number: 680
title: Valid Palindrome II
difficulty: Easy
topic: Two Pointers
pattern: Converging pointers with one skip
link: https://leetcode.com/problems/valid-palindrome-ii/
lists: [Interview Extras]
followup_of: ["0125 Valid Palindrome"]
related: ["0125 Valid Palindrome", "1216 Valid Palindrome III", "0009 Palindrome Number"]
---

# 0680. Valid Palindrome II

## ⚡ 30-Second Summary
**Pattern:** Two pointers; at the first mismatch, try both deletions
**Key insight:** Move lo and hi inward while their characters match. At the first mismatch one of them must go, and you can't tell which yet. So check whether `s[lo+1..hi]` **or** `s[lo..hi−1]` is a plain palindrome. Only one deletion is allowed, so there's no deeper branching. That keeps it O(n).
**Go-to:** Two pointers + one branch, O(n) time, O(1) space

## Problem
Decide whether a string can become a palindrome by deleting at most one character. [LeetCode](https://leetcode.com/problems/valid-palindrome-ii/)

**Examples:**
```
Input:  s = "aba"
Output: true
Why:    Already a palindrome.

Input:  s = "abca"
Output: true
Why:    Delete 'b' or 'c'.

Input:  s = "abc"
Output: false
Why:    Two deletions would be needed.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so trying every deletion (O(n²)) is too slow.
- Lowercase letters.

## Hints
<details><summary>Hint 1</summary>
Check from both ends as usual. When does the one allowed deletion actually matter?
</details>
<details><summary>Hint 2</summary>
At the first mismatch, either the left or the right character is the extra one. What do you check for each case?
</details>
<details><summary>Hint 3</summary>
At the first s[lo] ≠ s[hi], return isPal(lo+1, hi) or isPal(lo, hi−1). If you never mismatch, return true.
</details>

## Clarifying Questions
- At most one deletion, so zero is fine? (Yes.)
- Case-sensitive, only letters? (Lowercase letters only.)
- Return just yes/no? (Yes.)

## Example Walkthrough
`"deeee"`: d vs e mismatch at (0,4). Skipping the left gives "eeee" ✓, so true. Skipping the right gives "deee" ✗. You need both options, because sometimes only one of them works.

## Approaches

### 1. Try Every Deletion: O(n²) time, O(n) space
For each i, remove s[i] and test for a palindrome. Too slow for 10⁵.

### 2. Two Pointers + One Branch ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** linear, and it shows you understand that the mismatch pins down where the deletion must be.

## Dry Run (Approach 2)
`"abca"`

| lo | hi | s[lo] | s[hi] | action |
|----|----|-------|-------|--------|
| 0 | 3 | a | a | move in |
| 1 | 2 | b | c | mismatch → check "c" (2..2) ✓ → **true** |

## Edge Case Check
- Already a palindrome → true, no branch. ✅
- n ≤ 2 → always true. ✅
- `"cbbcc"` → mismatch at (1,3); skipping the right leaves "bb" ✓ → true. ✅

## ⚠️ Pitfalls
- **Greedy single choice** (always skip left) fails on `"eeeed"`: skipping the left leaves "eeed" ✗, while skipping the right leaves "eeee" ✓. Try both.
- **Allowing more than one deletion** through recursion turns it into LC 1216 and costs more.
- **Building substrings** (`s[lo+1:hi+1]`) makes it O(n) extra space. Fine, but index-based checks are O(1).

## 🎯 What the Interviewer Wants
- The two-option branch at the first mismatch.
- Linear time with constant space.
- A clear argument that one branch level is enough.

## Follow-ups
- **No deletions, ignore non-alphanumerics:** [LC 0125 Valid Palindrome](../0125-valid-palindrome/)
- **Up to k deletions:** LC 1216 Valid Palindrome III (not added yet). It's n − LPS(s) ≤ k, with longest palindromic subsequence DP in O(n²).
