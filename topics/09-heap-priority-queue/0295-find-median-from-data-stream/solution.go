/*
 * 0295. Find Median from Data Stream  |  Hard  |  Heap / Priority Queue
 * Link: https://leetcode.com/problems/find-median-from-data-stream/
 *
 * Problem: addNum(num) and findMedian() over a stream of integers.
 *
 * Examples:
 *   add 1, add 2, median, add 3, median
 *     -> [null,null,null,1.50000,null,2.00000]
 *   add -1, median, add -2, median, add -3, median, add -4, median, add -5, median
 *     -> [null,null,-1.00000,null,-1.50000,null,-2.00000,null,-2.50000,null,-3.00000]
 *
 * Approaches:
 *   1. Sorted list with insertion   O(n) add, O(1) median, O(n) space
 *   2. Two heaps  ⭐                 O(log n) add, O(1) median, O(n) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
	"sort"
	"strings"
)

// ---------- Approach 1: Sorted List With Insertion ----------
type MedianFinderSorted struct{ a []int }

func (m *MedianFinderSorted) AddNum(x int) {
	m.a = slices.Insert(m.a, sort.SearchInts(m.a, x), x)
}

func (m *MedianFinderSorted) FindMedian() float64 {
	n := len(m.a)
	if n%2 == 1 {
		return float64(m.a[n/2])
	}
	return float64(m.a[n/2-1]+m.a[n/2]) / 2
}

// ---------- Approach 2: Two Heaps ⭐ ----------
type IntHeap []int // min-heap; the lower half stores negated values

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

type MedianFinder struct{ low, high *IntHeap } // low: negated max-heap, high: min-heap

func Constructor() MedianFinder { return MedianFinder{&IntHeap{}, &IntHeap{}} }

func (m *MedianFinder) AddNum(x int) {
	heap.Push(m.low, -x)                      // 1) into the lower half
	heap.Push(m.high, -heap.Pop(m.low).(int)) // 2) its max moves up
	if m.high.Len() > m.low.Len() {           // 3) rebalance: low keeps the extra one
		heap.Push(m.low, -heap.Pop(m.high).(int))
	}
}

func (m *MedianFinder) FindMedian() float64 {
	if m.low.Len() > m.high.Len() {
		return float64(-(*m.low)[0])
	}
	return float64(-(*m.low)[0]+(*m.high)[0]) / 2
}

// ---------- Driver ----------
type medianer interface {
	AddNum(int)
	FindMedian() float64
}

func run(m medianer, ops []string, args []int) string {
	out := []string{"null"}
	for i := 1; i < len(ops); i++ {
		if ops[i] == "addNum" {
			m.AddNum(args[i])
			out = append(out, "null")
		} else {
			out = append(out, fmt.Sprintf("%.5f", m.FindMedian()))
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct {
		ops  []string
		args []int
	}{
		{[]string{"MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"}, []int{0, 1, 2, 0, 3, 0}},
		{[]string{"MedianFinder", "addNum", "findMedian", "addNum", "findMedian", "addNum", "findMedian", "addNum",
			"findMedian", "addNum", "findMedian"}, []int{0, -1, 0, -2, 0, -3, 0, -4, 0, -5, 0}},
	}
	for _, t := range tests {
		mf := Constructor()
		fmt.Println("sorted:", run(&MedianFinderSorted{}, t.ops, t.args))
		fmt.Println("heaps :", run(&mf, t.ops, t.args))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - One min-heap type serves both halves: negate values for the max side.
 * - heap.Pop returns any: assert with .(int) before negating.
 */
