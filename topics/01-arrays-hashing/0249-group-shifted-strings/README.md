---
number: 249
title: Group Shifted Strings
difficulty: Medium
topic: Arrays & Hashing
pattern: Canonical key (letter gaps mod 26)
link: https://leetcode.com/problems/group-shifted-strings/
lists: [Interview Extras]
followup_of: ["0049 Group Anagrams"]
related: ["0049 Group Anagrams", "0890 Find and Replace Pattern", "0205 Isomorphic Strings"]
---

# 0249. Group Shifted Strings

## ⚡ 30-Second Summary
**Pattern:** Group by a canonical key, like Group Anagrams
**Key insight:** Shifting every letter by the same amount keeps the **gaps** between neighbouring letters unchanged (mod 26). So the key is the tuple of `(s[i] − s[i−1]) mod 26`. Equivalently, shift the string so its first letter becomes 'a'. Strings with equal keys (and so equal length) go in one group.
**Go-to:** Hashmap from normalised key to list, O(total characters) time and space

## Problem
Shifting a string moves every letter one step forward in the alphabet, with z wrapping to a ("abc" → "bcd", "az" → "ba"). Group the given strings so that each group contains strings reachable from one another by repeated shifting. LeetCode Premium. [LeetCode](https://leetcode.com/problems/group-shifted-strings/)

**Examples:**
```
Input:  strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
Why:    abc/bcd/xyz all step +1,+1; az and ba both step -1 (= +25); single letters all match.

Input:  strings = ["a"]
Output: [["a"]]
Why:    One string, one group.
```

**Constraints:**
- 1 ≤ count ≤ 200; 1 ≤ length ≤ 50; lowercase letters.
- Group order and order within groups don't matter.

## Hints
<details><summary>Hint 1</summary>
Group Anagrams used a key that's the same for every member of a group. What stays the same when you shift a string?
</details>
<details><summary>Hint 2</summary>
Look at neighbouring letters. How does "abc" compare to "xyz"? What about wrap-around ("az" vs "ba")?
</details>
<details><summary>Hint 3</summary>
Key = tuple((ord(s[i]) − ord(s[i−1])) % 26 for i ≥ 1). groups[key].append(s). Return the groups' values.
</details>

## Clarifying Questions
- Does wrap-around count (z → a)? (Yes.)
- Are duplicate strings kept? (Yes, both copies go in the same group.)
- Output order? (Any.)

## Example Walkthrough
"az": gap (z − a) mod 26 = 25. "ba": gap (a − b) mod 26 = −1 mod 26 = 25. Same key (25,), so same group. "a" and "z" have no gaps, so both get the empty key ().

## Approaches

### 1. Pairwise Compare: O(n² · L) time
Two strings belong together iff they have the same length and the same shift for every position. Compare each string with one representative of every existing group. Works, but quadratic in the number of strings.

### 2. Canonical Key ⭐ Go-to: O(N) time, O(N) space (N = total characters)
**Why it's the go-to:** same shape as Group Anagrams; you only change the key function.

## Dry Run (Approach 2)

| string | key | groups after |
|--------|-----|--------------|
| abc | (1,1) | {(1,1):[abc]} |
| bcd | (1,1) | {(1,1):[abc,bcd]} |
| acef | (2,2,1) | + {(2,2,1):[acef]} |
| xyz | (1,1) | (1,1):[abc,bcd,xyz] |
| az | (25,) | + {(25,):[az]} |
| ba | (25,) | (25,):[az,ba] |
| a, z | () | + {():[a,z]} |

**4 groups.**

## Edge Case Check
- Single-letter strings → all share the empty key. ✅
- Different lengths with "matching" gaps can't collide: the key length is L − 1. ✅
- Wrap-around → `% 26` normalises negatives (add 26 in C++). ✅

## ⚠️ Pitfalls
- **Negative gaps in C++:** `(b − a) % 26` can be negative. Use `(b − a + 26) % 26`.
- **String keys without separators** (e.g. "1" + "11" vs "11" + "1") can collide. Use a tuple, or append a delimiter or fixed-width char per gap.
- **Forgetting that length matters:** a key built from gaps already encodes it; a key built by "shift to start at 'a'" does too.

## 🎯 What the Interviewer Wants
- Recognise "group by an invariant" and pick a correct key.
- Handle wrap-around properly.
- Linear time in the total input size.

## Follow-ups
- **Same grouping, anagram key:** [LC 0049 Group Anagrams](../0049-group-anagrams/)
- **Pattern bijection instead of shift:** [LC 0890 Find and Replace Pattern](../0890-find-and-replace-pattern/)
