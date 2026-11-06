---
number: 981
title: Time Based Key-Value Store
difficulty: Medium
topic: Binary Search
pattern: Hashmap + binary search on time
link: https://leetcode.com/problems/time-based-key-value-store/
lists: [NeetCode 150]
followup_of: []
related: ["0035 Search Insert Position", "0146 LRU Cache", "2034 Stock Price Fluctuation"]
---

# 0981. Time Based Key-Value Store

## ⚡ 30-Second Summary
**Pattern:** Hashmap of sorted (timestamp, value) lists + binary search
**Key insight:** Timestamps for `set` arrive strictly increasing, so appending keeps each key's list sorted for free. `get(key, t)` is "the last entry with timestamp ≤ t" = upper bound(t) - 1.
**Go-to:** Hashmap → list + upper-bound search, O(1) set, O(log n) get, O(n) space

## Problem
Design a store with `set(key, value, timestamp)` and `get(key, timestamp)`. `get` returns the value set for that key at the largest timestamp ≤ the given one, or "" if there is none. [LeetCode](https://leetcode.com/problems/time-based-key-value-store/)

**Examples:**
```
Input:  ["TimeMap","set","get","get","set","get","get"]
        [[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
Output: [null,null,"bar","bar",null,"bar2","bar2"]
Why:    get at 3 falls back to the value from time 1. After "bar2" is set at 4,
        gets at 4 and 5 see it.
```

**Constraints:**
- Timestamps of `set` calls are strictly increasing (the key fact).
- Up to 2·10⁵ calls; 1 ≤ timestamp ≤ 10⁷.

## Hints
<details><summary>Hint 1</summary>
Store every version per key. In what order do the versions arrive?
</details>
<details><summary>Hint 2</summary>
Strictly increasing timestamps mean each key's list is already sorted. What search finds "latest ≤ t"?
</details>
<details><summary>Hint 3</summary>
Binary search for the first timestamp > t; the answer is the entry just before it (if any).
</details>

## Clarifying Questions
- Are set timestamps increasing? (Yes, strictly, across all calls.)
- What does get return for an unknown key or a too-early time? ("".)
- Can the same key be set twice at the same time? (No, timestamps are strictly increasing.)

## Example Walkthrough
After set(foo, bar, 1) and set(foo, bar2, 4): foo → [(1, bar), (4, bar2)].
- get(foo, 3): first timestamp > 3 is index 1, so take index 0: "bar".
- get(foo, 5): first > 5 is index 2 (end), take index 1: "bar2".
- get(foo, 0): first > 0 is index 0, nothing before it: "".

## Approaches

### 1. Hashmap + Linear Scan: O(1) set, O(n) get, O(n) space
Scan the key's list backwards for the first timestamp ≤ t.

### 2. Hashmap + Binary Search ⭐ Go-to: O(1) set, O(log n) get, O(n) space
Upper bound on timestamps, then step back one. (C++ alternative: `map<int, string>` per key with `upper_bound`, O(log n) set as well.)
**Why it's the go-to:** uses the sorted-for-free insight; the search is the standard upper-bound template.

## Dry Run (Approach 2)
foo → [(1, bar), (4, bar2)], `get(foo, 4)`

| lo | hi | mid | ts[mid] | ts[mid] ≤ 4? | action |
|----|----|-----|---------|--------------|--------|
| 0 | 2 | 1 | 4 | yes | lo = 2 |
| 2 | 2 | | | | upper bound = 2 → entry 1 → **"bar2"** |

## Edge Case Check
- Unknown key: "". ✅
- Timestamp before the first set: upper bound 0, nothing before: "". ✅
- Exact timestamp match: `≤` includes it. ✅

## ⚠️ Pitfalls
- **Lower bound instead of upper bound**: on an exact match, lower bound - 1 gives the previous version.
- **C++ `m[key]` in get** inserts an empty list for unknown keys; use `find`.
- **Go map zero value**: `m[key]` on a missing key gives a nil slice, which is fine to search (length 0) but don't write through it.
- **Assuming per-key sortedness without the guarantee**: if timestamps weren't increasing, you'd need a sorted map or insertion sort.

## 🎯 What the Interviewer Wants
- Notice that sorted order comes free from the constraint.
- Correct "last ≤ t" search (upper bound - 1).
- Discuss the alternative with a balanced BST (`std::map`, `TreeMap`) when inserts aren't ordered.

## Follow-ups
- **Out-of-order timestamps:** a per-key sorted map (`std::map::upper_bound`, Java `TreeMap.floorKey`).
- **Delete or update old versions:** sorted containers again.
- **Similar "latest ≤ t" lookups:** stock prices with corrections: LC 2034 Stock Price Fluctuation (not added yet)
- **Lower-bound template:** [LC 0035 Search Insert Position](../0035-search-insert-position/)
