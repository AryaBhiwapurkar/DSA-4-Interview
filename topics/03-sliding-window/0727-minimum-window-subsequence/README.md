---
number: 727
title: Minimum Window Subsequence
difficulty: Hard
topic: Sliding Window
pattern: Forward match, backward shrink (or DP of latest start)
link: https://leetcode.com/problems/minimum-window-subsequence/
lists: [Interview Extras]
followup_of: ["0076 Minimum Window Substring"]
related: ["0076 Minimum Window Substring", "0392 Is Subsequence", "0792 Number of Matching Subsequences"]
---

# 0727. Minimum Window Subsequence

## ⚡ 30-Second Summary
**Pattern:** Scan forward until s2 is matched as a subsequence, then scan backward to tighten the start
**Key insight:** Walking right, match s2's characters in order. When the last one matches at `end`, walk left from `end` matching s2 backwards. That finds the **latest** possible start for a window ending at end, which is the shortest one. Record it, then restart the forward scan at `start + 1`. Unlike 0076, order matters, so a count map doesn't work.
**Go-to:** Forward-backward two pointers, O(|s1| · |s2|) worst time, O(1) space

## Problem
Find the shortest contiguous substring of s1 that contains s2 as a subsequence (s2's letters in order, gaps allowed). If several have the same length, return the left-most. Return "" if none exists. LeetCode Premium. [LeetCode](https://leetcode.com/problems/minimum-window-subsequence/)

**Examples:**
```
Input:  s1 = "abcdebdde", s2 = "bde"
Output: "bcde"
Why:    "bcde" contains b..d..e in order; "bdde" ties in length but starts later.

Input:  s1 = "jmeqksfrsdcmsiwvaovztaqenprpvnbstl", s2 = "u"
Output: ""
Why:    There's no 'u' in s1.
```

**Constraints:**
- |s1| ≤ 2·10⁴, |s2| ≤ 100, so O(|s1| · |s2|) = 2·10⁶ is fine.

## Hints
<details><summary>Hint 1</summary>
Why doesn't the 0076 count-map window work here?
</details>
<details><summary>Hint 2</summary>
Once you've matched all of s2 ending at some index, how do you find the shortest window that ends exactly there?
</details>
<details><summary>Hint 3</summary>
Forward: advance j through s2 as s1[i] matches. When j == |s2|, walk k left from i matching s2 backwards; the window is [k+1, i]. Record it if shorter, then resume the forward scan at k + 2 with j = 0.
</details>

## Clarifying Questions
- Ties? (Left-most window wins.)
- No match? (Return "".)
- Order matters? (Yes, subsequence, not multiset.)

## Example Walkthrough
`s1 = "abcdebdde", s2 = "bde"`. Forward: b@1, d@3, e@4 → end 4. Backward from 4: e@4, d@3, b@1 → window [1,4] = "bcde". Restart at 2: d? no, the next b is @5, d@6, e@8 → end 8. Backward: e@8, d@7, b@5 → [5,8] = "bdde", the same length, so keep the earlier one.

## Approaches

### 1. DP of Latest Start: O(|s1| · |s2|) time, O(|s2|) space
`start[j]` = latest index in s1 where a match of s2[0..j] can begin, given the prefix of s1 scanned so far. For each s1[i], go j from high to low: if s1[i] == s2[j], set start[j] = (j == 0 ? i : start[j − 1]). After each i, if start[last] ≥ 0, the window [start[last], i] is a candidate.

### 2. Forward-Backward ⭐ Go-to: O(|s1| · |s2|) worst time, O(1) space
**Why it's the go-to:** no tables, an intuitive "stretch then tighten" picture, and it naturally prefers the left-most window.

## Dry Run (Approach 2)
`s1 = "abcdebdde", s2 = "bde"`

| phase | scan | match positions | window | best |
|-------|------|-----------------|--------|------|
| forward | i = 0..4 | b1, d3, e4 | end = 4 | |
| backward | k = 4..1 | e4, d3, b1 | [1,4] "bcde" | "bcde" |
| forward | i = 2..8 | b5, d6, e8 | end = 8 | |
| backward | k = 8..5 | e8, d7, b5 | [5,8] "bdde" | tie, keep "bcde" |
| forward | i = 6..8 | no full match | | **"bcde"** |

## Edge Case Check
- s2 has a character not in s1 → "". ✅
- s2 == s1 → s1. ✅
- s2 of length 1 → first occurrence. ✅

## ⚠️ Pitfalls
- **Using a count map (0076):** it ignores order.
- **Restarting at end + 1 instead of start + 1** misses overlapping windows that start inside the last one.
- **`<=` when recording:** it replaces the left-most window with a later tie. Use strict `<`.

## 🎯 What the Interviewer Wants
- Recognise that subsequence order kills the count-map idea.
- The tighten-backwards trick, or the DP.
- Correct tie-breaking and restart point.

## Follow-ups
- **Order doesn't matter (multiset):** [LC 0076 Minimum Window Substring](../0076-minimum-window-substring/)
- **Just check a subsequence:** [LC 0392 Is Subsequence](../../02-two-pointers/0392-is-subsequence/)
- **Many subsequence queries:** [LC 0792 Number of Matching Subsequences](../../02-two-pointers/0792-number-of-matching-subsequences/)
