/*
 * 0086. Partition List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/partition-list/
 *
 * Problem: Move nodes with value < x before nodes with value >= x, keeping
 *          the original order within each group.
 *
 * Examples:
 *   [1,4,3,2,5,2], x 3  -> [1 2 2 4 3 5]
 *   [2,1],         x 2  -> [1 2]
 *   [],            x 0  -> []
 *   [3,1,2],       x 4  -> [3 1 2]
 *   [3,1,2],       x 0  -> [3 1 2]
 *
 * Approaches:
 *   1. Two value arrays, rebuild   O(n) time, O(n) space
 *   2. Two dummy lists  ⭐          O(n) time, O(1) extra space   <- go-to
 */

package main

import "fmt"

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

// ---------- Approach 1: Two Value Arrays, Rebuild ----------
func partitionArray(head *ListNode, x int) *ListNode {
	less, rest := []int{}, []int{}
	for p := head; p != nil; p = p.Next {
		if p.Val < x {
			less = append(less, p.Val)
		} else {
			rest = append(rest, p.Val)
		}
	}
	return build(append(less, rest...))
}

// ---------- Approach 2: Two Dummy Lists ⭐ ----------
func partition(head *ListNode, x int) *ListNode {
	lessDummy, geDummy := &ListNode{}, &ListNode{}
	less, ge := lessDummy, geDummy
	for p := head; p != nil; p = p.Next {
		if p.Val < x { // appending keeps the order (stable)
			less.Next = p
			less = p
		} else {
			ge.Next = p
			ge = p
		}
	}
	ge.Next = nil // or the old link may form a cycle
	less.Next = geDummy.Next
	return lessDummy.Next
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		vals []int
		x    int
	}{
		{[]int{1, 4, 3, 2, 5, 2}, 3}, {[]int{2, 1}, 2}, {[]int{}, 0}, {[]int{3, 1, 2}, 4}, {[]int{3, 1, 2}, 0},
	}
	for _, t := range tests {
		fmt.Println("arrays :", toSlice(partitionArray(build(t.vals), t.x)))
		fmt.Println("dummies:", toSlice(partition(build(t.vals), t.x)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - append(a, b...) concatenates; it may reuse a's backing array.
 * - The loop reads p.Next after relinking p, which is safe here because
 *   p.Next is only changed for the previous tail, not for p itself.
 */
