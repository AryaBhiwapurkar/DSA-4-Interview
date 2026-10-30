/*
 * 0002. Add Two Numbers  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/add-two-numbers/
 *
 * Problem: Two numbers stored as digit lists, ones digit first. Return
 *          their sum in the same format.
 *
 * Examples:
 *   [2,4,3],         [5,6,4]    -> [7 0 8]
 *   [0],             [0]        -> [0]
 *   [9,9,9,9,9,9,9], [9,9,9,9]  -> [8 9 9 9 0 0 0 1]
 *   [5],             [5]        -> [0 1]
 *   [1,8],           [0]        -> [1 8]
 *
 * Approaches:
 *   1. Iterative with carry  ⭐   O(max(m,n)) time, O(1) extra space   <- go-to
 *   2. Recursive                 O(max(m,n)) time, O(max(m,n)) stack
 */

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

// ---------- Approach 1: Iterative With Carry ⭐ ----------
func addTwoNumbers(l1, l2 *ListNode) *ListNode {
	dummy := &ListNode{}
	tail := dummy
	carry := 0
	for l1 != nil || l2 != nil || carry > 0 { // carry keeps the loop alive for the last digit
		sum := carry
		if l1 != nil {
			sum += l1.Val
			l1 = l1.Next
		}
		if l2 != nil {
			sum += l2.Val
			l2 = l2.Next
		}
		tail.Next = &ListNode{Val: sum % 10}
		tail = tail.Next
		carry = sum / 10
	}
	return dummy.Next
}

// ---------- Approach 2: Recursive ----------
func addTwoNumbersRecursive(l1, l2 *ListNode, carry int) *ListNode {
	if l1 == nil && l2 == nil && carry == 0 {
		return nil
	}
	sum := carry
	var n1, n2 *ListNode
	if l1 != nil {
		sum += l1.Val
		n1 = l1.Next
	}
	if l2 != nil {
		sum += l2.Val
		n2 = l2.Next
	}
	return &ListNode{sum % 10, addTwoNumbersRecursive(n1, n2, sum/10)}
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
	tests := [][2][]int{
		{{2, 4, 3}, {5, 6, 4}}, {{0}, {0}}, {{9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}}, {{5}, {5}}, {{1, 8}, {0}},
	}
	for _, t := range tests {
		fmt.Println("iterative:", toSlice(addTwoNumbers(build(t[0]), build(t[1]))))
		fmt.Println("recursive:", toSlice(addTwoNumbersRecursive(build(t[0]), build(t[1]), 0)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go has no default parameters: pass carry = 0 explicitly.
 * - `var n1, n2 *ListNode` declares two nil pointers at once.
 * - Positional struct literal &ListNode{val, next} builds and links in one go.
 */
