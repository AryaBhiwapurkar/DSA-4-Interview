---
number: 647
title: Palindromic Substrings
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Expand around center
link: https://leetcode.com/problems/palindromic-substrings/
lists: [NeetCode 150]
followup_of: ["0005 Longest Palindromic Substring"]
related: ["0516 Longest Palindromic Subsequence", "0131 Palindrome Partitioning"]
---

# 0647. Palindromic Substrings

## ⚡ 30-Second Summary
**Pattern:** Expand around every center, counting
**Key insight:** Same centers as LC 5 (2n-1 of them). Each successful expansion step from a center is one more palindrome, so count steps instead of tracking the longest.
**Go-to:** Expand around center, O(n²) time, O(1) space

## Problem
Count how many substrings of s are palindromes. Two substrings with the same letters but different start or end positions count as different. [LeetCode](https://leetcode.com/problems/palindromic-substrings/)

**Examples:**
```
Input:  s = "abc"
Output: 3
Why:    Only the three single letters.

Input:  s = "aaa"
Output: 6
Why:    Three "a", two "aa" (positions 0-1 and 1-2), one "aaa".
```

**Constraints:**
- 1 ≤ n ≤ 1000: O(n²) is expected. The count is at most n(n+1)/2 ≈ 5·10⁵.
- Lowercase letters only.

## Hints
<details><summary>Hint 1</summary>
This is LC 5, but counting every palindrome instead of keeping the longest one. What made LC 5 efficient?
</details>
<details><summary>Hint 2</summary>
If you expand from a center and the ends keep matching, how many palindromes did you find along the way?
</details>
<details><summary>Hint 3</summary>
For each i, expand from (i, i) and (i, i+1). Add 1 for every step where s[l] == s[r], then move l--, r++. Sum over all centers.
</details>

## Clarifying Questions
- Do identical substrings at different positions count separately? (Yes.)
- Are single characters palindromes? (Yes, each counts.)
- Empty substring? (Not counted.)

## Example Walkthrough
"abba": the four single letters count 4. No odd center grows past one letter (center 1 compares a vs b, center 2 compares b vs a). Even centers: (0,1) a≠b, (1,2) "bb" ✓ then (0,3) "abba" ✓, (2,3) b≠a. That adds 2, so the total is 6.

## Approaches

### 1. Brute Force: O(n³) time, O(1) space
Check every substring with two pointers.

### 2. DP Table by Length: O(n²) time, O(n²) space
Same `pal[i][j]` table as LC 5; count the true cells.

### 3. Expand Around Center ⭐ Go-to: O(n²) time, O(1) space
Sum successful expansion steps over all 2n-1 centers.
**Why it's the go-to:** constant space and almost no code beyond LC 5's helper.

## Dry Run (Approach 3)
"aaa".

| i | odd (i,i) steps | even (i,i+1) steps | running total |
|---|-----------------|--------------------|---------------|
| 0 | (0,0) ✓, (-1,1) out → 1 | (0,1) ✓, (-1,2) out → 1 | 2 |
| 1 | (1,1) ✓, (0,2) ✓, (-1,3) out → 2 | (1,2) ✓, (0,3) out → 1 | 5 |
| 2 | (2,2) ✓, (1,3) out → 1 | (2,3) out → 0 | **6** |

## Edge Case Check
- Single char: 1. ✅
- All distinct ("abc"): n. ✅
- All the same: n(n+1)/2. For "aaa", 6. ✅

## ⚠️ Pitfalls
- **Skipping even centers** undercounts "aa", "abba".
- **Counting distinct palindromes** by accident, e.g. with a set. The problem counts positions.
- **DP fill order:** pal[i+1][j-1] must be ready, so go by length (or i descending).

## 🎯 What the Interviewer Wants
- Reuse the LC 5 center idea and adapt it to counting.
- Explain why each expansion step is exactly one palindrome.
- O(n²) time with O(1) space.

## Follow-ups
- **Longest instead of count:** [LC 0005 Longest Palindromic Substring](../0005-longest-palindromic-substring/)
- **Min cuts to split into palindromes:** LC 0132 Palindrome Partitioning II (not added yet). Precompute pal[i][j], then 1-D DP.
- **List all partitions:** [LC 0131 Palindrome Partitioning](../../10-backtracking/0131-palindrome-partitioning/)
