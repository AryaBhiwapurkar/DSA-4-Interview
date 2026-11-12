---
number: 316
title: Remove Duplicate Letters
difficulty: Medium
topic: Stack
pattern: Monotonic stack + last occurrence + in-stack set
link: https://leetcode.com/problems/remove-duplicate-letters/
lists: [Interview Extras]
followup_of: ["0402 Remove K Digits"]
related: ["0402 Remove K Digits", "1081 Smallest Subsequence of Distinct Characters", "0763 Partition Labels"]
---

# 0316. Remove Duplicate Letters

## ⚡ 30-Second Summary
**Pattern:** The Remove K Digits greedy, but a letter may only be dropped if it appears again later
**Key insight:** Build the answer on a stack. For each letter c that isn't already used, pop the top while the top > c **and** the top appears again later (`last[top] > i`). Then push c. Skip letters already in the stack, since an earlier copy is in a position at least as good. Last occurrences and an in-stack set make every step O(1).
**Go-to:** Greedy stack, O(n) time, O(1) space (26 letters)

## Problem
Remove duplicate letters so each letter appears exactly once, choosing the result that is lexicographically smallest among all valid results. The result must keep the original relative order. [LeetCode](https://leetcode.com/problems/remove-duplicate-letters/)

**Examples:**
```
Input:  s = "bcabc"
Output: "abc"
Why:    Every letter repeats later, so the first b and c can go and 'a' can lead.

Input:  s = "cbacdcbc"
Output: "acdb"
Why:    'a' leads; 'd' appears only once, so the 'b' after it must stay after d.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; lowercase letters only.

## Hints
<details><summary>Hint 1</summary>
How did Remove K Digits decide to drop a digit? What extra condition is needed when each letter must appear exactly once?
</details>
<details><summary>Hint 2</summary>
You may drop a bigger letter in front of you only if you'll see it again. How do you know quickly?
</details>
<details><summary>Hint 3</summary>
last[c] = final index of c. For i, c: if c in stack, skip. While stack and top &gt; c and last[top] &gt; i: remove top from the set and pop. Push c and mark it.
</details>

## Clarifying Questions
- Lowercase only? (Yes.)
- Subsequence order preserved? (Yes.)
- Lexicographic over results that contain every distinct letter once? (Yes.)

## Example Walkthrough
`"cbacdcbc"`: last = {a:2, b:6, c:7, d:4}.
- c → [c]. b < c and c recurs → pop c, push b. a < b and b recurs → pop b, push a → [a].
- c → [a,c]. d → [a,c,d]. c is already in the stack, skip.
- b: b < d, but d never recurs (last 4 < 6) → push → [a,c,d,b]. The final c is in the stack, skip.

Result "acdb".

## Approaches

### 1. Recursive Smallest-first Choice: O(26 · n) time
Pick the smallest letter c such that the suffix starting at its first occurrence still contains every distinct letter. Output c, remove all c's from that suffix, and recurse. Clean to reason about, more code.

### 2. Greedy Stack ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** one pass, three small arrays, and it's 0402's template with two extra checks.

## Dry Run (Approach 2)
`"cbacdcbc"`

| i | c | in stack? | pops | stack |
|---|---|-----------|------|-------|
| 0 | c | no | – | c |
| 1 | b | no | c (recurs at 7) | b |
| 2 | a | no | b (recurs at 6) | a |
| 3 | c | no | – | ac |
| 4 | d | no | – | acd |
| 5 | c | yes | skip | acd |
| 6 | b | no | d? last[d]=4 < 6 → stop | acdb |
| 7 | c | yes | skip | **acdb** |

## Edge Case Check
- All distinct → unchanged. ✅
- All the same letter → that letter once. ✅
- Already sorted with duplicates `"aabbcc"` → "abc". ✅

## ⚠️ Pitfalls
- **Not skipping letters already in the stack:** you'd pop good letters to fit a duplicate.
- **Popping without the `last[top] > i` check:** loses a letter for good.
- **Forgetting to clear the in-stack flag** when popping.

## 🎯 What the Interviewer Wants
- The connection to the monotonic-stack greedy.
- Both guards (recurs later, already used), with a justification.
- O(n) with constant alphabet space.

## Follow-ups
- **Identical problem:** LC 1081 Smallest Subsequence of Distinct Characters (not added yet)
- **Without the "exactly once" rule:** [LC 0402 Remove K Digits](../0402-remove-k-digits/)
- **Last-occurrence table used differently:** [LC 0763 Partition Labels](../../15-greedy/0763-partition-labels/)
