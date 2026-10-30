/*
 * 0143. Reorder List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/reorder-list/
 *
 * Problem: Relink L0->L1->...->Ln into L0->Ln->L1->Ln-1->... in place.
 *
 * Examples:
 *   [1,2,3,4]    -> [1 4 2 3]
 *   [1,2,3,4,5]  -> [1 5 2 4 3]
 *   [1]          -> [1]
 *   [1,2]        -> [1 2]
 *
 * Approaches:
 *   1. Array of nodes + two pointers   O(n) time, O(n) space
 *   2. Mid + reverse + merge  ⭐        O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

// ---------- Approach 1: Array of Nodes + Two Pointers ----------
func reorderListArray(head *ListNode) {
	nodes := []*ListNode{}
	for p := head; p != nil; p = p.Next {
		nodes = append(nodes, p)
	}
	i, j := 0, len(nodes)-1
	for i < j {
		nodes[i].Next = nodes[j]
		i++
		if i == j {
			break
		}
		nodes[j].Next = nodes[i]
		j--
	}
	nodes[i].Next = nil // new tail: cut the old links
}

// ---------- Approach 2: Mid + Reverse + Merge ⭐ ----------
func reorderList(head *ListNode) {
	slow, fast := head, head // find the end of the first half
	for fast.Next != nil && fast.Next.Next != nil {
		slow, fast = slow.Next, fast.Next.Next
	}
	second := slow.Next
	slow.Next = nil // cut, or the weave makes a cycle

	var prev *ListNode // reverse the second half
	for second != nil {
		second.Next, prev, second = prev, second, second.Next
	}

	first, back := head, prev // weave: first is never shorter
	for back != nil {
		n1, n2 := first.Next, back.Next // save both before relinking
		first.Next, back.Next = back, n1
		first, back = n1, n2
	}
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
	for _, v := range [][]int{{1, 2, 3, 4}, {1, 2, 3, 4, 5}, {1}, {1, 2}} { // fresh list per approach
		a := build(v)
		reorderListArray(a)
		fmt.Println("array  :", toSlice(a))
		b := build(v)
		reorderList(b)
		fmt.Println("inPlace:", toSlice(b))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - []*ListNode is a slice of pointers: indexing gives the node to relink.
 * - `first.Next, back.Next = back, n1` relinks two nodes in one statement.
 * - A function with no return type mutates through the pointer it receives.
 */
