---
number: 61
title: Rotate List
difficulty: Medium
topic: Linked List
pattern: Close ring, cut at n-k
link: https://leetcode.com/problems/rotate-list/
lists: [LC Top Interview 150]
followup_of: []
related: ["0189 Rotate Array", "0019 Remove Nth Node From End of List"]
---

# 0061. Rotate List

## ⚡ 30-Second Summary
**Pattern:** Close the list into a ring, then cut it
**Key insight:** Rotating right by k moves the last k mod n nodes to the front. Find the length n and the tail in one pass, connect tail → head to make a ring, walk n - k - 1 steps from the head to the new tail, and cut after it.
**Go-to:** Length + ring + cut, O(n) time, O(1) space

## Problem
Rotate a linked list to the right by k places (each step moves the last node to the front) and return the new head. k can be much larger than the list length. [LeetCode](https://leetcode.com/problems/rotate-list/)

**Examples:**
```
Input:  head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
Why:    The last two nodes move to the front.

Input:  head = [0,1,2], k = 4
Output: [2,0,1]
Why:    4 rotations of 3 nodes is the same as 4 mod 3 = 1 rotation.
```

**Constraints:**
- 0 ≤ n ≤ 500 (empty list allowed).
- 0 ≤ k ≤ 2·10⁹, so simulating k steps is far too slow: reduce k mod n.

## Hints
<details><summary>Hint 1</summary>
Rotating by n gives back the original list. What does that tell you about large k?
</details>
<details><summary>Hint 2</summary>
After the rotation, which node is the new tail, counting from the original head?
</details>
<details><summary>Hint 3</summary>
Get n and the tail; k %= n; if k == 0 return head. Link tail → head, step n - k - 1 times from head to the new tail, new head = newTail.next, set newTail.next = null.
</details>

## Clarifying Questions
- Right rotation (last to front)? (Yes.)
- Can k exceed n, or be 0? (Yes and yes.)
- Empty list? (Return it as is.)

## Example Walkthrough
`[1,2,3,4,5], k = 2`: n = 5, tail = 5.
- k % 5 = 2. Link 5 → 1 (ring).
- New tail is n - k - 1 = 2 steps from the head: 1 → 2 → 3. New head = 4.
- Cut 3 → null. Result [4,5,1,2,3].

## Approaches

### 1. Rotate One Step at a Time: O(n · (k mod n)) time, O(1) space
Repeatedly detach the tail and push it to the front, k mod n times. Without the mod it's hopeless for k = 2·10⁹.

### 2. Ring and Cut ⭐ Go-to: O(n) time, O(1) space
One pass for length and tail, one partial pass to the cut point.
**Why it's the go-to:** linear, constant space, and the ring makes the reconnection trivial.

## Dry Run (Approach 2)
`[0,1,2], k = 4`

| step | value |
|------|-------|
| n, tail | 3, node 2 |
| k % n | 1 |
| ring | 2 → 0 |
| walk n - k - 1 = 1 step from head | new tail = node 1 |
| new head = newTail.next | node 2 |
| cut newTail.next = null | **[2,0,1]** |

## Edge Case Check
- Empty list or single node: return head. ✅
- k % n == 0: return head unchanged, and don't leave a ring behind. ✅
- k < n and k > n: both reduced by mod. ✅

## ⚠️ Pitfalls
- **Not reducing k mod n**: timeouts, or walking off the list.
- **Dividing by zero**: compute k % n only after checking n > 0.
- **Forgetting to cut the ring**: the result loops forever.
- **Making the ring when k % n == 0** and returning early: leaves a cycle. Check before linking.

## 🎯 What the Interviewer Wants
- k mod n immediately.
- A clean way to find the new tail (n - k - 1 steps from the head).
- No cycles left behind.

## Follow-ups
- **Array version:** [LC 0189 Rotate Array](../../01-arrays-hashing/0189-rotate-array/)
- **Left rotation:** cut after k mod n nodes instead.
- **k-th from the end (the new head):** two pointers with a gap: [LC 0019 Remove Nth Node From End of List](../0019-remove-nth-node-from-end-of-list/)
