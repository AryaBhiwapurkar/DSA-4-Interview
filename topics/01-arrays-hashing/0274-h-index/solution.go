/*
 * 0274. H-Index  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/h-index/
 *
 * Problem: Return the largest h such that at least h papers have at least
 *          h citations each.
 *
 * Examples:
 *   [3,0,6,1,5]  -> 3
 *   [1,3,1]      -> 1
 *   [0,0]        -> 0
 *   [100]        -> 1
 *
 * Approaches:
 *   1. Try every h          O(n^2) time, O(1) space
 *   2. Sort descending      O(n log n) time, O(n) space (sorted copy)
 *   3. Counting buckets  ⭐  O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Try Every h ----------
func hIndexBrute(citations []int) int {
	for h := len(citations); h >= 0; h-- {
		cnt := 0
		for _, c := range citations {
			if c >= h {
				cnt++
			}
		}
		if cnt >= h {
			return h
		}
	}
	return 0
}

// ---------- Approach 2: Sort Descending ----------
func hIndexSorted(citations []int) int {
	c := slices.Clone(citations)
	slices.Sort(c)
	slices.Reverse(c) // descending
	h := 0
	for h < len(c) && c[h] >= h+1 { // (h+1)-th best paper has >= h+1 citations
		h++
	}
	return h
}

// ---------- Approach 3: Counting Buckets ⭐ ----------
func hIndex(citations []int) int {
	n := len(citations)
	bucket := make([]int, n+1)
	for _, c := range citations {
		bucket[min(c, n)]++ // h <= n, so cap at n
	}
	total := 0 // papers with >= h citations
	for h := n; h >= 0; h-- {
		total += bucket[h]
		if total >= h {
			return h
		}
	}
	return 0
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{3, 0, 6, 1, 5}, {1, 3, 1}, {0, 0}, {100}}
	for _, c := range tests {
		fmt.Println("brute :", hIndexBrute(c))
		fmt.Println("sorted:", hIndexSorted(c))
		fmt.Println("bucket:", hIndex(c))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Descending sort: slices.Sort then slices.Reverse (or SortFunc with b - a).
 * - min(a, b) is a built-in since Go 1.21.
 * - make([]int, n+1) is zero-filled, ready to use as counters.
 */
