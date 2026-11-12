---
number: 418
title: Sentence Screen Fitting
difficulty: Medium
topic: Arrays & Hashing
pattern: Joined-sentence pointer (or per-word DP)
link: https://leetcode.com/problems/sentence-screen-fitting/
lists: [Interview Extras]
followup_of: []
related: ["0068 Text Justification", "0006 Zigzag Conversion"]
---

# 0418. Sentence Screen Fitting

## ⚡ 30-Second Summary
**Pattern:** Treat the sentence as one infinite looping string and jump a row at a time
**Key insight:** Join the words into `s = "w1 w2 … wk "` (trailing space included), of length L. Track `pos`, the number of characters of the infinite repetition placed so far. Each row adds `cols` to pos. If `s[pos % L]` is a space, the row ended exactly at a word boundary, so skip that space (`pos++`). Otherwise the row cut a word, so back up until just after a space. The answer is `pos / L` complete sentences.
**Go-to:** Joined-string pointer, O(rows · maxWordLen) time, O(L) space

## Problem
A screen has `rows` lines of `cols` characters. Write the sentence (a list of words) repeatedly. A word can't be split across lines, consecutive words on a line need one space between them, and a line may start any word. Return how many times the whole sentence fits. LeetCode Premium. [LeetCode](https://leetcode.com/problems/sentence-screen-fitting/)

**Examples:**
```
Input:  rows = 2, cols = 8, sentence = ["hello","world"]
Output: 1
Why:    "hello---" / "world---": one full sentence.

Input:  rows = 3, cols = 6, sentence = ["a","bcd","e"]
Output: 2
Why:    "a-bcd-" / "e-a---" / "bcd-e-": the sentence completes twice.

Input:  rows = 4, cols = 5, sentence = ["i","had","apple","pie"]
Output: 1
Why:    "i-had" / "apple" / "pie-i" / "had--": one full pass.
```

**Constraints:**
- 1 ≤ rows, cols ≤ 2·10⁴; up to 100 words, each 1–10 letters.
- A word longer than cols can never be placed, so the answer is 0.

## Hints
<details><summary>Hint 1</summary>
Simulating word by word is up to rows · cols steps. What if you think of the sentence as one long repeating string?
</details>
<details><summary>Hint 2</summary>
After filling a row of cols characters, where can the next row start? What if the row's last character is mid-word?
</details>
<details><summary>Hint 3</summary>
s = " ".join(words) + " ". For each row: pos += cols; if s[pos % L] == ' ': pos += 1; else while pos &gt; 0 and s[(pos − 1) % L] != ' ': pos −= 1. Answer pos // L.
</details>

## Clarifying Questions
- Can a word split across lines? (No.)
- Is a trailing space needed at the end of a line? (No; spaces only separate words on the same line.)
- What if a word is longer than cols? (Then nothing fits → 0.)

## Example Walkthrough
`rows = 2, cols = 8, ["hello","world"]` → s = "hello world " (L = 12). Row 1: pos jumps to 8, landing on 'r' in the middle of "world", so back up to pos 6, the start of "world". Row 1 holds "hello". Row 2: pos jumps to 14, landing on 'l' (index 2) mid-"hello", so back up to 12. Row 2 holds "world". 12 // 12 = **1** sentence.

## Approaches

### 1. Word-by-word Simulation: O(rows · cols) worst time, O(1) space
For each row, keep placing words (plus a space) while they fit; count wraps of the word index. Simple, but slow with many tiny words.

### 2. Joined-string Pointer ⭐ Go-to: O(rows · maxWordLen) time, O(L) space
**Why it's the go-to:** each row is one jump plus a short back-up of at most one word's length, and the code is five lines.

(A DP alternative: for each starting word, precompute the next starting word and the sentences completed in one row. Then walk rows in O(1) each.)

## Dry Run (Approach 2)
`rows = 3, cols = 6, ["a","bcd","e"]` → s = "a bcd e " (L = 8; indices 0..7 = a,␣,b,c,d,␣,e,␣)

| row | pos + cols | char at (pos % L) | adjust | pos after | row content |
|-----|------------|-------------------|--------|-----------|-------------|
| 1 | 6 | 'e' (index 6), but s[5] is ' ' | word starts here, no back-up | 6 | "a bcd" |
| 2 | 12 | 'd' (index 4), mid-word | back up to just after the space at index 1 | 10 | "e a" |
| 3 | 16 | 'a' (index 0), s[7] is ' ' | word starts here | 16 | "bcd e" |

16 // 8 = **2** sentences.

## Edge Case Check
- A word longer than cols → pos never advances past it → 0. ✅
- The sentence fits exactly on one row → s[pos % L] is a space every time → rows sentences. ✅
- A single word repeated → back-up is bounded by the word length. ✅

## ⚠️ Pitfalls
- **No trailing space in s:** the boundary between the last and first word disappears.
- **Back-up loop without `pos > 0`** can go negative when the first word doesn't fit.
- **Counting a trailing space as needed at the line end:** a line ending exactly at a word end is fine.

## 🎯 What the Interviewer Wants
- Move from naive simulation to the circular-string trick (or the DP).
- Careful boundary handling at row ends.
- Complexity that doesn't depend on cols per row.

## Follow-ups
- **Full justification of lines:** [LC 0068 Text Justification](../0068-text-justification/)
- **Very many rows:** DP per starting word, and detect the cycle in starting words to skip ahead.
