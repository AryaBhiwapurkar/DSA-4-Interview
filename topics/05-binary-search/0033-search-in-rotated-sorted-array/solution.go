/*
 * 0033. Search in Rotated Sorted Array  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/search-in-rotated-sorted-array/
 *
 * Problem: A sorted array of distinct ints was rotated. Return the index of
 *          target or -1, in O(log n).
 *
 * Examples:
 *   [4,5,6,7,0,1,2], target 0  -> 4
 *   [4,5,6,7,0,1,2], target 3  -> -1
 *   [1],             target 0  -> -1
 *   [1,3],           target 3  -> 1
 *   [3,1],           target 1  -> 1
 *   [5,1,3],         target 5  -> 0
 *
 * Approaches:
 *   1. Linear scan                  O(n) time, O(1) space
 *   2. Find pivot, then search      O(log n) time, O(1) space
 *   3. One-pass sorted half  ⭐      O(log n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Linear Scan ----------
func searchLinear(nums []int, target int) int {
	return slices.Index(nums, target) // -1 if absent
}

// ---------- Approach 2: Find Pivot, Then Binary Search ----------
func binarySearch(nums []int, lo, hi, target int) int {
	for lo <= hi {
		mid := lo + (hi-lo)/2
		switch {
		case nums[mid] == target:
			return mid
		case nums[mid] < target:
			lo = mid + 1
		default:
			hi = mid - 1
		}
	}
	return -1
}

func searchPivot(nums []int, target int) int {
	n := len(nums)
	lo, hi := 0, n-1
	for lo < hi { // index of the minimum (LC 0153)
		mid := lo + (hi-lo)/2
		if nums[mid] > nums[hi] {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	p := lo
	if target >= nums[p] && target <= nums[n-1] {
		return binarySearch(nums, p, n-1, target)
	}
	return binarySearch(nums, 0, p-1, target)
}

// ---------- Approach 3: One-Pass Sorted Half ⭐ ----------
func search(nums []int, target int) int {
	lo, hi := 0, len(nums)-1
	for lo <= hi {
		mid := lo + (hi-lo)/2
		if nums[mid] == target {
			return mid
		}
		if nums[lo] <= nums[mid] { // left half sorted (<=: lo may equal mid)
			if nums[lo] <= target && target < nums[mid] {
				hi = mid - 1
			} else {
				lo = mid + 1
			}
		} else { // right half sorted
			if nums[mid] < target && target <= nums[hi] {
				lo = mid + 1
			} else {
				hi = mid - 1
			}
		}
	}
	return -1
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums   []int
		target int
	}{
		{[]int{4, 5, 6, 7, 0, 1, 2}, 0}, {[]int{4, 5, 6, 7, 0, 1, 2}, 3}, {[]int{1}, 0},
		{[]int{1, 3}, 3}, {[]int{3, 1}, 1}, {[]int{5, 1, 3}, 5},
	}
	for _, t := range tests {
		fmt.Println("linear :", searchLinear(t.nums, t.target))
		fmt.Println("pivot  :", searchPivot(t.nums, t.target))
		fmt.Println("onePass:", search(t.nums, t.target))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Index(s, x) returns the first index of x, or -1.
 * - Go has no chained comparisons: write a <= x && x < b.
 * - Parameters of the same type can share it: (nums []int, lo, hi, target int).
 */
