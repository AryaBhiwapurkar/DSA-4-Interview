/*
 * 0021. Merge Two Sorted Lists  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/merge-two-sorted-lists/
 *
 * Problem: Splice two sorted linked lists into one sorted list.
 *
 * Examples:
 *   [1,2,4], [1,3,4]  -> [1 1 2 3 4 4]
 *   [],      []       -> []
 *   [],      [0]      -> [0]
 *   [5],     [1,2,3]  -> [1 2 3 5]
 *
 * Approaches:
 *   1. Collect, sort, rebuild      O((m+n) log(m+n)) time, O(m+n) space
 *   2. Recursive merge             O(m+n) time, O(m+n) stack
 *   3. Iterative with dummy  ⭐     O(m+n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

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

// ---------- Approach 1: Collect, Sort, Rebuild ----------
func mergeTwoListsSort(l1, l2 *ListNode) *ListNode {
	vals := append(toSlice(l1), toSlice(l2)...)
	slices.Sort(vals)
	return build(vals)
}

// ---------- Approach 2: Recursive Merge ----------
func mergeTwoListsRecursive(l1, l2 *ListNode) *ListNode {
	if l1 == nil {
		return l2
	}
	if l2 == nil {
		return l1
	}
	if l1.Val <= l2.Val {
		l1.Next = mergeTwoListsRecursive(l1.Next, l2)
		return l1
	}
	l2.Next = mergeTwoListsRecursive(l1, l2.Next)
	return l2
}

// ---------- Approach 3: Iterative With Dummy ⭐ ----------
func mergeTwoLists(l1, l2 *ListNode) *ListNode {
	dummy := &ListNode{} // removes the "who is head?" case
	tail := dummy
	for l1 != nil && l2 != nil {
		if l1.Val <= l2.Val { // <= keeps it stable
			tail.Next, l1 = l1, l1.Next
		} else {
			tail.Next, l2 = l2, l2.Next
		}
		tail = tail.Next
	}
	if l1 != nil { // attach the leftover in one step
		tail.Next = l1
	} else {
		tail.Next = l2
	}
	return dummy.Next
}

// ---------- Driver ----------
func main() {
	tests := [][2][]int{{{1, 2, 4}, {1, 3, 4}}, {{}, {}}, {{}, {0}}, {{5}, {1, 2, 3}}}
	for _, t := range tests { // fresh lists per approach: merging splices nodes
		fmt.Println("sort     :", toSlice(mergeTwoListsSort(build(t[0]), build(t[1]))))
		fmt.Println("recursive:", toSlice(mergeTwoListsRecursive(build(t[0]), build(t[1]))))
		fmt.Println("iterative:", toSlice(mergeTwoLists(build(t[0]), build(t[1]))))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - append(a, b...) concatenates two slices.
 * - `tail.Next, l1 = l1, l1.Next` links and advances in one statement.
 * - Go has no ternary, so attaching the leftover is an if/else.
 */
