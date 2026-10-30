/*
 * 0035. Search Insert Position  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/search-insert-position/
 *
 * Problem: Sorted distinct ints. Return target's index, or the index where
 *          it would be inserted to keep order. O(log n).
 *
 * Examples:
 *   [1,3,5,6], target 5  -> 2
 *   [1,3,5,6], target 2  -> 1
 *   [1,3,5,6], target 7  -> 4
 *   [1,3,5,6], target 0  -> 0
 *   [1],       target 1  -> 0
 *
 * Approaches:
 *   1. Linear scan       O(n) time, O(1) space
 *   2. Lower bound  ⭐    O(log n) time, O(1) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Linear Scan ----------
func searchInsertLinear(nums []int, target int) int {
	for i, x := range nums {
		if x >= target {
			return i
		}
	}
	return len(nums)
}

// ---------- Approach 2: Lower Bound ⭐ ----------
func searchInsert(nums []int, target int) int {
	lo, hi := 0, len(nums) // half-open [lo, hi): answer can be n
	for lo < hi {
		mid := lo + (hi-lo)/2
		if nums[mid] < target {
			lo = mid + 1
		} else {
			hi = mid // mid might be the answer: keep it
		}
	}
	return lo
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums   []int
		target int
	}{
		{[]int{1, 3, 5, 6}, 5}, {[]int{1, 3, 5, 6}, 2}, {[]int{1, 3, 5, 6}, 7}, {[]int{1, 3, 5, 6}, 0}, {[]int{1}, 1},
	}
	for _, t := range tests {
		fmt.Println("linear:", searchInsertLinear(t.nums, t.target))
		fmt.Println("lower :", searchInsert(t.nums, t.target))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Library one-liner: sort.SearchInts(nums, target).
 * - sort.Search(n, func(i int) bool { return nums[i] >= target }) is the
 *   general form: first i where the predicate becomes true.
 */
