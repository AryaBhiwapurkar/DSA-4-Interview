# 06. Linked List

## Core Idea
A linked list gives O(1) insert/delete once you hold the right node, but no random access. Almost every problem is a mix of a few moves: **walk with two pointers** (fast/slow for the middle or cycles, a fixed gap for "n-th from the end"), **rewire `next` pointers** (reverse, splice, cut, reconnect), and **build a new chain behind a dummy node** (merge, partition, filter). Draw the boxes and arrows, save any `next` you're about to overwrite, and use a dummy whenever the head might change.

## When to Use
- "Reverse" all or part of a list, in place (0206, 0092, 0025).
- "Middle", "cycle", "n-th from the end" without knowing the length (0141, 0019, 0143).
- Merge or sort sorted sequences without extra arrays (0021, 0023, 0148).
- Reorder / partition / remove nodes while keeping order (0143, 0086, 0082).
- O(1) "move to front" and "evict oldest" with a hashmap → node index (0146).
- Arrays whose values are valid indices: treat i → nums[i] as a linked list (0287).
- Deep copies of pointer structures: map old node → new node (0138).

## Templates

### Dummy node + tail (build a result chain)
```cpp
ListNode dummy;
ListNode* tail = &dummy;
for (/* each node p to keep */) tail = tail->next = p;
tail->next = nullptr;                    // cut whatever followed
return dummy.next;
```
```python
dummy = tail = ListNode()
for p in nodes_to_keep:
    tail.next = p
    tail = p
tail.next = None
return dummy.next
```
```go
dummy := &ListNode{}
tail := dummy
for _, p := range nodesToKeep {
	tail.Next = p
	tail = p
}
tail.Next = nil
return dummy.Next
```

### Reverse (prev / curr / next)
```cpp
ListNode *prev = nullptr, *curr = head;
while (curr) {
    ListNode* nxt = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nxt;
}
return prev;
```
```python
prev, curr = None, head
while curr:
    curr.next, prev, curr = prev, curr, curr.next
return prev
```
```go
var prev *ListNode
for curr := head; curr != nil; {
	curr.Next, prev, curr = prev, curr, curr.Next
}
return prev
```

### Fast / slow (middle, cycle)
```cpp
ListNode *slow = head, *fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) { /* cycle */ }
}
// no cycle: slow is the middle (second middle for even length)
```
```python
slow = fast = head
while fast and fast.next:
    slow, fast = slow.next, fast.next.next
    if slow is fast:
        ...  # cycle
```
```go
slow, fast := head, head
for fast != nil && fast.Next != nil {
	slow, fast = slow.Next, fast.Next.Next
	if slow == fast {
		// cycle
	}
}
```

## Common Variations
- **Gap of n:** move fast n steps first, then both, to land on the node before the n-th from the end (0019).
- **First vs second middle:** start `fast = head.next` to get the first middle (split for merge sort, 0148); `fast = head` gives the second.
- **Floyd phase 2:** after meeting, restart one pointer at the head; stepping both by 1 meets at the cycle entry (0287).
- **Head insertion:** reverse a sub-range by moving `curr.next` to just after `prev`, `right - left` times (0092).
- **Group reversal:** check k nodes exist, reverse with `prev = groupNext`, reconnect, advance (0025).
- **Two chains, then join:** stable partition (0086), odd/even, split and weave (0143).
- **Ring trick:** connect tail → head, then cut at the new tail (0061).
- **Hashmap + DLL with sentinels:** O(1) reorder and eviction (0146).
- **Old → new map / interleaving** for deep copies (0138).

## ⚠️ Pitfalls
- **Overwriting `next` before saving it:** the rest of the list is lost.
- **Head changes without a dummy:** removing or reordering the first node needs special cases otherwise.
- **Forgetting to terminate a chain:** a stale `next` creates a cycle (partition, reorder, rotate).
- **Null checks in the right order:** `fast && fast->next` before `fast->next->next`; `curr && curr.val == v`.
- **Comparing values instead of nodes** for cycles, intersections, and copies.
- **Mutating inputs in test drivers:** build a fresh list for each approach.
- **Language notes:** C++ leaks if you don't `delete` removed nodes (fine on LeetCode); Python `a = b = ListNode()` aliases one node; Go `nil` pointer dereference panics.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0021 | [Merge Two Sorted Lists](0021-merge-two-sorted-lists/) | Easy | Dummy head merge | ✅ |
| 0141 | [Linked List Cycle](0141-linked-list-cycle/) | Easy | Floyd fast/slow | ✅ |
| 0206 | [Reverse Linked List](0206-reverse-linked-list/) | Easy | Iterative reversal | ✅ |
| 0002 | [Add Two Numbers](0002-add-two-numbers/) | Medium | Digit-wise add with carry | ✅ |
| 0019 | [Remove Nth Node From End of List](0019-remove-nth-node-from-end-of-list/) | Medium | Fast/slow with n gap | ✅ |
| 0061 | [Rotate List](0061-rotate-list/) | Medium | Close ring, cut at n-k | ✅ |
| 0082 | [Remove Duplicates from Sorted List II](0082-remove-duplicates-from-sorted-list-ii/) | Medium | Dummy + skip duplicate runs | ✅ |
| 0086 | [Partition List](0086-partition-list/) | Medium | Two dummy lists | ✅ |
| 0092 | [Reverse Linked List II](0092-reverse-linked-list-ii/) | Medium | Sublist reversal | ✅ |
| 0138 | [Copy List with Random Pointer](0138-copy-list-with-random-pointer/) | Medium | Hashmap old→new / interleave | ✅ |
| 0143 | [Reorder List](0143-reorder-list/) | Medium | Find mid + reverse + merge | ✅ |
| 0146 | [LRU Cache](0146-lru-cache/) | Medium | Hashmap + doubly linked list | ✅ |
| 0148 | [Sort List](0148-sort-list/) | Medium | Merge sort on list | ✅ |
| 0287 | [Find the Duplicate Number](0287-find-the-duplicate-number/) | Medium | Floyd cycle on indices | ✅ |
| 0023 | [Merge k Sorted Lists](0023-merge-k-sorted-lists/) | Hard | Min-heap / divide & conquer | ✅ |
| 0025 | [Reverse Nodes in k-Group](0025-reverse-nodes-in-k-group/) | Hard | Group reversal with dummy | ✅ |
