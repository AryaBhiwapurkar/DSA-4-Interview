---
number: 5
title: Longest Palindromic Substring
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Expand around center
link: https://leetcode.com/problems/longest-palindromic-substring/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0647 Palindromic Substrings", "0516 Longest Palindromic Subsequence", "0131 Palindrome Partitioning"]
---

# 0005. Longest Palindromic Substring

## ⚡ 30-Second Summary
**Pattern:** Expand around every center
**Key insight:** Every palindrome is symmetric around a center, which is either a character (odd length) or the gap between two characters (even length). That's 2n-1 centers; expand each while both ends match.
**Go-to:** Expand around center, O(n²) time, O(1) space

## Problem
Given a string, return its longest substring (contiguous) that is a palindrome. [LeetCode](https://leetcode.com/problems/longest-palindromic-substring/)

**Examples:**
```
Input:  s = "babad"
Output: "bab"
Why:    "bab" and "aba" both have length 3, and either is accepted. Nothing of length 4 or 5 is a palindrome.

Input:  s = "cbbd"
Output: "bb"
Why:    The only palindrome longer than one letter is the even-length "bb" in the middle.
```

**Constraints:**
- 1 ≤ n ≤ 1000, so O(n²) = 10⁶ is fine and O(n³) is borderline.
- Digits and English letters only.

## Hints
<details><summary>Hint 1</summary>
Checking every substring is O(n³). If s[i..j] is a palindrome, what does that tell you about s[i+1..j-1]?
</details>
<details><summary>Hint 2</summary>
Instead of choosing both ends, choose the middle and grow outwards. How many possible middles are there?
</details>
<details><summary>Hint 3</summary>
For each i, expand from (i, i) for odd lengths and from (i, i+1) for even lengths while s[l] == s[r]. The length is r - l - 1 after the loop. Keep the best start and length.
</details>

## Clarifying Questions
- Substring (contiguous) or subsequence? (Substring. The subsequence version is LC 516, a 2-D DP.)
- If several have the same length, which one? (Any.)
- Case-sensitive? Spaces? (Only letters/digits; treat as-is.)

## Example Walkthrough
"cbbd": odd centers give only single letters. The even center between the two b's: b = b, expand to c vs d, mismatch. Length 2 → "bb".

## Approaches

### 1. Brute Force: O(n³) time, O(1) space
Check every substring, longest kept. Skipping lengths that can't beat the current best helps, but the worst case stays cubic.

### 2. DP Table by Length: O(n²) time, O(n²) space
`pal[i][j] = s[i] == s[j] && (j - i < 2 || pal[i+1][j-1])`. Fill by increasing length so the inner part is ready. This is the classic DP answer, but it uses 10⁶ booleans.

### 3. Expand Around Center ⭐ Go-to: O(n²) time, O(1) space
2n-1 centers, each expanded in O(n).
**Why it's the go-to:** same time as the DP, constant space, and less code. Manacher's is O(n) but not expected in interviews.

## Dry Run (Approach 3)
"babad".

| i | odd expand (i,i) | even expand (i,i+1) | len | best (start, len) |
|---|------------------|---------------------|-----|-------------------|
| 0 | "b"; then (-1,1) out | b≠a → 0 | 1 | (0, 1) "b" |
| 1 | "a" → (0,2) b=b → "bab"; (-1,3) out | a≠b → 0 | 3 | (0, 3) "bab" |
| 2 | "b" → (1,3) a=a → "aba"; (0,4) b≠d | b≠a → 0 | 3 | not > 3, keep "bab" |
| 3 | "a" → (2,4) b≠d | a≠d → 0 | 1 | keep |
| 4 | "d" | out | 1 | keep |

Answer **"bab"**.

## Edge Case Check
- Single char: "a". ✅
- No repeats ("ac"): best length 1, first char "a". ✅
- Even-length answer ("cbbd"): needs the (i, i+1) center. ✅
- Whole string is a palindrome: center expands to both ends. ✅

## ⚠️ Pitfalls
- **Forgetting even-length centers** misses "bb" / "abba".
- **Start index:** `i - (len - 1) / 2` works for both parities; deriving it per case invites off-by-ones.
- **C++ `substr(pos, len)`** takes a length; Python slices take an end index.
- **Python `[[False]*n]*n`** aliases rows in the DP table.

## 🎯 What the Interviewer Wants
- Spot the center idea, including even centers.
- Mention the O(n²) DP and why expand-around-center saves space.
- Know Manacher's exists (O(n)) without being expected to code it.

## Follow-ups
- **Count all palindromic substrings:** [LC 0647 Palindromic Substrings](../0647-palindromic-substrings/)
- **Longest palindromic subsequence:** LC 0516 Longest Palindromic Subsequence (not added yet). 2-D DP, or LCS of s and reverse(s).
- **Split into palindromes:** [LC 0131 Palindrome Partitioning](../../10-backtracking/0131-palindrome-partitioning/)
- **O(n):** Manacher's algorithm.
