/*
 * 0078. Subsets  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/subsets/
 *
 * Problem: Return the power set of an array of distinct integers.
 *
 * Examples:
 *   [1,2,3]  -> [[] [1] [2] [1 2] [3] [1 3] [2 3] [1 2 3]]
 *   [0]      -> [[] [0]]
 *   [5,-1]   -> [[] [5] [-1] [5 -1]]
 *
 * Approaches:
 *   1. Iterative doubling    O(n * 2^n) time, O(n * 2^n) space
 *   2. Bitmask               O(n * 2^n) time, O(n) extra
 *   3. Backtracking  ⭐       O(n * 2^n) time, O(n) extra   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Iterative Doubling ----------
func subsetsIter(nums []int) [][]int {
	res := [][]int{{}}
	for _, x := range nums {
		sz := len(res) // snapshot: res grows inside the loop
		for i := 0; i < sz; i++ {
			s := append(slices.Clone(res[i]), x) // clone first: res[i] may have spare capacity
			res = append(res, s)
		}
	}
	return res
}

// ---------- Approach 2: Bitmask ----------
func subsetsBitmask(nums []int) [][]int {
	n := len(nums)
	res := [][]int{}
	for mask := 0; mask < 1<<n; mask++ {
		s := []int{}
		for j := 0; j < n; j++ {
			if mask>>j&1 == 1 {
				s = append(s, nums[j])
			}
		}
		res = append(res, s)
	}
	return res
}

// ---------- Approach 3: Backtracking ⭐ ----------
func subsets(nums []int) [][]int {
	res := [][]int{}
	path := []int{}
	var dfs func(start int)
	dfs = func(start int) {
		res = append(res, slices.Clone(path)) // every node is a subset
		for i := start; i < len(nums); i++ {
			path = append(path, nums[i])
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
	for _, nums := range [][]int{{1, 2, 3}, {0}, {5, -1}} {
		fmt.Println("iter     :", sorted(subsetsIter(nums)))
		fmt.Println("bitmask  :", sorted(subsetsBitmask(nums)))
		fmt.Println("backtrack:", sorted(subsets(nums)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - append(res[i], x) can write into res[i]'s spare capacity and corrupt
 *   another subset; clone before appending.
 * - Go has no implicit int->bool: compare `mask>>j&1 == 1`.
 * - `1<<n` in a loop bound: shifts bind tighter than comparison.
 */
