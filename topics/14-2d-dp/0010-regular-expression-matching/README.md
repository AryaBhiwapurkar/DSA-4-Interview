---
number: 10
title: Regular Expression Matching
difficulty: Hard
topic: 2-D Dynamic Programming
pattern: Two-string DP with star
link: https://leetcode.com/problems/regular-expression-matching/
lists: [NeetCode 150]
followup_of: []
related: ["0044 Wildcard Matching", "0072 Edit Distance"]
---

# 0010. Regular Expression Matching

## ⚡ 30-Second Summary
**Pattern:** Two-string DP on suffixes, with a special case for `x*`
**Key insight:** `go(i, j)` = does `s[i:]` match `p[j:]`. If `p[j+1]` is `*`, either skip the pair (`go(i, j+2)`) or, if `s[i]` matches `p[j]`, consume one character and keep the star (`go(i+1, j)`). Otherwise the current characters must match and both advance.
**Go-to:** Top-down memo on (i, j), O(m·n) time, O(m·n) space

## Problem
Implement full-string matching for a pattern where `.` matches any single character and `*` means "zero or more of the character just before it". [LeetCode](https://leetcode.com/problems/regular-expression-matching/)

**Examples:**
```
Input:  s = "aa", p = "a"
Output: false
Why:    The pattern covers one character; the match must cover the whole string.

Input:  s = "aa", p = "a*"
Output: true
Why:    a* expands to two a's.

Input:  s = "ab", p = ".*"
Output: true
Why:    .* is any string, including "ab".
```

**Constraints:**
- 1 ≤ |s| ≤ 20, 1 ≤ |p| ≤ 20: small, but the plain recursion still blows up on patterns like `a*a*a*...`.
- Every `*` has a valid character before it.

## Hints
<details><summary>Hint 1</summary>
Process the pattern one token at a time, where a token is a char or a char followed by '*'. What can a "x*" token do?
</details>
<details><summary>Hint 2</summary>
"x*" either matches nothing (skip two pattern chars), or matches one char of s and stays available for more. A plain char must match exactly one char.
</details>
<details><summary>Hint 3</summary>
go(i, j): if j == |p| return i == |s|. first = i < |s| and p[j] in {s[i], '.'}. If p[j+1] == '*': return go(i, j+2) or (first and go(i+1, j)). Else return first and go(i+1, j+1). Memoize on (i, j).
</details>

## Clarifying Questions
- Must the whole string match? (Yes, not a substring.)
- Can `*` appear first or twice in a row? (No, guaranteed valid.)
- Does `.` match an empty position? (No, exactly one character.)

## Example Walkthrough
`s = "aab"`, `p = "c*a*b"`. c* can't match 'a', so it matches zero c's. a* eats both a's. Then 'b' matches 'b' and both strings end together → true.

## Approaches

### 1. Plain Recursion: exponential time, O(m+n) space
The same case analysis without caching. Patterns like `a*a*a*a*c` against "aaaa…" revisit the same (i, j) many times.

### 2. Top-down Memo ⭐ Go-to: O(m·n) time, O(m·n) space
**Why it's the go-to:** it's the recursion you'd explain anyway, plus a cache. The star logic stays readable, which is the part interviewers grill.

### 3. Bottom-up Table: O(m·n) time, O(m·n) space
Fill dp[i][j] for suffixes from (m, n) backwards with the same transitions. Note that row i = m must be computed: an empty s can still match `x*` pairs.

## Dry Run (Approach 2)
`s = "aab"`, `p = "c*a*b"` (indices: c0 *1 a2 *3 b4).

| call | case | result |
|------|------|--------|
| go(0,0) | c* and 'a' ≠ 'c' → skip pair | go(0,2) |
| go(0,2) | a*: skip → go(0,4) is false ('b' ≠ 'a'); eat 'a' | go(1,2) |
| go(1,2) | a*: skip → go(1,4) is false; eat 'a' | go(2,2) |
| go(2,2) | a*, 'b' ≠ 'a' → skip pair | go(2,4) |
| go(2,4) | 'b' == 'b' → advance both | go(3,5) |
| go(3,5) | pattern done, string done | **true** |

## Edge Case Check
- `s = ""`, `p = "a*b*"` → both stars match zero → true. ✅
- `"mississippi"`, `"mis*is*p*."` → false. "mis*is*" covers "mississ", leaving "ippi" for "p*.": p* can't take the i, and "." takes only one char. ✅
- `"aa"`, `"a"` → pattern ends early → false. ✅

## ⚠️ Pitfalls
- **Handling `*` when you reach it** instead of looking ahead at p[j+1]: by then the char before it has been consumed.
- **Checking `first` before `i < |s|`** reads past the end of s.
- **Forgetting the empty-s row** in the bottom-up table: `""` vs `"a*"` must be true.
- **Treating `*` as "one or more"**: it allows zero.

## 🎯 What the Interviewer Wants
- A clean case split: star vs no star, look-ahead at p[j+1].
- Recognise overlapping subproblems and memoize.
- State the O(m·n) complexity and handle empty-string cases.

## Follow-ups
- **`?` and `*` where `*` matches any sequence by itself:** LC 0044 Wildcard Matching (not added yet). Similar DP, simpler star.
- **Two-string DP warm-up:** [LC 0072 Edit Distance](../0072-edit-distance/)
- **Add `+` (one or more):** rewrite `x+` as `xx*`.
