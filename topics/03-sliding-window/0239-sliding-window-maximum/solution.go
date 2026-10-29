/*
 * 0239. Sliding Window Maximum  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/sliding-window-maximum/
 *
 * Problem: Return the maximum of every window of size k as it slides
 *          from left to right.
 *
 * Examples:
 *   [1,3,-1,-3,5,3,6,7], k=3   -> [3,3,5,5,6,7]
 *   [1], k=1                   -> [1]
 *   [9,8,7,6], k=2             -> [9,8,7]
 *   [4,4,4], k=2               -> [4,4]
 *
 * Approaches:
 *   1. Brute force                   O(n*k) time, O(1) space
 *   2. Max-heap with lazy deletion   O(n log n) time, O(n) space
 *   3. Monotonic deque  ⭐            O(n) time, O(k) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
)

// ---------- Approach 1: Brute Force ----------
func maxSlidingWindowBrute(nums []int, k int) []int {
	var res []int
	for i := 0; i+k <= len(nums); i++ {
		res = append(res, slices.Max(nums[i:i+k]))
	}
	return res
}

// ---------- Approach 2: Max-Heap With Lazy Deletion ----------
type entry struct{ val, idx int }
type maxHeap []entry

func (h maxHeap) Len() int           { return len(h) }
func (h maxHeap) Less(i, j int) bool { return h[i].val > h[j].val }
func (h maxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *maxHeap) Push(x any)        { *h = append(*h, x.(entry)) }
func (h *maxHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func maxSlidingWindowHeap(nums []int, k int) []int {
	h := &maxHeap{}
	var res []int
	for i, x := range nums {
		heap.Push(h, entry{x, i})
		if i >= k-1 {
			for (*h)[0].idx <= i-k { // discard maxes that left the window
				heap.Pop(h)
			}
			res = append(res, (*h)[0].val)
		}
	}
	return res
}

// ---------- Approach 3: Monotonic Deque ⭐ ----------
func maxSlidingWindow(nums []int, k int) []int {
	dq := []int{} // indices; values strictly decreasing (slice used as a deque)
	var res []int
	for i, x := range nums {
		if len(dq) > 0 && dq[0] <= i-k { // front left the window
			dq = dq[1:]
		}
		for len(dq) > 0 && nums[dq[len(dq)-1]] <= x { // dominated: never a max again
			dq = dq[:len(dq)-1]
		}
		dq = append(dq, i)
		if i >= k-1 {
			res = append(res, nums[dq[0]])
		}
	}
	return res
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums []int
		k    int
	}{
		{[]int{1, 3, -1, -3, 5, 3, 6, 7}, 3},
		{[]int{1}, 1},
		{[]int{9, 8, 7, 6}, 2},
		{[]int{4, 4, 4}, 2},
	}
	for _, t := range tests {
		fmt.Println("brute:", maxSlidingWindowBrute(t.nums, t.k))
		fmt.Println("heap :", maxSlidingWindowHeap(t.nums, t.k))
		fmt.Println("deque:", maxSlidingWindow(t.nums, t.k))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Slice as deque: pop front with dq = dq[1:], pop back with dq = dq[:len(dq)-1].
 *   (Popping the front leaks the prefix until the next realloc; fine here.)
 * - (*h)[0] peeks the heap top without popping.
 * - slices.Max(s) returns the largest element of a non-empty slice.
 */
