/*
 * 0092. Reverse Linked List II  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/reverse-linked-list-ii/
 *
 * Problem: Reverse the nodes from position left to right (1-indexed).
 *
 * Examples:
 *   [1,2,3,4,5], left 2, right 4  -> [1 4 3 2 5]
 *   [5],         left 1, right 1  -> [5]
 *   [3,5],       left 1, right 2  -> [5 3]
 *   [1,2,3],     left 1, right 3  -> [3 2 1]
 *   [1,2,3],     left 2, right 2  -> [1 2 3]
 *
 * Approaches:
 *   1. Values array, reverse segment   O(n) time, O(n) space
 *   2. Head insertion with dummy  ⭐    O(n) time, O(1) space   <- go-to
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

// ---------- Approach 1: Values Array, Reverse Segment ----------
func reverseBetweenArray(head *ListNode, left, right int) *ListNode {
	vals := toSlice(head)
	slices.Reverse(vals[left-1 : right]) // 1-indexed, inclusive
	return build(vals)
}

// ---------- Approach 2: Head Insertion With Dummy ⭐ ----------
func reverseBetween(head *ListNode, left, right int) *ListNode {
	dummy := &ListNode{Next: head} // left = 1 becomes a normal case
	prev := dummy
	for i := 1; i < left; i++ { // node before position left
		prev = prev.Next
	}
	curr := prev.Next // stays fixed; ends as the range's tail
	for i := 0; i < right-left; i++ {
		nxt := curr.Next // move nxt to right after prev
		curr.Next = nxt.Next
		nxt.Next = prev.Next
		prev.Next = nxt
	}
	return dummy.Next
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		vals        []int
		left, right int
	}{
		{[]int{1, 2, 3, 4, 5}, 2, 4}, {[]int{5}, 1, 1}, {[]int{3, 5}, 1, 2}, {[]int{1, 2, 3}, 1, 3}, {[]int{1, 2, 3}, 2, 2},
	}
	for _, t := range tests {
		fmt.Println("array    :", toSlice(reverseBetweenArray(build(t.vals), t.left, t.right)))
		fmt.Println("headInsert:", toSlice(reverseBetween(build(t.vals), t.left, t.right)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - vals[left-1:right] is the 1-indexed inclusive range as a sub-slice.
 * - Struct fields can share a type: left, right int.
 */
