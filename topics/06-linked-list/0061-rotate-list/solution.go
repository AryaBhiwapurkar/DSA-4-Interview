/*
 * 0061. Rotate List  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/rotate-list/
 *
 * Problem: Rotate a linked list to the right by k places. k can be huge.
 *
 * Examples:
 *   [1,2,3,4,5], k 2   -> [4 5 1 2 3]
 *   [0,1,2],     k 4   -> [2 0 1]
 *   [],          k 0   -> []
 *   [1],         k 99  -> [1]
 *   [1,2],       k 2   -> [1 2]
 *
 * Approaches:
 *   1. Rotate one step, (k mod n) times   O(n * (k mod n)) time, O(1) space
 *   2. Ring and cut  ⭐                    O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

// ---------- Approach 1: Rotate One Step at a Time ----------
func rotateRightSteps(head *ListNode, k int) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	n := 0
	for p := head; p != nil; p = p.Next {
		n++
	}
	for s := 0; s < k%n; s++ { // without %n, k = 2e9 never finishes
		prev := head
		for prev.Next.Next != nil { // second-to-last
			prev = prev.Next
		}
		last := prev.Next
		prev.Next = nil
		last.Next = head
		head = last
	}
	return head
}

// ---------- Approach 2: Ring and Cut ⭐ ----------
func rotateRight(head *ListNode, k int) *ListNode {
	if head == nil {
		return head
	}
	n, tail := 1, head
	for tail.Next != nil {
		tail = tail.Next
		n++
	}
	k %= n // n > 0 here: safe
	if k == 0 {
		return head // check BEFORE making the ring
	}
	tail.Next = head // close the ring
	newTail := head
	for i := 0; i < n-k-1; i++ {
		newTail = newTail.Next
	}
	newHead := newTail.Next
	newTail.Next = nil // cut the ring
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
	tests := []struct {
		vals []int
		k    int
	}{
		{[]int{1, 2, 3, 4, 5}, 2}, {[]int{0, 1, 2}, 4}, {[]int{}, 0}, {[]int{1}, 99}, {[]int{1, 2}, 2},
	}
	for _, t := range tests {
		fmt.Println("steps:", toSlice(rotateRightSteps(build(t.vals), t.k)))
		fmt.Println("ring :", toSlice(rotateRight(build(t.vals), t.k)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Integer modulo by zero panics at runtime; guard n > 0 first.
 * - `n, tail := 1, head` initialises a counter and a pointer together.
 */
