---
number: 380
title: Insert Delete GetRandom O(1)
difficulty: Medium
topic: Arrays & Hashing
pattern: Hashmap + array, swap-delete
link: https://leetcode.com/problems/insert-delete-getrandom-o1/
lists: [LC Top Interview 150]
followup_of: []
related: ["0381 Insert Delete GetRandom O(1) - Duplicates allowed", "0146 LRU Cache"]
---

# 0380. Insert Delete GetRandom O(1)

## ⚡ 30-Second Summary
**Pattern:** Hashmap (value → index) + dynamic array, delete by swapping with the last element
**Key insight:** An array gives O(1) uniform random access but O(n) deletion from the middle; a hashmap gives O(1) lookup but no random access. Combine them, and delete by moving the last element into the hole, so the array never has gaps.
**Go-to:** Map + array with swap-delete, O(1) average for every operation, O(n) space

## Problem
Design a set of integers supporting `insert(val)` (returns true if it was absent), `remove(val)` (returns true if it was present), and `getRandom()` (returns a uniformly random current element; at least one exists when called). Each operation must be O(1) on average. [LeetCode](https://leetcode.com/problems/insert-delete-getrandom-o1/)

**Examples:**
```
Input:  ["RandomizedSet","insert","remove","insert","getRandom","remove","insert","getRandom"]
        [[],[1],[2],[2],[],[1],[2],[]]
Output: [null,true,false,true,2,true,false,2]
Why:    insert 1 → true; remove 2 (absent) → false; insert 2 → true;
        getRandom returns 1 or 2 with equal chance (2 shown); remove 1 → true;
        insert 2 (already there) → false; getRandom must return 2, the only element.
```

**Constraints:**
- -2³¹ ≤ val ≤ 2³¹ - 1; up to 2·10⁵ total calls.
- getRandom is only called when the set is non-empty.

## Hints
<details><summary>Hint 1</summary>
Which structure gives O(1) random pick? Which gives O(1) membership?
</details>
<details><summary>Hint 2</summary>
Removing from the middle of an array is O(n). Does the order of elements matter for this set?
</details>
<details><summary>Hint 3</summary>
Store val → index in a map. To remove, copy the last element into the removed slot, update its index in the map, then pop the last slot.
</details>

## Clarifying Questions
- Duplicates allowed? (No here; see 0381 for the multiset version.)
- Must getRandom be exactly uniform? (Yes.)
- Average or worst-case O(1)? (Average, because of hashing.)

## Example Walkthrough
Insert 10, 20, 30: `arr = [10,20,30]`, `pos = {10:0, 20:1, 30:2}`.
- remove(10): last = 30. Put 30 at index 0: `arr = [30,20,30]`, `pos[30] = 0`. Pop: `arr = [30,20]`, delete `pos[10]`.
- getRandom: pick `arr[rand() % 2]`.

## Approaches

### 1. Hash Set Only: insert/remove O(1), getRandom O(n)
A set handles membership, but picking a random element means copying or walking it each time. Fails the requirement.

### 2. Map + Array, Swap-Delete ⭐ Go-to: O(1) average for all ops, O(n) space
`insert`: append and record index. `remove`: swap with last, fix the moved element's index, pop. `getRandom`: random index into the array.
**Why it's the go-to:** it's the standard (and only simple) way to meet all three O(1) requirements.

## Dry Run (Approach 2)
Ops: insert 1, remove 2, insert 2, getRandom, remove 1, insert 2, getRandom

| op | arr | pos | returns |
|----|-----|-----|---------|
| insert 1 | [1] | {1:0} | true |
| remove 2 | [1] | {1:0} | false |
| insert 2 | [1,2] | {1:0, 2:1} | true |
| getRandom | [1,2] | | 1 or 2 |
| remove 1 | [2] | {2:0} | true (2 moved into index 0) |
| insert 2 | [2] | {2:0} | false |
| getRandom | [2] | | 2 |

## Edge Case Check
- Remove the last element itself: swapping with itself is harmless; just make sure you delete the map entry *after* updating the moved index (or handle the self-swap). ✅
- Remove from a one-element set: same as above. ✅
- Insert after removal reuses the array slot at the end. ✅

## ⚠️ Pitfalls
- **Order of map updates on remove:** set `pos[last] = idx` first, then `erase(val)`. Doing it the other way round re-inserts val when val == last.
- **C++ `pos[val]` for the membership check** inserts a default; use `count`/`find`.
- **Go map zero value:** index 0 is a valid position; use comma-ok.
- **Python `random.choice(set)`** doesn't work on sets; that's why the list exists.

## 🎯 What the Interviewer Wants
- Explain why neither structure alone works.
- The swap-with-last trick and correct index bookkeeping.
- Mention that O(1) is average-case due to hashing.

## Follow-ups
- **Duplicates allowed:** map val → set of indices: LC 0381 Insert Delete GetRandom O(1) - Duplicates allowed (not added yet)
- **Weighted random pick:** prefix sums + binary search (LC 0528 Random Pick with Weight, not added yet).
- **Another map + linked-structure design:** [LC 0146 LRU Cache](../../06-linked-list/0146-lru-cache/)
