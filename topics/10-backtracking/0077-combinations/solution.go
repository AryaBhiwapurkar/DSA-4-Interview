/*
 * 0077. Combinations  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/combinations/
 *
 * Problem: Return all ways to choose k numbers from 1..n.
 *
 * Examples:
 *   n 4, k 2  -> [[1 2] [1 3] [1 4] [2 3] [2 4] [3 4]]
 *   n 1, k 1  -> [[1]]
 *   n 3, k 3  -> [[1 2 3]]
 *   n 5, k 3  -> 10 combinations
 *
 * Approaches:
 *   1. Include / exclude                 O(2^n) time, O(n) space
 *   2. Start-index loop + prune  ⭐       O(k * C(n,k)) time, O(k) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Include / Exclude ----------
func combineBinary(n, k int) [][]int {
	res := [][]int{}
	path := []int{}
	var gofn func(x int)
	gofn = func(x int) {
		if len(path) == k {
			res = append(res, slices.Clone(path))
			return
		}
		if x > n {
			return
		}
		path = append(path, x)
		gofn(x + 1)
		path = path[:len(path)-1]
		gofn(x + 1)
	}
	gofn(1)
	return res
}

// ---------- Approach 2: Start-Index Loop + Prune ⭐ ----------
func combine(n, k int) [][]int {
	res := [][]int{}
	path := make([]int, 0, k)
	var dfs func(start int)
	dfs = func(start int) {
		if len(path) == k {
			res = append(res, slices.Clone(path))
			return
		}
		need := k - len(path)
		for i := start; i <= n-need+1; i++ { // enough numbers must remain
			path = append(path, i)
			dfs(i + 1)
			path = path[:len(path)-1]
		}
	}
	dfs(1)
	return res
}

// ---------- Driver ----------
func sorted(v [][]int) [][]int {
	slices.SortFunc(v, slices.Compare[[]int]) // any order is accepted
	return v
}

func main() {
	for _, t := range [][2]int{{4, 2}, {1, 1}, {3, 3}, {5, 3}} {
		fmt.Println("binary:", sorted(combineBinary(t[0], t[1])))
		fmt.Println("prune :", sorted(combine(t[0], t[1])))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - make([]int, 0, k) preallocates capacity so appends never reallocate.
 * - [][2]int{{4, 2}, ...} is a compact table of fixed-size pairs.
 */
