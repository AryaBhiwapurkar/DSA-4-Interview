/*
 * 0040. Combination Sum II  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/combination-sum-ii/
 *
 * Problem: Positive candidates (with duplicates), a target. Return every
 *          unique combination summing to target, each element used once.
 *
 * Examples:
 *   [10,1,2,7,6,1,5], 8  -> [[1 1 6] [1 2 5] [1 7] [2 6]]
 *   [2,5,2,1,2],      5  -> [[1 2 2] [5]]
 *   [2,2,2],          4  -> [[2 2]]
 *   [3],              1  -> []
 *
 * Approaches:
 *   1. All subsets + set           O(2^n * n log n) time, O(2^n * n) space
 *   2. Sort + skip duplicates  ⭐   O(2^n * n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: All Subsets + Set ----------
func combinationSum2Set(candidates []int, target int) [][]int {
	c := slices.Clone(candidates)
	slices.Sort(c)
	seen := map[string][]int{} // fmt key -> combination
	path := []int{}
	var gofn func(i, rem int)
	gofn = func(i, rem int) {
		if rem == 0 {
			seen[fmt.Sprint(path)] = slices.Clone(path) // path built in sorted order
			return
		}
		if i == len(c) || rem < 0 {
			return
		}
		path = append(path, c[i])
		gofn(i+1, rem-c[i])
		path = path[:len(path)-1]
		gofn(i+1, rem)
	}
	gofn(0, target)
	res := [][]int{}
	for _, v := range seen {
		res = append(res, v)
	}
	return res
}

// ---------- Approach 2: Sort + Skip Duplicates ⭐ ----------
func combinationSum2(candidates []int, target int) [][]int {
	c := slices.Clone(candidates)
	slices.Sort(c)
	res := [][]int{}
	path := []int{}
	var dfs func(start, rem int)
	dfs = func(start, rem int) {
		if rem == 0 {
			res = append(res, slices.Clone(path))
			return
		}
		for i := start; i < len(c); i++ {
			if i > start && c[i] == c[i-1] {
				continue // same value, same depth: already explored
			}
			if c[i] > rem {
				break
			}
			path = append(path, c[i])
			dfs(i+1, rem-c[i]) // i + 1: each element once
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
	}{{[]int{10, 1, 2, 7, 6, 1, 5}, 8}, {[]int{2, 5, 2, 1, 2}, 5}, {[]int{2, 2, 2}, 4}, {[]int{3}, 1}}
	for _, t := range tests {
		fmt.Println("set :", norm(combinationSum2Set(t.c, t.t)))
		fmt.Println("skip:", norm(combinationSum2(t.c, t.t)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Slices can't be map keys; fmt.Sprint(path) makes a string key instead.
 * - Map iteration order is random, so results are sorted before printing.
 */
