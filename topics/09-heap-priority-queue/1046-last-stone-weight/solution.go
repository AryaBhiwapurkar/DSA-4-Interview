/*
 * 1046. Last Stone Weight  |  Easy  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/last-stone-weight/
 *
 * Problem: Repeatedly smash the two heaviest stones; equal ones vanish,
 *          otherwise the difference remains. Return the last weight or 0.
 *
 * Examples:
 *   [2,7,4,1,8,1]  -> 1
 *   [1]            -> 1
 *   [2,2]          -> 0
 *   [10,4,2,10]    -> 2
 *
 * Approaches:
 *   1. Sort every round   O(n^2 log n) time, O(1) extra
 *   2. Max-heap  ⭐        O(n log n) time, O(n) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
)

// ---------- Approach 1: Sort Every Round ----------
func lastStoneWeightSort(stones []int) int {
	s := slices.Clone(stones)
	for len(s) > 1 {
		slices.Sort(s)
		y, x := s[len(s)-1], s[len(s)-2]
		s = s[:len(s)-2]
		if y > x {
			s = append(s, y-x)
		}
	}
	if len(s) == 0 {
		return 0
	}
	return s[0]
}

// ---------- Approach 2: Max-Heap ⭐ ----------
type MaxHeap []int

func (h MaxHeap) Len() int           { return len(h) }
func (h MaxHeap) Less(i, j int) bool { return h[i] > h[j] } // > : max-heap
func (h MaxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *MaxHeap) Push(x any)        { *h = append(*h, x.(int)) }
func (h *MaxHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func lastStoneWeight(stones []int) int {
	h := MaxHeap(slices.Clone(stones))
	heap.Init(&h)
	for h.Len() > 1 {
		y, x := heap.Pop(&h).(int), heap.Pop(&h).(int)
		if y > x { // equal stones both vanish
			heap.Push(&h, y-x)
		}
	}
	if h.Len() == 0 {
		return 0
	}
	return h[0]
}

// ---------- Driver ----------
func main() {
	for _, s := range [][]int{{2, 7, 4, 1, 8, 1}, {1}, {2, 2}, {10, 4, 2, 10}} {
		fmt.Println("sort:", lastStoneWeightSort(s))
		fmt.Println("heap:", lastStoneWeight(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - MaxHeap(slice) converts a []int to the heap type; heap.Init heapifies in O(n).
 * - The two heap.Pop calls in one assignment run left to right.
 */
