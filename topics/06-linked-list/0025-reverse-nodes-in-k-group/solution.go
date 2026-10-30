/*
 * 0025. Reverse Nodes in k-Group  |  Hard  |  Linked List
 * Link: https://leetcode.com/problems/reverse-nodes-in-k-group/
 *
 * Problem: Reverse the list k nodes at a time; a final group shorter than
 *          k stays as is. Relink nodes, don't change values.
 *
 * Examples:
 *   [1,2,3,4,5], k 2  -> [2 1 4 3 5]
 *   [1,2,3,4,5], k 3  -> [3 2 1 4 5]
 *   [1,2,3,4],   k 4  -> [4 3 2 1]
 *   [1,2],       k 1  -> [1 2]
 *   [1],         k 1  -> [1]
 *
 * Approaches:
 *   1. Values array, reverse chunks   O(n) time, O(n) space
 *   2. Iterative group reversal  ⭐    O(n) time, O(1) space   <- go-to
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

// ---------- Approach 1: Values Array, Reverse Chunks ----------
func reverseKGroupArray(head *ListNode, k int) *ListNode {
	vals := toSlice(head)
	for i := 0; i+k <= len(vals); i += k { // full chunks only
		slices.Reverse(vals[i : i+k])
	}
	return build(vals)
}

// ---------- Approach 2: Iterative Group Reversal ⭐ ----------
func reverseKGroup(head *ListNode, k int) *ListNode {
	dummy := &ListNode{Next: head}
	groupPrev := dummy
	for {
		kth := groupPrev
		for i := 0; i < k && kth != nil; i++ {
			kth = kth.Next
		}
		if kth == nil { // fewer than k left: keep as is
			break
		}
		groupNext := kth.Next

		prev, curr := groupNext, groupPrev.Next // prev = groupNext, NOT nil
		for curr != groupNext {
			curr.Next, prev, curr = prev, curr, curr.Next
		}

		oldFirst := groupPrev.Next // now the group's last node
		groupPrev.Next = kth
		groupPrev = oldFirst
	}
	return dummy.Next
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		vals []int
		k    int
	}{
		{[]int{1, 2, 3, 4, 5}, 2}, {[]int{1, 2, 3, 4, 5}, 3}, {[]int{1, 2, 3, 4}, 4}, {[]int{1, 2}, 1}, {[]int{1}, 1},
	}
	for _, t := range tests {
		fmt.Println("array    :", toSlice(reverseKGroupArray(build(t.vals), t.k)))
		fmt.Println("iterative:", toSlice(reverseKGroup(build(t.vals), t.k)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Reverse(s[i:i+k]) reverses a sub-slice in place (it shares memory).
 * - `for { ... break }` is Go's infinite loop.
 * - Pointer comparison `curr != groupNext` works with nil too.
 */
