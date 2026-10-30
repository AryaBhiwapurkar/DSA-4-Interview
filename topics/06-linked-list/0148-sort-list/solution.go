/*
 * 0148. Sort List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/sort-list/
 *
 * Problem: Sort a linked list ascending in O(n log n) time.
 *
 * Examples:
 *   [4,2,1,3]      -> [1 2 3 4]
 *   [-1,5,3,4,0]   -> [-1 0 3 4 5]
 *   []             -> []
 *   [1]            -> [1]
 *   [2,1,2,1]      -> [1 1 2 2]
 *
 * Approaches:
 *   1. Copy values, sort, write back   O(n log n) time, O(n) space
 *   2. Top-down merge sort  ⭐          O(n log n) time, O(log n) stack   <- go-to
 *   3. Bottom-up merge sort            O(n log n) time, O(1) space
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

func merge(a, b *ListNode) *ListNode {
	dummy := &ListNode{}
	tail := dummy
	for a != nil && b != nil {
		if a.Val <= b.Val { // <= keeps it stable
			tail.Next, a = a, a.Next
		} else {
			tail.Next, b = b, b.Next
		}
		tail = tail.Next
	}
	if a != nil {
		tail.Next = a
	} else {
		tail.Next = b
	}
	return dummy.Next
}

// ---------- Approach 1: Copy Values, Sort, Write Back ----------
func sortListCopy(head *ListNode) *ListNode {
	vals := []int{}
	for p := head; p != nil; p = p.Next {
		vals = append(vals, p.Val)
	}
	slices.Sort(vals)
	i := 0
	for p := head; p != nil; p = p.Next {
		p.Val = vals[i]
		i++
	}
	return head
}

// ---------- Approach 2: Top-Down Merge Sort ⭐ ----------
func sortList(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	slow, fast := head, head.Next // head.Next: 2 nodes split 1 + 1
	for fast != nil && fast.Next != nil {
		slow, fast = slow.Next, fast.Next.Next
	}
	right := slow.Next
	slow.Next = nil // cut before recursing
	return merge(sortList(head), sortList(right))
}

// ---------- Approach 3: Bottom-Up Merge Sort ----------
func split(head *ListNode, n int) *ListNode { // cut after n nodes, return the rest
	for i := 1; head != nil && i < n; i++ {
		head = head.Next
	}
	if head == nil {
		return nil
	}
	rest := head.Next
	head.Next = nil
	return rest
}

func sortListBottomUp(head *ListNode) *ListNode {
	n := 0
	for p := head; p != nil; p = p.Next {
		n++
	}
	dummy := &ListNode{Next: head}
	for width := 1; width < n; width *= 2 {
		tail, curr := dummy, dummy.Next
		for curr != nil {
			left := curr
			right := split(left, width)
			curr = split(right, width)
			tail.Next = merge(left, right)
			for tail.Next != nil { // advance to the end of the merged run
				tail = tail.Next
			}
		}
	}
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
	for _, v := range [][]int{{4, 2, 1, 3}, {-1, 5, 3, 4, 0}, {}, {1}, {2, 1, 2, 1}} {
		fmt.Println("copy    :", toSlice(sortListCopy(build(v))))
		fmt.Println("topDown :", toSlice(sortList(build(v))))
		fmt.Println("bottomUp:", toSlice(sortListBottomUp(build(v))))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A shared merge() helper serves both merge sort variants.
 * - `for width := 1; width < n; width *= 2` doubles the run size.
 * - Recursion on a list is fine in Go: goroutine stacks grow dynamically.
 */
