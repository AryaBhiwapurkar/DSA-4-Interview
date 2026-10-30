/*
 * 0215. Kth Largest Element in an Array  |  Medium  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/kth-largest-element-in-an-array/
 *
 * Problem: Return the k-th largest element (duplicates count).
 *
 * Examples:
 *   [3,2,1,5,6,4],         k 2  -> 5
 *   [3,2,3,1,2,4,5,5,6],   k 4  -> 4
 *   [1],                   k 1  -> 1
 *   [2,1],                 k 2  -> 1
 *   [7,7,7,7],             k 3  -> 7
 *
 * Approaches:
 *   1. Sort                        O(n log n) time, O(1) extra
 *   2. Min-heap of size k  ⭐       O(n log k) time, O(k) space   <- go-to
 *   3. Quickselect (3-way)         O(n) average, O(n^2) worst, O(1) space
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
)

// ---------- Approach 1: Sort ----------
func findKthLargestSort(nums []int, k int) int {
	a := slices.Clone(nums)
	slices.Sort(a)
	return a[len(a)-k]
}

// ---------- Approach 2: Min-Heap of Size k ⭐ ----------
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *IntHeap) Push(x any)        { *h = append(*h, x.(int)) }
func (h *IntHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func findKthLargest(nums []int, k int) int {
	h := &IntHeap{}
	for _, x := range nums {
		heap.Push(h, x)
		if h.Len() > k {
			heap.Pop(h) // keep only the k largest
		}
	}
	return (*h)[0]
}

// ---------- Approach 3: Quickselect (3-Way Partition) ----------
func findKthLargestSelect(nums []int, k int) int {
	a := slices.Clone(nums)
	lo, hi, target := 0, len(a)-1, len(a)-k // index in ascending order
	for {
		pivot := a[lo+(hi-lo)/2]
		lt, i, gt := lo, lo, hi // [lo,lt) < pivot, [lt,i) == pivot, (gt,hi] > pivot
		for i <= gt {
			switch {
			case a[i] < pivot:
				a[lt], a[i] = a[i], a[lt]
				lt++
				i++
			case a[i] > pivot:
				a[i], a[gt] = a[gt], a[i]
				gt--
			default:
				i++
			}
		}
		switch {
		case target < lt:
			hi = lt - 1
		case target > gt:
			lo = gt + 1
		default:
			return pivot // target inside the == block
		}
	}
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums []int
		k    int
	}{
		{[]int{3, 2, 1, 5, 6, 4}, 2}, {[]int{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4}, {[]int{1}, 1}, {[]int{2, 1}, 2}, {[]int{7, 7, 7, 7}, 3},
	}
	for _, t := range tests {
		fmt.Println("sort  :", findKthLargestSort(t.nums, t.k))
		fmt.Println("heap  :", findKthLargest(t.nums, t.k))
		fmt.Println("select:", findKthLargestSelect(t.nums, t.k))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Clone keeps the caller's slice untouched by the partitioning.
 * - A for with no condition plus returns inside acts as while(true).
 */
