/*
 * 0046. Permutations  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/permutations/
 *
 * Problem: Return all orderings of an array of distinct integers.
 *
 * Examples:
 *   [1,2,3]  -> [[1 2 3] [1 3 2] [2 1 3] [2 3 1] [3 1 2] [3 2 1]]
 *   [0,1]    -> [[0 1] [1 0]]
 *   [1]      -> [[1]]
 *   [-1,5]   -> [[-1 5] [5 -1]]
 *
 * Approaches:
 *   1. Backtracking with used[]  ⭐  O(n * n!) time, O(n) extra space   <- go-to
 *   2. In-place swapping            O(n * n!) time, O(n) recursion
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Backtracking with used[] ⭐ ----------
func permute(nums []int) [][]int {
	res := [][]int{}
	path := []int{}
	used := make([]bool, len(nums))
	var dfs func()
	dfs = func() {
		if len(path) == len(nums) {
			res = append(res, slices.Clone(path))
			return
		}
		for i := range nums { // from 0: order matters
			if used[i] {
				continue
			}
			used[i] = true
			path = append(path, nums[i])
			dfs()
			path = path[:len(path)-1]
			used[i] = false
		}
	}
	dfs()
	return res
}

// ---------- Approach 2: In-Place Swapping ----------
func permuteSwap(nums []int) [][]int {
	a := slices.Clone(nums)
	res := [][]int{}
	var gofn func(i int)
	gofn = func(i int) {
		if i == len(a) {
			res = append(res, slices.Clone(a))
			return
		}
		for j := i; j < len(a); j++ {
			a[i], a[j] = a[j], a[i] // put a[j] in slot i
			gofn(i + 1)
			a[i], a[j] = a[j], a[i] // restore for the next j
		}
	}
	gofn(0)
	return res
}

// ---------- Driver ----------
func sorted(v [][]int) [][]int {
	slices.SortFunc(v, slices.Compare[[]int]) // any order of permutations is accepted
	return v
}

func main() {
	for _, nums := range [][]int{{1, 2, 3}, {0, 1}, {1}, {-1, 5}} {
		fmt.Println("used:", sorted(permute(nums)))
		fmt.Println("swap:", sorted(permuteSwap(nums)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - `for i := range nums` gives indices only.
 * - make([]bool, n) is all false; no explicit init needed.
 * - a[i], a[j] = a[j], a[i] is a parallel swap.
 */
