/*
 * 0039. Combination Sum  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/combination-sum/
 *
 * Problem: Distinct positive candidates, a target. Return every unique
 *          multiset of candidates (unlimited reuse) summing to target.
 *
 * Examples:
 *   [2,3,6,7], 7  -> [[2 2 3] [7]]
 *   [2,3,5],   8  -> [[2 2 2 2] [2 3 3] [3 5]]
 *   [2],       1  -> []
 *   [7,3,2],  18  -> 7 combinations (unsorted input)
 *
 * Approaches:
 *   1. Include / exclude                O(2^(n+T/m)) time, O(n+T/m) space
 *   2. Sorted loop from start  ⭐        O(n^(T/m+1)) time, O(T/m) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Include / Exclude ----------
func combinationSumBinary(candidates []int, target int) [][]int {
	res := [][]int{}
	path := []int{}
	var gofn func(i, rem int)
	gofn = func(i, rem int) {
		if rem == 0 {
			res = append(res, slices.Clone(path))
			return
		}
		if i == len(candidates) || rem < 0 {
			return
		}
		path = append(path, candidates[i])
		gofn(i, rem-candidates[i]) // use it again
		path = path[:len(path)-1]
		gofn(i+1, rem) // never use it again
	}
	gofn(0, target)
	return res
}

// ---------- Approach 2: Sorted Loop from Start Index ⭐ ----------
func combinationSum(candidates []int, target int) [][]int {
	c := slices.Clone(candidates)
	slices.Sort(c)
	res := [][]int{}
	path := []int{}
	var dfs func(start, rem int)
	dfs = func(start, rem int) {
		if rem == 0 {
			res = append(res, slices.Clone(path)) // copy: path's array is reused
			return
		}
		for i := start; i < len(c); i++ {
			if c[i] > rem {
				break // sorted: everything after is bigger too
			}
			path = append(path, c[i])
			dfs(i, rem-c[i]) // i, not i + 1: reuse allowed
			path = path[:len(path)-1]
		}
	}
	dfs(0, target)
	return res
}

// ---------- Driver ----------
func norm(v [][]int) [][]int {
	for _, x := range v {
		slices.Sort(x)
	}
	slices.SortFunc(v, slices.Compare[[]int]) // any order is accepted
	return v
}

func main() {
	tests := []struct {
		c []int
		t int
	}{{[]int{2, 3, 6, 7}, 7}, {[]int{2, 3, 5}, 8}, {[]int{2}, 1}, {[]int{7, 3, 2}, 18}}
	for _, t := range tests {
		fmt.Println("binary:", norm(combinationSumBinary(t.c, t.t)))
		fmt.Println("loop  :", norm(combinationSum(t.c, t.t)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Clone(path) snapshots the path; appending `path` itself would alias
 *   the backing array that later appends overwrite.
 * - slices.SortFunc(v, slices.Compare[[]int]) sorts slices lexicographically.
 * - `go` is a keyword, hence the helper name gofn.
 */
