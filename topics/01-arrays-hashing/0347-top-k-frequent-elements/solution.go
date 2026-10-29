/*
 * 0347. Top K Frequent Elements  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/top-k-frequent-elements/
 *
 * Problem: Return the k most frequent values (any order; answer is unique).
 *
 * Examples (printed sorted for stable output):
 *   [1,1,1,2,2,3], k=2             -> [1,2]
 *   [1], k=1                       -> [1]
 *   [1,2,1,2,1,2,3,1,3,2], k=2     -> [1,2]
 *   [4,4,-1,-1,-1,7], k=1          -> [-1]
 *
 * Approaches:
 *   1. Sort by frequency     O(n log n) time, O(n) space
 *   2. Min-heap of size k    O(n log k) time, O(n) space
 *   3. Bucket sort  ⭐        O(n) time, O(n) space   <- go-to
 */

package main

import (
	"container/heap"
	"fmt"
	"slices"
)

func counts(nums []int) map[int]int {
	cnt := make(map[int]int)
	for _, x := range nums {
		cnt[x]++
	}
	return cnt
}

// ---------- Approach 1: Sort by Frequency ----------
func topKFrequentSorted(nums []int, k int) []int {
	cnt := counts(nums)
	vals := make([]int, 0, len(cnt))
	for v := range cnt {
		vals = append(vals, v)
	}
	slices.SortFunc(vals, func(a, b int) int { return cnt[b] - cnt[a] }) // descending by count
	return vals[:k]
}

// ---------- Approach 2: Min-Heap of Size k ----------
type item struct{ count, val int }
type minHeap []item

func (h minHeap) Len() int           { return len(h) }
func (h minHeap) Less(i, j int) bool { return h[i].count < h[j].count }
func (h minHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *minHeap) Push(x any)        { *h = append(*h, x.(item)) }
func (h *minHeap) Pop() any {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}

func topKFrequentHeap(nums []int, k int) []int {
	h := &minHeap{}
	for v, c := range counts(nums) {
		heap.Push(h, item{c, v})
		if h.Len() > k {
			heap.Pop(h) // evict the least frequent
		}
	}
	res := make([]int, 0, k)
	for _, it := range *h {
		res = append(res, it.val)
	}
	return res
}

// ---------- Approach 3: Bucket Sort ⭐ ----------
func topKFrequent(nums []int, k int) []int {
	buckets := make([][]int, len(nums)+1) // index = frequency, max n
	for v, c := range counts(nums) {
		buckets[c] = append(buckets[c], v)
	}
	res := make([]int, 0, k)
	for f := len(nums); f >= 1; f-- {
		for _, v := range buckets[f] {
			res = append(res, v)
			if len(res) == k {
				return res
			}
		}
	}
	return res
}

// ---------- Driver ----------
func sorted(v []int) []int {
	slices.Sort(v) // normalize: order is unspecified
	return v
}

func main() {
	tests := []struct {
		nums []int
		k    int
	}{
		{[]int{1, 1, 1, 2, 2, 3}, 2},
		{[]int{1}, 1},
		{[]int{1, 2, 1, 2, 1, 2, 3, 1, 3, 2}, 2},
		{[]int{4, 4, -1, -1, -1, 7}, 1},
	}
	for _, t := range tests {
		fmt.Println("sorted:", sorted(topKFrequentSorted(t.nums, t.k)))
		fmt.Println("heap  :", sorted(topKFrequentHeap(t.nums, t.k)))
		fmt.Println("bucket:", sorted(topKFrequent(t.nums, t.k)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - container/heap needs Len, Less, Swap (value receiver) and Push, Pop (pointer receiver).
 * - Use heap.Push/heap.Pop (package funcs), not h.Push/h.Pop directly.
 * - slices.SortFunc comparator returns negative/zero/positive, like cmp.Compare.
 * - make([][]int, n+1) gives n+1 nil slices; append to a nil slice is fine.
 */
