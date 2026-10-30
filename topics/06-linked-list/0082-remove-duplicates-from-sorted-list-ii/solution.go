/*
 * 0082. Remove Duplicates from Sorted List II  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
 *
 * Problem: In a sorted list, delete every node whose value is duplicated,
 *          keeping only values that appear exactly once.
 *
 * Examples:
 *   [1,2,3,3,4,4,5]  -> [1 2 5]
 *   [1,1,1,2,3]      -> [2 3]
 *   []               -> []
 *   [1,1]            -> []
 *   [1,2,2]          -> [1]
 *
 * Approaches:
 *   1. Count values, then relink   O(n) time, O(n) space
 *   2. Dummy + skip runs  ⭐        O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

// ---------- Approach 1: Count Values, Then Relink ----------
func deleteDuplicatesCount(head *ListNode) *ListNode {
	cnt := map[int]int{}
	for p := head; p != nil; p = p.Next {
		cnt[p.Val]++
	}
	dummy := &ListNode{}
	tail := dummy
	for p := head; p != nil; p = p.Next {
		if cnt[p.Val] == 1 { // keep unique values only
			tail.Next = p
			tail = p
		}
	}
	tail.Next = nil // cut whatever followed the last kept node
	return dummy.Next
}

// ---------- Approach 2: Dummy + Skip Runs ⭐ ----------
func deleteDuplicates(head *ListNode) *ListNode {
	dummy := &ListNode{Next: head} // a run at the head becomes a normal case
	prev, curr := dummy, head
	for curr != nil {
		if curr.Next != nil && curr.Val == curr.Next.Val {
			v := curr.Val
			for curr != nil && curr.Val == v { // skip the whole run
				curr = curr.Next
			}
			prev.Next = curr // prev stays: curr may start another run
		} else {
			prev, curr = curr, curr.Next // curr is unique
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
	for _, v := range [][]int{{1, 2, 3, 3, 4, 4, 5}, {1, 1, 1, 2, 3}, {}, {1, 1}, {1, 2, 2}} {
		fmt.Println("count:", toSlice(deleteDuplicatesCount(build(v))))
		fmt.Println("skip :", toSlice(deleteDuplicates(build(v))))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - cnt[k]++ works on a missing key (zero value 0).
 * - Guard order matters: `curr != nil && curr.Val == v`.
 * - Relinking kept nodes needs a final tail.Next = nil to cut the rest.
 */
