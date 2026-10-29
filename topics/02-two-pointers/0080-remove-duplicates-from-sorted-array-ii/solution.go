/*
 * 0080. Remove Duplicates from Sorted Array II  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
 *
 * Problem: In a sorted array, keep each value at most twice (in order),
 *          in place. Return k = length of the result.
 *
 * Examples (k, then first k elements):
 *   [1,1,1,2,2,3]          -> 5, [1,1,2,2,3]
 *   [0,0,1,1,1,1,2,3,3]    -> 7, [0,0,1,1,2,3,3]
 *   [1,1,1,2,2,2]          -> 4, [1,1,2,2]
 *   [5]                    -> 1, [5]
 *
 * Approaches:
 *   1. Run counter               O(n) time, O(1) space
 *   2. Compare with nums[k-2] ⭐  O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Run Counter ----------
func removeDuplicatesCounter(nums []int) int {
	k, run := 0, 0
	prev := 0
	for i, x := range nums { // range copies values up front per iteration
		if i > 0 && x == prev {
			run++
		} else {
			run = 1
		}
		prev = x // track input value separately: nums may be overwritten
		if run <= 2 {
			nums[k] = x
			k++
		}
	}
	return k
}

// ---------- Approach 2: Compare With nums[k-2] ⭐ ----------
func removeDuplicates(nums []int) int {
	k := min(len(nums), 2) // first two always stay
	for i := 2; i < len(nums); i++ {
		if nums[i] != nums[k-2] { // output already has two copies if equal
			nums[k] = nums[i]
			k++
		}
	}
	return k
}

// ---------- Driver ----------
func show(label string, nums []int, fn func([]int) int) {
	nums = slices.Clone(nums)
	k := fn(nums)
	fmt.Printf("%s: %d, %v\n", label, k, nums[:k])
}

func main() {
	tests := [][]int{{1, 1, 1, 2, 2, 3}, {0, 0, 1, 1, 1, 1, 2, 3, 3}, {1, 1, 1, 2, 2, 2}, {5}}
	for _, nums := range tests {
		show("counter", nums, removeDuplicatesCounter)
		show("k-2    ", nums, removeDuplicates)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - min(len(nums), 2) uses the Go 1.21 built-in.
 * - `for i, x := range nums` reads nums[i] at each step (writes to earlier slots are safe).
 * - Generalize: keep at most m copies by comparing with nums[k-m].
 */
