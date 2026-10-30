/*
 * 0973. K Closest Points to Origin  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/k-closest-points-to-origin/
 *
 * Problem: Return the k points closest to (0,0). Any order.
 *
 * Examples (printed sorted):
 *   [[1,3],[-2,2]],          k 1  -> [[-2 2]]
 *   [[3,3],[5,-1],[-2,4]],   k 2  -> [[-2 4] [3 3]]
 *   [[0,1],[1,0]],           k 2  -> [[0 1] [1 0]]
 *
 * Approaches:
 *   1. Sort by distance         O(n log n) time, O(n) space
 *   2. Max-heap of size k  ⭐    O(n log k) time, O(k) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
)

func d2(p []int) int { return p[0]*p[0] + p[1]*p[1] }

// ---------- Approach 1: Sort by Distance ----------
func kClosestSort(points [][]int, k int) [][]int {
	pts := slices.Clone(points)
	slices.SortFunc(pts, func(a, b []int) int { return d2(a) - d2(b) })
	return pts[:k]
}

// ---------- Approach 2: Max-Heap of Size k ⭐ ----------
type item struct{ dist, idx int }
type MaxHeap []item

func (h MaxHeap) Len() int           { return len(h) }
func (h MaxHeap) Less(i, j int) bool { return h[i].dist > h[j].dist } // farthest on top
func (h MaxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *MaxHeap) Push(x any)        { *h = append(*h, x.(item)) }
func (h *MaxHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func kClosest(points [][]int, k int) [][]int {
	h := &MaxHeap{}
	for i, p := range points {
		heap.Push(h, item{d2(p), i})
		if h.Len() > k {
			heap.Pop(h) // evict the farthest of the current k
		}
	}
	res := [][]int{}
	for _, it := range *h {
		res = append(res, points[it.idx])
	}
	return res
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		pts [][]int
		k   int
	}{
		{[][]int{{1, 3}, {-2, 2}}, 1}, {[][]int{{3, 3}, {5, -1}, {-2, 4}}, 2}, {[][]int{{0, 1}, {1, 0}}, 2},
	}
	cmp := func(a, b []int) int { return slices.Compare(a, b) }
	for _, t := range tests {
		a, b := kClosestSort(t.pts, t.k), kClosest(t.pts, t.k)
		slices.SortFunc(a, cmp) // normalize: any order is accepted
		slices.SortFunc(b, cmp)
		fmt.Println("sort:", a)
		fmt.Println("heap:", b)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.SortFunc takes a comparator returning <0, 0, >0.
 * - slices.Compare compares two slices lexicographically.
 * - Ranging over *h reads the heap's backing slice (no particular order).
 */
