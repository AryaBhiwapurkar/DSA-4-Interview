/*
 * 0141. Linked List Cycle  |  Easy  |  Linked List
 * Link: https://leetcode.com/problems/linked-list-cycle/
 *
 * Problem: Return whether a linked list contains a cycle. (pos below only
 *          says where the tail links back; it isn't an input.)
 *
 * Examples:
 *   [3,2,0,-4], pos 1   -> true
 *   [1,2],      pos 0   -> true
 *   [1],        pos -1  -> false
 *   [],         pos -1  -> false
 *   [1],        pos 0   -> true   (self-loop)
 *   [1,2,3],    pos -1  -> false
 *
 * Approaches:
 *   1. Hash set of visited nodes   O(n) time, O(n) space
 *   2. Floyd fast/slow  ⭐          O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

// ---------- Approach 1: Hash Set of Visited Nodes ----------
func hasCycleSet(head *ListNode) bool {
	seen := map[*ListNode]bool{} // node identity, not values
	for p := head; p != nil; p = p.Next {
		if seen[p] {
			return true
		}
		seen[p] = true
	}
	return false
}

// ---------- Approach 2: Floyd Fast/Slow ⭐ ----------
func hasCycle(head *ListNode) bool {
	slow, fast := head, head
	for fast != nil && fast.Next != nil { // both needed before fast.Next.Next
		slow = slow.Next
		fast = fast.Next.Next
		if slow == fast { // check AFTER moving: they start equal
			return true
		}
	}
	return false
}

// ---------- Driver ----------
func buildCycle(vals []int, pos int) *ListNode {
	dummy := &ListNode{}
	tail := dummy
	var entry *ListNode
	for i, v := range vals {
		tail.Next = &ListNode{Val: v}
		tail = tail.Next
		if i == pos {
			entry = tail
		}
	}
	if entry != nil {
		tail.Next = entry // close the loop
	}
	return dummy.Next
}

func main() {
	tests := []struct {
		vals []int
		pos  int
	}{
		{[]int{3, 2, 0, -4}, 1}, {[]int{1, 2}, 0}, {[]int{1}, -1}, {[]int{}, -1}, {[]int{1}, 0}, {[]int{1, 2, 3}, -1},
	}
	for _, t := range tests {
		head := buildCycle(t.vals, t.pos) // read-only approaches: one list is enough
		fmt.Println("hashSet:", hasCycleSet(head))
		fmt.Println("floyd  :", hasCycle(head))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Pointers are comparable, so map[*ListNode]bool keys on node identity.
 * - A missing key in map[...]bool reads as false: no comma-ok needed here.
 * - == on pointers compares addresses, not the structs they point to.
 */
