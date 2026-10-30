/*
 * 0502. IPO  |  Hard  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/ipo/
 *
 * Problem: Start with capital w; do at most k distinct projects, each needing
 *          capital[i] and adding profits[i]. Maximize final capital.
 *
 * Examples:
 *   k 2, w 0, profits [1,2,3], capital [0,1,1]    -> 4
 *   k 3, w 0, profits [1,2,3], capital [0,1,2]    -> 6
 *   k 1, w 0, profits [1],     capital [1]        -> 0   (nothing affordable)
 *   k 10, w 0, profits [1,2,3], capital [0,1,1]   -> 6   (runs out of projects)
 *
 * Approaches:
 *   1. Rescan each round        O(k * n) time, O(n) space
 *   2. Sort + max-heap  ⭐       O(n log n + k log n) time, O(n) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"sort"
)

// ---------- Approach 1: Rescan Each Round ----------
func findMaximizedCapitalBrute(k, w int, profits, capital []int) int {
	used := make([]bool, len(profits))
	for ; k > 0; k-- {
		best := -1
		for i := range profits {
			if !used[i] && capital[i] <= w && (best == -1 || profits[i] > profits[best]) {
				best = i
			}
		}
		if best == -1 { // nothing affordable
			break
		}
		used[best] = true
		w += profits[best]
	}
	return w
}

// ---------- Approach 2: Sort + Max-Heap ⭐ ----------
type MaxHeap []int

func (h MaxHeap) Len() int           { return len(h) }
func (h MaxHeap) Less(i, j int) bool { return h[i] > h[j] }
func (h MaxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *MaxHeap) Push(x any)        { *h = append(*h, x.(int)) }
func (h *MaxHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func findMaximizedCapital(k, w int, profits, capital []int) int {
	idx := make([]int, len(profits))
	for i := range idx {
		idx[i] = i
	}
	sort.Slice(idx, func(a, b int) bool { return capital[idx[a]] < capital[idx[b]] }) // by capital needed
	h := &MaxHeap{}                                                                   // profits of affordable projects
	i := 0
	for ; k > 0; k-- {
		for i < len(idx) && capital[idx[i]] <= w { // newly affordable
			heap.Push(h, profits[idx[i]])
			i++
		}
		if h.Len() == 0 {
			break
		}
		w += heap.Pop(h).(int) // greedy: best affordable (capital never shrinks)
	}
	return w
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		k, w             int
		profits, capital []int
	}{
		{2, 0, []int{1, 2, 3}, []int{0, 1, 1}}, {3, 0, []int{1, 2, 3}, []int{0, 1, 2}},
		{1, 0, []int{1}, []int{1}}, {10, 0, []int{1, 2, 3}, []int{0, 1, 1}},
	}
	for _, t := range tests {
		fmt.Println("brute:", findMaximizedCapitalBrute(t.k, t.w, t.profits, t.capital))
		fmt.Println("heap :", findMaximizedCapital(t.k, t.w, t.profits, t.capital))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Sorting an index slice keeps profits and capital paired without a struct.
 * - `for ; k > 0; k--` counts down a parameter in place.
 */
