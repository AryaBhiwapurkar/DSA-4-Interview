/*
 * 0703. Kth Largest Element in a Stream  |  Easy  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/kth-largest-element-in-a-stream/
 *
 * Problem: KthLargest(k, nums); add(val) returns the k-th largest so far.
 *
 * Examples:
 *   k 3, [4,5,8,2]; add 3, 5, 10, 9, 4      -> [null,4,5,5,8,8]
 *   k 4, [7,7,7,7,8,3]; add 2, 10, 9, 9     -> [null,7,7,7,8]
 *   k 1, []; add -3, -2, -4                 -> [null,-3,-2,-2]
 *
 * Approaches:
 *   1. Sorted list with insertion   O(n) per add, O(n) space
 *   2. Min-heap of size k  ⭐        O(log k) per add, O(k) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
	"sort"
	"strconv"
	"strings"
)

// ---------- Approach 1: Sorted List With Insertion ----------
type KthLargestSorted struct {
	k int
	a []int // ascending
}

func newKthLargestSorted(k int, nums []int) *KthLargestSorted {
	a := slices.Clone(nums)
	slices.Sort(a)
	return &KthLargestSorted{k, a}
}

func (s *KthLargestSorted) Add(val int) int {
	i := sort.SearchInts(s.a, val)
	s.a = slices.Insert(s.a, i, val) // O(n) shift
	return s.a[len(s.a)-s.k]
}

// ---------- Approach 2: Min-Heap of Size k ⭐ ----------
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] } // min-heap
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *IntHeap) Push(x any)        { *h = append(*h, x.(int)) }
func (h *IntHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

type KthLargest struct {
	k int
	h *IntHeap // min-heap of the k largest
}

func Constructor(k int, nums []int) KthLargest {
	kl := KthLargest{k: k, h: &IntHeap{}}
	for _, x := range nums {
		kl.Add(x)
	}
	return kl
}

func (kl *KthLargest) Add(val int) int {
	heap.Push(kl.h, val)
	if kl.h.Len() > kl.k {
		heap.Pop(kl.h) // drop the smallest: it's not in the top k
	}
	return (*kl.h)[0] // smallest of the top k = k-th largest
}

// ---------- Driver ----------
type adder interface{ Add(int) int }

func run(a adder, adds []int) string {
	out := []string{"null"}
	for _, v := range adds {
		out = append(out, strconv.Itoa(a.Add(v)))
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct {
		k          int
		nums, adds []int
	}{
		{3, []int{4, 5, 8, 2}, []int{3, 5, 10, 9, 4}}, {4, []int{7, 7, 7, 7, 8, 3}, []int{2, 10, 9, 9}},
		{1, []int{}, []int{-3, -2, -4}},
	}
	for _, t := range tests {
		kl := Constructor(t.k, t.nums)
		fmt.Println("sorted:", run(newKthLargestSorted(t.k, t.nums), t.adds))
		fmt.Println("heap  :", run(&kl, t.adds))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - container/heap needs the five-method interface; (*h)[0] peeks the min.
 * - slices.Insert(s, i, v) inserts at index i (shifts the tail).
 * - Always call heap.Push/heap.Pop, not h.Push/h.Pop directly.
 */
