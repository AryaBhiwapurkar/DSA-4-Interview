/*
 * 0704. Binary Search  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/binary-search/
 *
 * Problem: Sorted array of distinct ints; return target's index or -1,
 *          in O(log n).
 *
 * Examples:
 *   [-1,0,3,5,9,12], target 9   -> 4
 *   [-1,0,3,5,9,12], target 2   -> -1
 *   [5],             target 5   -> 0
 *   [5],             target -5  -> -1
 *   [1,3],           target 3   -> 1
 *
 * Approaches:
 *   1. Linear scan            O(n) time, O(1) space
 *   2. Binary search  ⭐       O(log n) time, O(1) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Linear Scan ----------
func searchLinear(nums []int, target int) int {
	for i, x := range nums {
		if x == target {
			return i
		}
	}
	return -1
}

// ---------- Approach 2: Iterative Binary Search ⭐ ----------
func search(nums []int, target int) int {
	lo, hi := 0, len(nums)-1 // inclusive window
	for lo <= hi {           // <= : a 1-element window is still a candidate
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

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums   []int
		target int
	}{
		{[]int{-1, 0, 3, 5, 9, 12}, 9}, {[]int{-1, 0, 3, 5, 9, 12}, 2}, {[]int{5}, 5}, {[]int{5}, -5}, {[]int{1, 3}, 3},
	}
	for _, t := range tests {
		fmt.Println("linear:", searchLinear(t.nums, t.target))
		fmt.Println("binary:", search(t.nums, t.target))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - len() is a signed int, so hi = len-1 = -1 on empty input is safe.
 * - Library: sort.SearchInts(a, x) returns the first index with a[i] >= x;
 *   slices.BinarySearch(a, x) returns (index, found).
 */
