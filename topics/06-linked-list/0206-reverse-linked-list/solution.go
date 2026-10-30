/*
 * 0206. Reverse Linked List  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/reverse-linked-list/
 *
 * Problem: Reverse a singly linked list and return the new head.
 *
 * Examples:
 *   [1,2,3,4,5]  -> [5 4 3 2 1]
 *   [1,2]        -> [2 1]
 *   []           -> []
 *   [1]          -> [1]
 *
 * Approaches:
 *   1. Copy values, rebuild     O(n) time, O(n) space
 *   2. Iterative  ⭐             O(n) time, O(1) space   <- go-to
 *   3. Recursive                O(n) time, O(n) stack
 */

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

// ---------- Approach 1: Copy Values, Rebuild ----------
func reverseListCopy(head *ListNode) *ListNode {
	var res *ListNode
	for p := head; p != nil; p = p.Next {
		res = &ListNode{p.Val, res} // prepend each value
	}
	return res
}

// ---------- Approach 2: Iterative ⭐ ----------
func reverseList(head *ListNode) *ListNode {
	var prev *ListNode
	curr := head
	for curr != nil {
		curr.Next, prev, curr = prev, curr, curr.Next // RHS evaluated first: safe
	}
	return prev // old tail
}

// ---------- Approach 3: Recursive ----------
func reverseListRecursive(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	newHead := reverseListRecursive(head.Next)
	head.Next.Next = head // the node after me now points back to me
	head.Next = nil       // otherwise a 2-node cycle remains
	return newHead
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
	for _, v := range [][]int{{1, 2, 3, 4, 5}, {1, 2}, {}, {1}} { // fresh list per approach: reversal mutates
		fmt.Println("copy     :", toSlice(reverseListCopy(build(v))))
		fmt.Println("iterative:", toSlice(reverseList(build(v))))
		fmt.Println("recursive:", toSlice(reverseListRecursive(build(v))))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Parallel assignment evaluates all right-hand values first, so the
 *   three-pointer step fits on one line.
 * - `var prev *ListNode` is a nil pointer; &ListNode{Val: v} allocates.
 * - Positional struct literal &ListNode{p.Val, res} sets fields in order.
 */
