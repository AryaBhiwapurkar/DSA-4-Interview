/*
 * 0026. Remove Duplicates from Sorted Array  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 *
 * Problem: In a sorted array, keep one copy of each value at the front
 *          (in order), in place. Return k = number of unique values.
 *
 * Examples (k, then first k elements):
 *   [1,1,2]                 -> 2, [1,2]
 *   [0,0,1,1,1,2,2,3,3,4]   -> 5, [0,1,2,3,4]
 *   [7]                     -> 1, [7]
 *
 * Approaches:
 *   1. Collect uniques, copy back   O(n) time, O(n) space
 *   2. Read/write pointers  ⭐       O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Collect Uniques, Copy Back ----------
func removeDuplicatesCopy(nums []int) int {
	uniq := slices.Compact(slices.Clone(nums)) // Compact drops consecutive duplicates
	copy(nums, uniq)
	return len(uniq)
}

// ---------- Approach 2: Read/Write Pointers ⭐ ----------
func removeDuplicates(nums []int) int {
	k := 1 // nums[0] is always kept
	for i := 1; i < len(nums); i++ {
		if nums[i] != nums[k-1] { // compare with last WRITTEN value
			nums[k] = nums[i]
			k++
		}
	}
	return k
}

// ---------- Driver ----------
func show(label string, nums []int, fn func([]int) int) {
	nums = slices.Clone(nums) // don't mutate the shared test case
	k := fn(nums)
	fmt.Printf("%s: %d, %v\n", label, k, nums[:k])
}

func main() {
	tests := [][]int{{1, 1, 2}, {0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, {7}}
	for _, nums := range tests {
		show("copy      ", nums, removeDuplicatesCopy)
		show("read/write", nums, removeDuplicates)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Compact(s) removes consecutive duplicates in place and returns the shortened slice.
 * - func([]int) int is a function type; functions are first-class values.
 * - nums[:k] reslices without copying.
 */
