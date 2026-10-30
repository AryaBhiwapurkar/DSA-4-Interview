/*
 * 0034. Find First and Last Position of Element in Sorted Array  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 *
 * Problem: Sorted array with duplicates. Return [first, last] index of
 *          target, or [-1,-1]. O(log n).
 *
 * Examples:
 *   [5,7,7,8,8,10], target 8  -> [3 4]
 *   [5,7,7,8,8,10], target 6  -> [-1 -1]
 *   [],             target 0  -> [-1 -1]
 *   [1],            target 1  -> [0 0]
 *   [2,2,2],        target 2  -> [0 2]
 *   [1,2,3],        target 4  -> [-1 -1]
 *
 * Approaches:
 *   1. Linear scan           O(n) time, O(1) space
 *   2. Two lower bounds  ⭐   O(log n) time, O(1) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Linear Scan ----------
func searchRangeLinear(nums []int, target int) []int {
	first, last := -1, -1
	for i, x := range nums {
		if x != target {
			continue
		}
		if first == -1 {
			first = i
		}
		last = i
	}
	return []int{first, last}
}

// ---------- Approach 2: Two Lower Bounds ⭐ ----------
func lowerBound(nums []int, x int) int { // first index with nums[i] >= x
	lo, hi := 0, len(nums)
	for lo < hi {
		mid := lo + (hi-lo)/2
		if nums[mid] < x {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

func searchRange(nums []int, target int) []int {
	first := lowerBound(nums, target)
	if first == len(nums) || nums[first] != target { // bounds check first
		return []int{-1, -1}
	}
	return []int{first, lowerBound(nums, target+1) - 1}
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums   []int
		target int
	}{
		{[]int{5, 7, 7, 8, 8, 10}, 8}, {[]int{5, 7, 7, 8, 8, 10}, 6}, {[]int{}, 0},
		{[]int{1}, 1}, {[]int{2, 2, 2}, 2}, {[]int{1, 2, 3}, 4},
	}
	for _, t := range tests {
		fmt.Println("linear:", searchRangeLinear(t.nums, t.target))
		fmt.Println("bounds:", searchRange(t.nums, t.target))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - sort.SearchInts(a, x) is lower bound; sort.SearchInts(a, x+1) - 1 is
 *   the last occurrence for ints.
 * - `||` short-circuits, so nums[first] is never read when first == len(nums).
 */
