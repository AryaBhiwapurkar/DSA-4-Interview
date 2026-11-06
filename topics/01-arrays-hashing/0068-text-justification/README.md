---
number: 68
title: Text Justification
difficulty: Hard
topic: Arrays & Hashing
pattern: Greedy line packing + space distribution
link: https://leetcode.com/problems/text-justification/
lists: [LC Top Interview 150]
followup_of: []
related: ["0418 Sentence Screen Fitting", "0006 Zigzag Conversion"]
---

# 0068. Text Justification

## ⚡ 30-Second Summary
**Pattern:** Greedy packing, then distribute spaces
**Key insight:** Greedily put as many words on a line as fit (words + one space between each). Then spread the leftover spaces across the gaps: each gap gets `spaces / gaps`, and the leftmost `spaces % gaps` gaps get one extra. The last line and single-word lines are left-justified instead.
**Go-to:** Greedy simulation, O(total characters) time, O(maxWidth) extra space per line

## Problem
Given words and a width, lay the words out in lines of exactly `maxWidth` characters. Pack as many words per line as fit. Fully justify every line by padding the gaps between words, putting extra spaces in the left gaps when they don't divide evenly. The last line, and any line with a single word, is left-justified and padded on the right. [LeetCode](https://leetcode.com/problems/text-justification/)

**Examples:**
```
Input:  words = ["This","is","an","example","of","text","justification."], maxWidth = 16
Output: ["This    is    an",
         "example  of text",
         "justification.  "]
Why:    Line 1 has 8 letters, so 8 spaces split 4/4; line 2 has 13 letters, 3 spaces split 2/1.

Input:  words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output: ["What   must   be",
         "acknowledgment  ",
         "shall be        "]
Why:    "acknowledgment" is alone on its line, so it's left-justified; so is the last line.

Input:  words = ["Science","is","what","we","understand","well","enough","to","explain",
                 "to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output: ["Science  is  what we",
         "understand      well",
         "enough to explain to",
         "a  computer.  Art is",
         "everything  else  we",
         "do                  "]
Why:    E.g. line 1: 15 letters, 5 spaces over 3 gaps = 2, 2, 1 (extra goes left).
```

**Constraints:**
- 1 ≤ number of words ≤ 300; 1 ≤ each word length ≤ 20.
- Each word length ≤ maxWidth ≤ 100, so every word fits on a line by itself; words have no spaces.

## Hints
<details><summary>Hint 1</summary>
First decide which words go on each line. When does adding the next word fail?
</details>
<details><summary>Hint 2</summary>
For a line with k words and L total letters, how many spaces must be spread, and over how many gaps?
</details>
<details><summary>Hint 3</summary>
gaps = k - 1, spaces = maxWidth - L. Gap g gets spaces/gaps, plus 1 if g < spaces % gaps. Special-case k = 1 and the last line.
</details>

## Clarifying Questions
- Is every word guaranteed to fit in maxWidth? (Yes.)
- How are uneven spaces distributed? (Extra spaces go to the left gaps.)
- How are the last line and single-word lines handled? (Left-justified, padded right.)

## Example Walkthrough
`maxWidth = 16`, first line candidates: "This"(4), "is"(2), "an"(2), "example"(7)
- 4 + 1 + 2 + 1 + 2 = 10 fits; adding " example" makes 18 > 16, stop.
- Letters = 8, spaces = 8, gaps = 2: 4 each → "This    is    an".

## Approaches

### 1. Greedy Packing + Space Distribution ⭐ Go-to: O(N) time, O(maxWidth) per line
For each line: extend j while `letters + (j - i) + len(words[j]) ≤ maxWidth`; then build the line as described.
**Why it's the go-to:** this is a pure simulation; greedy packing is exactly what the problem specifies, so the work is getting the space math and special cases right. (There's no meaningfully different "brute force".)

## Dry Run (Approach 1)
Line 1 of example 3, `maxWidth = 20`: words "Science"(7) "is"(2) "what"(4) "we"(2)

| quantity | value |
|----------|-------|
| letters | 15 |
| gaps | 3 |
| spaces | 20 - 15 = 5 |
| base / extra | 5 / 3 = 1, 5 % 3 = 2 |
| gap sizes | 2, 2, 1 |
| line | "Science␣␣is␣␣what␣we" |

## Edge Case Check
- Single word on a non-last line: left-justify and pad (gaps = 0 would divide by zero). ✅
- Last line with several words: single spaces, padded right. ✅
- A word exactly maxWidth long: its own line, no padding. ✅

## ⚠️ Pitfalls
- **Division by zero** when a line has one word; branch before computing `spaces / gaps`.
- **Fit check off by one:** the next word needs one separating space *plus* its length.
- **Extra spaces to the wrong side:** they go to the leftmost gaps.
- **Forgetting to pad the last line** to exactly maxWidth.

## 🎯 What the Interviewer Wants
- Clean separation: pick words, then format the line.
- Correct integer division/remainder for spaces.
- All special cases handled without a mess of flags.

## Follow-ups
- **How many times does a sentence fit on a screen:** LC 0418 Sentence Screen Fitting (not added yet)
- **Minimize raggedness (Knuth-Plass style):** DP over break points, O(n²), instead of greedy.
- **Center-justify:** split the padding between both sides of the line.
