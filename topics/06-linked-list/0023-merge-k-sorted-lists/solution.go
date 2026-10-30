/*
 * 0023. Merge k Sorted Lists  |  Hard  |  Linked List
 * Link: https://leetcode.com/problems/merge-k-sorted-lists/
 *
 * Problem: Merge k sorted linked lists into one sorted list.
 *
 * Examples:
 *   [[1,4,5],[1,3,4],[2,6]]  -> [1 1 2 3 4 4 5 6]
 *   []                       -> []
 *   [[]]                     -> []
 *   [[2],[],[1]]             -> [1 2]
 *
 * Approaches:
 *   1. Collect, sort, rebuild        O(N log N) time, O(N) space
 *   2. Min-heap of heads  ⭐          O(N log k) time, O(k) space   <- go-to
 *   3. Divide & conquer merging      O(N log k) time, O(1) extra space
 */

package main

import (
	"container/heap"
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
func mergeKListsSort(lists []*ListNode) *ListNode {
	vals := []int{}
	for _, l := range lists {
		vals = append(vals, toSlice(l)...)
	}
	slices.Sort(vals)
	return build(vals)
}

// ---------- Approach 2: Min-Heap of Heads ⭐ ----------
type nodeHeap []*ListNode

func (h nodeHeap) Len() int           { return len(h) }
func (h nodeHeap) Less(i, j int) bool { return h[i].Val < h[j].Val } // < : MIN-heap
func (h nodeHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *nodeHeap) Push(x any)        { *h = append(*h, x.(*ListNode)) }
func (h *nodeHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func mergeKLists(lists []*ListNode) *ListNode {
	h := &nodeHeap{}
	for _, l := range lists {
		if l != nil { // skip empty lists
			*h = append(*h, l)
		}
	}
	heap.Init(h)
	dummy := &ListNode{}
	tail := dummy
	for h.Len() > 0 {
		n := heap.Pop(h).(*ListNode) // heap.Pop, not h.Pop: keeps the heap invariant
		tail.Next = n
		tail = n
		if n.Next != nil {
			heap.Push(h, n.Next)
		}
	}
	return dummy.Next
}

// ---------- Approach 3: Divide & Conquer Merging ----------
func mergeTwo(a, b *ListNode) *ListNode {
	dummy := &ListNode{}
	tail := dummy
	for a != nil && b != nil {
		if a.Val <= b.Val {
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

func mergeKListsDivide(lists []*ListNode) *ListNode {
	k := len(lists)
	if k == 0 {
		return nil
	}
	for step := 1; step < k; step *= 2 { // log k rounds
		for i := 0; i+step < k; i += 2 * step {
			lists[i] = mergeTwo(lists[i], lists[i+step])
		}
	}
	return lists[0]
}

// ---------- Driver ----------
func buildAll(vs [][]int) []*ListNode {
	out := []*ListNode{}
	for _, v := range vs {
		out = append(out, build(v))
	}
	return out
}

func main() {
	tests := [][][]int{{{1, 4, 5}, {1, 3, 4}, {2, 6}}, {}, {{}}, {{2}, {}, {1}}}
	for _, t := range tests { // fresh lists per approach: merging splices nodes
		fmt.Println("sort  :", toSlice(mergeKListsSort(buildAll(t))))
		fmt.Println("heap  :", toSlice(mergeKLists(buildAll(t))))
		fmt.Println("divide:", toSlice(mergeKListsDivide(buildAll(t))))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - container/heap needs Len, Less, Swap (value receiver) and Push, Pop
 *   (pointer receiver); call heap.Init/Push/Pop, never h.Push directly.
 * - heap.Pop returns `any`; assert the type: heap.Pop(h).(*ListNode).
 * - Filling the slice then heap.Init(h) is O(k), cheaper than k pushes.
 */
