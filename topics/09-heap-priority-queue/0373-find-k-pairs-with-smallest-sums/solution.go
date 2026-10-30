/*
 * 0373. Find K Pairs with Smallest Sums  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
 *
 * Problem: Two ascending arrays; return the k pairs (u, v) with the
 *          smallest sums u + v.
 *
 * Examples:
 *   [1,7,11], [2,4,6], k 3   -> [[1 2] [1 4] [1 6]]
 *   [1,1,2],  [1,2,3], k 2   -> [[1 1] [1 1]]
 *   [1,2],    [3],     k 3   -> [[1 3] [2 3]]   (k > number of pairs)
 *
 * Approaches:
 *   1. All pairs, sort           O(m*n log(m*n)) time, O(m*n) space
 *   2. Min-heap frontier  ⭐      O(k log k) time, O(k) space   <- go-to
 */

package main

import (
	"cmp"
	"container/heap"
	"fmt"
	"slices"
)

type cell struct{ sum, i, j int }

func less(x, y cell) bool { // sum, then i, then j: deterministic ties
	return cmp.Or(cmp.Compare(x.sum, y.sum), cmp.Compare(x.i, y.i), cmp.Compare(x.j, y.j)) < 0
}

// ---------- Approach 1: All Pairs, Sort ----------
func kSmallestPairsBrute(a, b []int, k int) [][]int {
	all := []cell{}
	for i := range a {
		for j := range b {
			all = append(all, cell{a[i] + b[j], i, j})
		}
	}
	slices.SortFunc(all, func(x, y cell) int {
		return cmp.Or(cmp.Compare(x.sum, y.sum), cmp.Compare(x.i, y.i), cmp.Compare(x.j, y.j))
	})
	res := [][]int{}
	for t := 0; t < k && t < len(all); t++ {
		res = append(res, []int{a[all[t].i], b[all[t].j]})
	}
	return res
}

// ---------- Approach 2: Min-Heap Frontier ⭐ ----------
type cellHeap []cell

func (h cellHeap) Len() int           { return len(h) }
func (h cellHeap) Less(i, j int) bool { return less(h[i], h[j]) }
func (h cellHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *cellHeap) Push(x any)        { *h = append(*h, x.(cell)) }
func (h *cellHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func kSmallestPairs(a, b []int, k int) [][]int {
	h := &cellHeap{}
	for i := 0; i < min(k, len(a)); i++ { // head of each row
		*h = append(*h, cell{a[i] + b[0], i, 0})
	}
	heap.Init(h)
	res := [][]int{}
	for h.Len() > 0 && len(res) < k {
		c := heap.Pop(h).(cell)
		res = append(res, []int{a[c.i], b[c.j]})
		if c.j+1 < len(b) { // move right in row i
			heap.Push(h, cell{a[c.i] + b[c.j+1], c.i, c.j + 1})
		}
	}
	return res
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		a, b []int
		k    int
	}{{[]int{1, 7, 11}, []int{2, 4, 6}, 3}, {[]int{1, 1, 2}, []int{1, 2, 3}, 2}, {[]int{1, 2}, []int{3}, 3}}
	for _, t := range tests {
		fmt.Println("brute:", kSmallestPairsBrute(t.a, t.b, t.k))
		fmt.Println("heap :", kSmallestPairs(t.a, t.b, t.k))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - cmp.Or(cmp.Compare(...), ...) builds a multi-key comparison (Go 1.22+).
 * - One `less` helper keeps the heap and the sort tie-breaking identical.
 */
