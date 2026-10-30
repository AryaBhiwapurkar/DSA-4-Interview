/*
 * 0153. Find Minimum in Rotated Sorted Array  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 *
 * Problem: A sorted array of distinct ints was rotated. Return its minimum
 *          in O(log n).
 *
 * Examples:
 *   [3,4,5,1,2]      -> 1
 *   [4,5,6,7,0,1,2]  -> 0
 *   [11,13,15,17]    -> 11
 *   [2,1]            -> 1
 *   [1]              -> 1
 *
 * Approaches:
 *   1. Linear scan                   O(n) time, O(1) space
 *   2. Binary search vs right end ⭐  O(log n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Linear Scan ----------
func findMinLinear(nums []int) int {
	return slices.Min(nums)
}

// ---------- Approach 2: Binary Search vs Right End ⭐ ----------
func findMin(nums []int) int {
	lo, hi := 0, len(nums)-1
	for lo < hi {
		mid := lo + (hi-lo)/2
		if nums[mid] > nums[hi] {
			lo = mid + 1 // drop is strictly right of mid
		} else {
			hi = mid // mid..hi sorted: min at mid or left
		}
	}
	return nums[lo]
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{3, 4, 5, 1, 2}, {4, 5, 6, 7, 0, 1, 2}, {11, 13, 15, 17}, {2, 1}, {1}}
	for _, nums := range tests {
		fmt.Println("linear:", findMinLinear(nums))
		fmt.Println("binary:", findMin(nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Min (Go 1.21+) panics on an empty slice; n >= 1 here.
 * - The same lo < hi / hi = mid shape as lower bound.
 */
