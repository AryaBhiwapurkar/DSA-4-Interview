---
number: 17
title: Letter Combinations of a Phone Number
difficulty: Medium
topic: Backtracking
pattern: Backtrack over digit map
link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0022 Generate Parentheses", "0078 Subsets", "0046 Permutations"]
---

# 0017. Letter Combinations of a Phone Number

## ⚡ 30-Second Summary
**Pattern:** Backtracking, one decision level per digit
**Key insight:** Each digit is a level of a tree and its letters are the branches. A DFS that picks one letter per digit and records the string at depth n produces every combination exactly once.
**Go-to:** Backtracking, O(4ⁿ · n) time, O(n) extra space (excluding output)

## Problem
Given a string of digits 2-9, return every letter string it could spell on a phone keypad (2 = abc, 3 = def, ..., 7 = pqrs, 9 = wxyz). Any order. [LeetCode](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)

**Examples:**
```
Input:  digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Why:    3 letters for 2 times 3 letters for 3 gives 9 strings.

Input:  digits = ""
Output: []
Why:    No digits means nothing to spell, not one empty string.

Input:  digits = "2"
Output: ["a","b","c"]
Why:    One digit, so each of its letters is a full answer.
```

**Constraints:**
- 0 ≤ digits.length ≤ 4 (the empty case appears in older versions), digits in '2'..'9'.
- Output size is at most 4⁴ = 256, so exponential is expected.

## Hints
<details><summary>Hint 1</summary>
Draw the choices as a tree: the first level picks a letter for digit 1, the next for digit 2...
</details>
<details><summary>Hint 2</summary>
A recursive function `dfs(i, path)` handles digit i. What does it do when i equals the length?
</details>
<details><summary>Hint 3</summary>
At depth n, save path. Otherwise loop over the letters of digits[i]: append, recurse with i+1, pop. Return [] up front for empty input.
</details>

## Clarifying Questions
- Can digits contain 0 or 1? (No, only 2-9.)
- Empty input: [] or [""]? (Return [].)
- Does output order matter? (No.)

## Example Walkthrough
`"23"`: pick 'a' for 2, then d/e/f for 3 → ad, ae, af. Back up, pick 'b' → bd, be, bf. Then 'c' → cd, ce, cf.

## Approaches

### 1. Iterative Expansion: O(4ⁿ · n) time, O(4ⁿ · n) space
Start with [""]. For each digit, replace the list with every existing string extended by each letter of that digit. Short, but builds every intermediate level.

### 2. Backtracking ⭐ Go-to: O(4ⁿ · n) time, O(n) extra space
DFS over digit positions with a shared path buffer; append a letter, recurse, pop.
**Why it's the go-to:** it is the template for every problem in this topic, and the interviewer usually wants to see it.

## Dry Run (Approach 2)
`digits = "23"`

| call | i | path before | letters tried | action |
|------|---|-------------|---------------|--------|
| dfs | 0 | "" | a, b, c | push 'a' |
| dfs | 1 | "a" | d, e, f | push 'd' |
| dfs | 2 | "ad" | (none) | save "ad", return |
| dfs | 1 | "a" | e | save "ae", then "af" |
| dfs | 0 | "" | b | pop 'a', push 'b' → bd, be, bf |
| dfs | 0 | "" | c | → cd, ce, cf; done (9 strings) |

## Edge Case Check
- `""`: early return gives []. ✅
- Digit with 4 letters ("7", "9"): the map handles it, and "79" gives 16. ✅
- Single digit: 3 or 4 one-letter strings. ✅

## ⚠️ Pitfalls
- **Empty input returns [""]** if you skip the early return (the DFS saves the empty path at depth 0).
- **Forgetting to pop** after recursion leaves stale letters in the path.
- **Index map off by 2:** with an array map, digit d is at `map[d - '0']` with entries for 0 and 1 left empty.
- **Go:** appending to a shared `[]byte` path is fine, but copy it with `string(path)` when saving.

## 🎯 What the Interviewer Wants
- The choose / explore / unchoose template.
- A correct complexity: 4ⁿ leaves, each costing O(n) to copy.
- The empty-input edge case without being told.

## Follow-ups
- **Generate balanced parentheses:** [LC 0022 Generate Parentheses](../../04-stack/0022-generate-parentheses/)
- **Count only, no listing:** multiply the letter counts per digit.
- **Only return combinations that are dictionary words:** prune with a trie (see [LC 0208](../../08-tries/0208-implement-trie-prefix-tree/)).
