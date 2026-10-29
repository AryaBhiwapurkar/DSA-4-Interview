---
number: 30
title: Substring with Concatenation of All Words
difficulty: Hard
topic: Sliding Window
pattern: Fixed window per offset + word counts
link: https://leetcode.com/problems/substring-with-concatenation-of-all-words/
lists: [LC Top Interview 150]
followup_of: []
related: ["0076 Minimum Window Substring", "0438 Find All Anagrams in a String", "0567 Permutation in String"]
---

# 0030. Substring with Concatenation of All Words

## ⚡ 30-Second Summary
**Pattern:** Sliding window over word-sized steps, one pass per offset
**Key insight:** All words have the same length w, so any valid start lies on one of w "tracks" (offsets 0..w-1). On each track, treat s as a sequence of w-length tokens and run a sliding window over tokens with word counts, exactly like Permutation in String but with words instead of letters.
**Go-to:** Per-offset token window, O(n·w) time, O(m·w) space

## Problem
Given a string s and an array of equal-length words, return every start index in s where a substring is exactly some concatenation of all the words, each used once (in any order). Return the indices in any order.

**Examples:**
```
Input:  s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Why:    "barfoo" at 0 and "foobar" at 9 are both concatenations of the two words.

Input:  s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Why:    "word" is needed twice, and no window of 16 chars has both copies plus "good" and "best".

Input:  s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
Why:    "foobarthe", "barthefoo", "thefoobar" all use each word once.
```

**Constraints:**
- 1 ≤ |s| ≤ 10⁴; 1 ≤ number of words m ≤ 5000; 1 ≤ word length w ≤ 30.
- Lowercase letters; words may repeat (count them).

## Hints
<details><summary>Hint 1</summary>
Every valid window has length m·w. For a single start, how do you check it?
</details>
<details><summary>Hint 2</summary>
Starts that differ by w share most of their tokens. Which starts can reuse work?
</details>
<details><summary>Hint 3</summary>
For each offset 0..w-1, slide over tokens s[i..i+w): add the token on the right; if it's not a word, reset; if its count exceeds the needed count, drop tokens from the left until it doesn't; when the window has m tokens, record its start.
</details>

## Clarifying Questions
- Are all words the same length? (Yes; that's what makes tokenizing possible.)
- Can words repeat? (Yes; match counts.)
- Overlapping answers allowed? (Yes, return every start.)

## Example Walkthrough
`s = "barfoothefoobarman", words = ["foo","bar"]`, w = 3, window = 6 chars
- Offset 0 tokens: bar foo the foo bar man.
- [bar, foo] valid → start 0. "the" isn't a word → reset. [foo, bar] valid → start 9. "man" → reset.
- Offsets 1 and 2 produce no valid windows. Answer [0, 9].

## Approaches

### 1. Check Every Start: O(n·m·w) time, O(m·w) space
For each start i, split the next m·w chars into m tokens and compare counts with words. Simple; can be slow at the limits.

### 2. Per-Offset Token Window ⭐ Go-to: O(n·w) time, O(m·w) space
w passes; each pass moves left and right in steps of w, so each token is added and removed once per pass.
**Why it's the go-to:** it reuses the window counts between overlapping starts, and the structure is exactly the familiar count-window template.

## Dry Run (Approach 2)
`s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]`, offset 0, need = {bar:1, foo:1, the:1}

| token start | token | window (after) | count > need? | valid start |
|-------------|-------|----------------|---------------|-------------|
| 0 | bar | bar | no | |
| 3 | foo | bar foo | no | |
| 6 | foo | foo (dropped bar, foo) | yes → shrink | |
| 9 | bar | foo bar | no | |
| 12 | the | foo bar the | no | 6 |
| 15 | foo | bar the foo | yes → drop foo | 9 |
| 18 | bar | the foo bar | yes → drop bar | 12 |
| 21 | man | - (reset) | not a word | |

## Edge Case Check
- s shorter than m·w: no windows, []. ✅
- Duplicate words: counts handle them (example 2). ✅
- A word that is never in s: no window ever fills. ✅

## ⚠️ Pitfalls
- **Only scanning offset 0:** valid starts can be at any offset mod w.
- **Not resetting on an unknown token:** a non-word breaks every window containing it.
- **Shrinking only once when a count overflows:** shrink until that word's count is back to the limit.
- **Building substrings is O(w)**; that's where the w factor comes from.

## 🎯 What the Interviewer Wants
- See that equal word length lets you tokenize.
- Run the count window over tokens, once per offset.
- Handle duplicates and resets correctly.

## Follow-ups
- **Single characters instead of words:** [LC 0567 Permutation in String](../0567-permutation-in-string/) / LC 0438 (not added yet)
- **Variable-size window covering a multiset:** [LC 0076 Minimum Window Substring](../0076-minimum-window-substring/)
- **Words of different lengths:** tokenizing no longer works; needs a trie/DP over positions.
