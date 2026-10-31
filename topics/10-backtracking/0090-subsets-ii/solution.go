/*
 * 0090. Subsets II  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/subsets-ii/
 *
 * Problem: Return all distinct subsets of an array that may contain duplicates.
 *
 * Examples:
 *   [1,2,2]      -> [[] [1] [1 2] [1 2 2] [2] [2 2]]
 *   [0]          -> [[] [0]]
 *   [4,4,4,1,4]  -> 10 subsets
 *
 * Approaches:
 *   1. Power set + set             O(n^2 * 2^n) time, O(n * 2^n) space
 *   2. Sort + skip duplicates  ⭐   O(n * 2^n) time, O(n) extra   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Power Set + Set ----------
func subsetsWithDupSet(nums []int) [][]int {
	a := slices.Clone(nums)
	slices.Sort(a) // equal subsets then look identical
	n := len(a)
	seen := map[string][]int{}
	for mask := 0; mask < 1<<n; mask++ {
		s := []int{}
		for j := 0; j < n; j++ {
			if mask>>j&1 == 1 {
				s = append(s, a[j])
			}
		}
		seen[fmt.Sprint(s)] = s
	}
	res := [][]int{}
	for _, s := range seen {
		res = append(res, s)
	}
	return res
}

// ---------- Approach 2: Sort + Skip Duplicates ⭐ ----------
func subsetsWithDup(nums []int) [][]int {
	a := slices.Clone(nums)
	slices.Sort(a)
	res := [][]int{}
	path := []int{}
	var dfs func(start int)
	dfs = func(start int) {
		res = append(res, slices.Clone(path))
		for i := start; i < len(a); i++ {
			if i > start && a[i] == a[i-1] {
				continue // same value at the same depth
			}
			path = append(path, a[i])
			dfs(i + 1)
			path = path[:len(path)-1]
		}
	}
	dfs(0)
	return res
}

// ---------- Driver ----------
func sorted(v [][]int) [][]int {
	slices.SortFunc(v, slices.Compare[[]int]) // any order is accepted
	return v
}

func main() {
	for _, nums := range [][]int{{1, 2, 2}, {0}, {4, 4, 4, 1, 4}} {
		fmt.Println("set :", sorted(subsetsWithDupSet(nums)))
		fmt.Println("skip:", sorted(subsetsWithDup(nums)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - fmt.Sprint(slice) gives a string key, since slices aren't comparable.
 * - slices.Clone before slices.Sort keeps the caller's input unchanged.
 */
