---
number: 139
title: Word Break
difficulty: Medium
topic: 1-D Dynamic Programming
pattern: Prefix DP + dictionary
link: https://leetcode.com/problems/word-break/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0140 Word Break II", "0472 Concatenated Words", "0091 Decode Ways"]
---

# 0139. Word Break

## ⚡ 30-Second Summary
**Pattern:** Prefix DP over split points
**Key insight:** `dp[i]` = "the first i characters can be split". It's true if some dictionary word `w` ends exactly at i and `dp[i - len(w)]` is true. Plain recursion re-explores the same suffixes exponentially; caching per position fixes it.
**Go-to:** Bottom-up boolean DP, O(n·W·L) time, O(n) space

## Problem
Given a string s and a list of words, decide whether s can be cut into pieces that are all dictionary words. Words may be reused. [LeetCode](https://leetcode.com/problems/word-break/)

**Examples:**
```
Input:  s = "leetcode", wordDict = ["leet","code"]
Output: true
Why:    leet + code.

Input:  s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Why:    apple + pen + apple. Reusing "apple" is allowed.

Input:  s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
Why:    Both "cats|and" and "cat|sand" leave "og", which no word covers.
```

**Constraints:**
- n ≤ 300, up to 1000 words of length ≤ 20, so O(n·W·L) ≈ 6·10⁶.
- Dictionary words are unique; everything is lowercase.

## Hints
<details><summary>Hint 1</summary>
Greedy longest match fails: try "cars" with ["car","ca","rs"]. What do you need to remember to avoid retrying the same work?
</details>
<details><summary>Hint 2</summary>
Whether the rest of the string from position i can be split doesn't depend on how you got to i. What's the state?
</details>
<details><summary>Hint 3</summary>
dp[0] = true. For each i from 1 to n, dp[i] is true if some word w has len(w) ≤ i, dp[i - len(w)] true, and s ends with w at i. Return dp[n].
</details>

## Clarifying Questions
- Can words be reused? (Yes.)
- Empty string? (n ≥ 1 per LC; dp[0] = true would return true.)
- Do I need the actual split or just yes/no? (Yes/no. Listing all splits is LC 140.)
- Dictionary size vs word length: which is bigger? (It decides whether to loop over words or over split points.)

## Example Walkthrough
"cars", ["car","ca","rs"]: greedy grabs "car" and is stuck on "s". DP: dp[2] = true ("ca"), dp[3] = true ("car"), and dp[4] = true because "rs" ends at 4 and dp[2] is true.

## Approaches

### 1. Plain Recursion: exponential, O(n) space
Try every word that matches at position i, recurse on the rest. "aaaa…ab" with ["a","aa","aaa"] explores every composition of the a's before failing.

### 2. Memoized Recursion: O(n·W·L) time, O(n) space
Same recursion, caching the result per start index. Each index is solved once.

### 3. Bottom-up Prefix DP ⭐ Go-to: O(n·W·L) time, O(n) space
Fill dp[0..n] left to right, checking each word as the last piece.
**Why it's the go-to:** iterative, no recursion limits, and the state is easy to explain.

## Dry Run (Approach 3)
"cars", dict ["car","ca","rs"].

| i | prefix | word checked as last piece | dp[i - len] | dp[i] |
|---|--------|----------------------------|-------------|-------|
| 0 | "" | | | T |
| 1 | "c" | all longer than 1 | | F |
| 2 | "ca" | "ca" ✓ | dp[0] = T | T |
| 3 | "car" | "car" ✓ | dp[0] = T | T |
| 4 | "cars" | "car": "ars" ✗, "ca": "rs" ✗, "rs" ✓ | dp[2] = T | **T** |

## Edge Case Check
- No word matches the ending (example 3): dp[n] stays false. ✅
- Pathological "aaa…ab": DP is still O(n·W·L); only plain recursion blows up. ✅
- One word equals s: dp[n] via dp[0]. ✅

## ⚠️ Pitfalls
- **Greedy longest match** fails ("cars").
- **Off-by-one on dp size:** n + 1 entries, dp[0] = true.
- **C++ substr in the inner loop** allocates; `s.compare(pos, len, w)` doesn't.
- **Python `@cache` on a closure** holding s and the word list works; don't put the list itself in the arguments (lists aren't hashable).

## 🎯 What the Interviewer Wants
- Show why plain recursion is exponential, then add memoization.
- A clear dp[i] definition and base case.
- Complexity in terms of n, W and L, plus the trie or "max word length" optimization.

## Follow-ups
- **Return all sentences:** LC 0140 Word Break II (not added yet). Memoized DFS returning lists.
- **Words made of other words in the list:** LC 0472 Concatenated Words (not added yet). Word Break per word.
- **Faster matching:** put the dictionary in a trie and walk forward from each true dp index.
- **Similar segmentation DP on digits:** [LC 0091 Decode Ways](../0091-decode-ways/)
