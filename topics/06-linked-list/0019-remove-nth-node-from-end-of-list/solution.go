/*
 * 0019. Remove Nth Node From End of List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 *
 * Problem: Remove the n-th node from the end and return the head.
 *          n is always valid.
 *
 * Examples:
 *   [1,2,3,4,5], n 2  -> [1 2 3 5]
 *   [1],         n 1  -> []
 *   [1,2],       n 1  -> [1]
 *   [1,2],       n 2  -> [2]
 *
 * Approaches:
 *   1. Two passes (count length)   O(L) time, O(1) space
 *   2. One pass with n-gap  ⭐      O(L) time, O(1) space   <- go-to
 */

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

// ---------- Approach 1: Two Passes ----------
func removeNthFromEndTwoPass(head *ListNode, n int) *ListNode {
	length := 0
	for p := head; p != nil; p = p.Next {
		length++
	}
	dummy := &ListNode{Next: head}
	prev := dummy
	for i := 0; i < length-n; i++ { // predecessor of the target
		prev = prev.Next
	}
	prev.Next = prev.Next.Next
	return dummy.Next
}

// ---------- Approach 2: One Pass With n-Gap ⭐ ----------
func removeNthFromEnd(head *ListNode, n int) *ListNode {
	dummy := &ListNode{Next: head} // makes removing the head a normal case
	slow, fast := dummy, dummy
	for i := 0; i < n; i++ { // fast leads by n
		fast = fast.Next
	}
	for fast.Next != nil { // stop with fast on the LAST node
		slow, fast = slow.Next, fast.Next
	}
	slow.Next = slow.Next.Next // slow is the predecessor
	return dummy.Next
}

// ---------- Driver ----------
func build(vals []int) *ListNode {
	dummy := &ListNode{}
	tail := dummy
	for _, v := range vals {
		tail.Next = &ListNode{Val: v}
		tail = tail.Next
	}
	return dummy.Next
}

func toSlice(head *ListNode) []int {
	out := []int{}
	for ; head != nil; head = head.Next {
		out = append(out, head.Val)
	}
	return out
}

func main() {
	tests := []struct {
		vals []int
		n    int
	}{
		{[]int{1, 2, 3, 4, 5}, 2}, {[]int{1}, 1}, {[]int{1, 2}, 1}, {[]int{1, 2}, 2},
	}
	for _, t := range tests { // fresh list per approach: removal mutates
		fmt.Println("twoPass:", toSlice(removeNthFromEndTwoPass(build(t.vals), t.n)))
		fmt.Println("onePass:", toSlice(removeNthFromEnd(build(t.vals), t.n)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - &ListNode{Next: head} sets one field by name; Val defaults to 0.
 * - Unlinked nodes are garbage collected; no manual free.
 * - `slow, fast = slow.Next, fast.Next` advances both together.
 */
