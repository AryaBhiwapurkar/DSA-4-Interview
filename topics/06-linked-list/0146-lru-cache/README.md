---
number: 146
title: LRU Cache
difficulty: Medium
topic: Linked List
pattern: Hashmap + doubly linked list
link: https://leetcode.com/problems/lru-cache/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0460 LFU Cache", "0380 Insert Delete GetRandom O(1)", "0155 Min Stack"]
---

# 0146. LRU Cache

## ⚡ 30-Second Summary
**Pattern:** Hashmap + doubly linked list
**Key insight:** You need O(1) lookup by key (hashmap) and O(1) "move to most recent" / "evict least recent" (a doubly linked list ordered by recency). The map stores key → list node, so you can unlink any node in O(1). Sentinel head/tail nodes remove all edge cases.
**Go-to:** Hashmap of key → node + DLL with sentinels, O(1) per operation, O(capacity) space

## Problem
Design a cache with a fixed capacity. `get(key)` returns the value or -1. `put(key, value)` inserts or updates; if that pushes the size over capacity, evict the least recently used key. Both operations count as a "use" and must run in O(1) on average.

**Examples:**
```
Input:  ["LRUCache","put","put","get","put","get","put","get","get","get"]
        [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
Output: [null,null,null,1,null,-1,null,-1,3,4]
Why:    get(1) makes 1 recent, so put(3) evicts 2. Then put(4) evicts 1
        (3 was used more recently), leaving 3 and 4.
```

**Constraints:**
- 1 ≤ capacity ≤ 3000; up to 2·10⁵ calls.
- O(1) average time for both `get` and `put`.

## Hints
<details><summary>Hint 1</summary>
Which structure gives O(1) lookup? Which gives O(1) removal from the middle and insertion at an end?
</details>
<details><summary>Hint 2</summary>
A doubly linked list can unlink a node in O(1), but only if you already have a pointer to it. Where would that pointer come from?
</details>
<details><summary>Hint 3</summary>
Map key → node. On every access, unlink the node and insert it right after a head sentinel. Evict the node just before the tail sentinel, and erase its key from the map (store the key in the node for this).
</details>

## Clarifying Questions
- Does `put` on an existing key count as a use? (Yes, and it updates the value.)
- Does `get` on a missing key change anything? (No.)
- Capacity ≥ 1? (Yes.)
- Thread safety? (Not required.)

## Example Walkthrough
capacity 2 (order shown most → least recent)
- put(1,1): [1]. put(2,2): [2,1]. get(1) → 1: [1,2].
- put(3,3): full, evict LRU 2: [3,1]. get(2) → -1.
- put(4,4): evict 1: [4,3]. get(1) → -1, get(3) → 3: [3,4], get(4) → 4.

## Approaches

### 1. Ordered List With Linear Search: O(capacity) per op, O(capacity) space
Keep (key, value) pairs in recency order; find, move and evict by scanning. Correct, but not O(1).

### 2. Hashmap + Doubly Linked List ⭐ Go-to: O(1) per op, O(capacity) space
Map for lookup, DLL for order, sentinels for clean pointer code. (Library shortcuts: Python `OrderedDict.move_to_end` / `popitem(last=False)`, C++ `std::list` + `splice`, Go `container/list`. Interviewers usually want the hand-written version.)
**Why it's the go-to:** it's the canonical answer, and writing the DLL yourself shows pointer fluency.

## Dry Run (Approach 2)
capacity 2; list shown head ⇄ … ⇄ tail (MRU first)

| op | action | list after | map keys | output |
|----|--------|------------|----------|--------|
| put(1,1) | new node, push front | 1 | {1} | null |
| put(2,2) | new node, push front | 2, 1 | {1,2} | null |
| get(1) | found: unlink, push front | 1, 2 | {1,2} | 1 |
| put(3,3) | full: evict tail.prev (2) | 3, 1 | {1,3} | null |
| get(2) | not in map | 3, 1 | {1,3} | -1 |
| put(4,4) | full: evict 1 | 4, 3 | {3,4} | null |

## Edge Case Check
- Capacity 1: every new key evicts the previous one. ✅
- put on an existing key: update value + move to front, no eviction. ✅
- get on a missing key: -1, order unchanged. ✅

## ⚠️ Pitfalls
- **Evicting before checking for an existing key**: updating a key in a full cache must not evict anything.
- **Not storing the key in the node**: you can't erase the evicted entry from the map.
- **Forgetting to erase from the map on eviction**: size check and lookups break.
- **No sentinels**: head/tail null checks everywhere; two dummy nodes remove them.
- **C++ `m[key]` in get** inserts a null entry for missing keys; use `find`.

## 🎯 What the Interviewer Wants
- Justify both structures: map for O(1) lookup, DLL for O(1) reorder/evict.
- Clean helper functions (`unlink`, `pushFront`) and sentinels.
- Correct ordering of steps in `put` (update vs insert vs evict).

## Follow-ups
- **Evict least frequently used (ties by recency):** map of freq → DLL: LC 0460 LFU Cache (not added yet)
- **O(1) insert/delete/random:** another "map + array/list" design: [LC 0380 Insert Delete GetRandom O(1)](../../01-arrays-hashing/0380-insert-delete-getrandom-o1/)
- **TTL / expiry:** add timestamps, evict expired entries lazily on access.
- **Concurrent cache:** a mutex around both structures, or sharded caches.
