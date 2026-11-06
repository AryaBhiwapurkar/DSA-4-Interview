---
number: 205
title: Isomorphic Strings
difficulty: Easy
topic: Arrays & Hashing
pattern: Two-way mapping
link: https://leetcode.com/problems/isomorphic-strings/
lists: [LC Top Interview 150]
followup_of: []
related: ["0290 Word Pattern", "0890 Find and Replace Pattern"]
---

# 0205. Isomorphic Strings

## ⚡ 30-Second Summary
**Pattern:** Two-way (bijective) mapping
**Key insight:** The character map must be one-to-one in BOTH directions. One map catches "a→x then a→y"; you need a second map to catch "a→x and b→x".
**Go-to:** Two maps (s→t and t→s), O(n) time, O(1) space (bounded alphabet)

## Problem
Two strings of equal length are isomorphic if you can replace every character in `s` consistently to get `t`, where no two different characters of `s` map to the same character of `t` (a character may map to itself). Return whether `s` and `t` are isomorphic. [LeetCode](https://leetcode.com/problems/isomorphic-strings/)

**Examples:**
```
Input:  s = "egg", t = "add"
Output: true
Why:    e→a and g→d, applied consistently.

Input:  s = "foo", t = "bar"
Output: false
Why:    'o' would have to map to both 'a' and 'r'.

Input:  s = "paper", t = "title"
Output: true
Why:    p→t, a→i, e→l, r→e, with no conflicts either way.
```

**Constraints:**
- 1 ≤ |s| ≤ 5·10⁴ and |t| = |s|.
- Any valid ASCII character, so a 256-slot array or a hashmap works.

## Hints
<details><summary>Hint 1</summary>
Build the mapping s[i] → t[i] as you go. When does it become invalid?
</details>
<details><summary>Hint 2</summary>
"badc" vs "baba": every s char maps consistently, yet the answer is false. Why?
</details>
<details><summary>Hint 3</summary>
Keep a reverse map t → s as well, and check both on every index.
</details>

## Clarifying Questions
- Are lengths always equal? (Yes here; otherwise return false.)
- Character set: ASCII or Unicode?
- Can a character map to itself? (Yes.)

## Example Walkthrough
`s = "badc", t = "baba"`
- b→b, a→a, d→b: forward map is fine (d is new), but reverse says b already came from b, not d. Conflict, false.

## Approaches

### 1. First-Occurrence Signature: O(n) time, O(n) space
Replace each character by the index of its first occurrence in its own string ("egg" → [0,1,1], "add" → [0,1,1]). Isomorphic iff the signatures match. Elegant, but builds two extra arrays.

### 2. Two Maps ⭐ Go-to: O(n) time, O(1) space
Walk both strings; if `s[i]` is mapped, it must map to `t[i]`; if `t[i]` is mapped back, it must map to `s[i]`. Otherwise record both directions.
**Why it's the go-to:** one pass, early exit, and it makes the bijection explicit, which is exactly what the interviewer is probing.

## Dry Run (Approach 2)
`s = "foo", t = "bar"`

| i | s[i] | t[i] | s→t (before) | t→s (before) | ok? |
|---|------|------|--------------|--------------|-----|
| 0 | f | b | {} | {} | yes, add f→b, b→f |
| 1 | o | a | {f:b} | {b:f} | yes, add o→a, a→o |
| 2 | o | r | {f:b, o:a} | {b:f, a:o} | o maps to a, not r: false |

## Edge Case Check
- Single char: always true. ✅
- `"badc"`/`"baba"`: caught by the reverse map. ✅
- Char mapping to itself, `"ab"`/`"ab"`: allowed. ✅

## ⚠️ Pitfalls
- **Only one map** misses many-to-one collisions ("badc" vs "baba").
- **Go map zero value:** `m[c]` returns 0 for a missing key, which is a valid byte; use the comma-ok form (or store index+1 in an array).
- **C++ `map[c]` inserts** a default when reading; use `count`/`find`, or arrays of size 256.

## 🎯 What the Interviewer Wants
- Recognize it's a bijection, not just a function.
- Produce the counterexample for the one-map solution yourself.
- Note O(1) space because the alphabet is bounded.

## Follow-ups
- **Words instead of characters:** [LC 0290 Word Pattern](../0290-word-pattern/)
- **Filter a list of words matching a pattern:** LC 0890 Find and Replace Pattern (not added yet)
- **Group strings that are isomorphic to each other:** use the first-occurrence signature as a hashmap key.
