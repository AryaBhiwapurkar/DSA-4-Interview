---
number: 49
title: Group Anagrams
difficulty: Medium
topic: Arrays & Hashing
pattern: Hashmap with canonical key
link: https://leetcode.com/problems/group-anagrams/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0242 Valid Anagram"]
related: ["0242 Valid Anagram", "0249 Group Shifted Strings"]
---

# 0049. Group Anagrams

## ⚡ 30-Second Summary
**Pattern:** Hashmap keyed by a canonical form
**Key insight:** All anagrams share the same sorted string (or the same 26 letter counts). Use that as a hashmap key and bucket words under it.
**Go-to:** Sorted-string key, O(n·k log k) time, O(n·k) space

## Problem
Given an array of strings, group the strings that are anagrams of each other. Groups and the words inside them may be returned in any order.

**Examples:**
```
Input:  strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Why:    eat/tea/ate share letters a,e,t; tan/nat share a,n,t; bat is alone.

Input:  strs = [""]
Output: [[""]]
Why:    The empty string forms its own group.

Input:  strs = ["a"]
Output: [["a"]]
Why:    A single word is a group of one.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; 0 ≤ each length k ≤ 100.
- Lowercase letters only, so a 26-count key is possible.

## Hints
<details><summary>Hint 1</summary>
How do you check if two words are anagrams? Doing that for every pair is O(n²).
</details>
<details><summary>Hint 2</summary>
Find something that is identical for all anagrams and different otherwise.
</details>
<details><summary>Hint 3</summary>
Sort each word's letters: anagrams produce the same string. Use it as a hashmap key mapping to a list of words.
</details>

## Clarifying Questions
- Does output order matter? (No.)
- Can strings be empty? (Yes, they group together.)
- Only lowercase? (Yes; otherwise the count key needs a bigger alphabet.)

## Example Walkthrough
`["eat","tea","tan","ate","nat","bat"]`
- eat → "aet", tea → "aet", tan → "ant", ate → "aet", nat → "ant", bat → "abt".
- Buckets: aet: [eat, tea, ate], ant: [tan, nat], abt: [bat].

## Approaches

### 1. Pairwise Compare (Brute Force): O(n²·k) time, O(n) space
For each ungrouped word, scan the rest and pull in every anagram (checked by counting). Too slow at n = 10⁴.

### 2. Sorted-String Key ⭐ Go-to: O(n·k log k) time, O(n·k) space
Key = word with its letters sorted; append the word to `groups[key]`.
**Why it's the go-to:** two lines of logic, obviously correct, and with k ≤ 100 the log k factor is negligible.

### 3. Letter-Count Key: O(n·k) time, O(n·k) space
Key = the 26 counts (e.g. "1#0#0#...") or a tuple of counts. Strictly linear in total characters; mention it as the optimization.

## Dry Run (Approach 2)
`["eat","tea","tan","ate","nat","bat"]`

| word | key | groups after |
|------|-----|--------------|
| eat | aet | {aet:[eat]} |
| tea | aet | {aet:[eat,tea]} |
| tan | ant | {aet:[eat,tea], ant:[tan]} |
| ate | aet | {aet:[eat,tea,ate], ant:[tan]} |
| nat | ant | {aet:[...], ant:[tan,nat]} |
| bat | abt | {aet:[...], ant:[...], abt:[bat]} |

## Edge Case Check
- `[""]`: key "" maps to [""]. ✅
- All words identical: one group. ✅
- No two anagrams: n groups of one. ✅

## ⚠️ Pitfalls
- **Count key without separators:** counts [1,11] and [11,1] both become "111"; use a delimiter or a tuple/array key.
- **Python lists aren't hashable:** use `tuple(count)` or `"".join(sorted(s))`.
- **Go:** a `[26]int` array IS comparable and works directly as a map key; a slice does not.
- **C++:** `unordered_map` has no hash for `array<int,26>`; use a string key.

## 🎯 What the Interviewer Wants
- Jump from "check pairs" to "canonical key in a hashmap".
- Compare the two key choices and their complexity.
- Correct hashable key in your language.

## Follow-ups
- **Just check two strings:** [LC 0242 Valid Anagram](../0242-valid-anagram/)
- **Group strings that are shifts of each other ("abc", "bcd"):** key = differences between adjacent letters mod 26: LC 0249 Group Shifted Strings (not added yet)
- **Unicode / very long strings:** count key with a hashmap of counts, or sort runes.
