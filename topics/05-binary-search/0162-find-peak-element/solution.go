/*
 * 0162. Find Peak Element  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/find-peak-element/
 *
 * Problem: Return the index of any element strictly greater than its
 *          neighbours (outside the array counts as -inf). O(log n).
 *
 * Examples (any peak is accepted; each approach's answer is checked):
 *   [1,2,3,1]        -> 2
 *   [1,2,1,3,5,6,4]  -> 1 or 5   (linear finds 1, binary finds 5)
 *   [1]              -> 0
 *   [3,2,1]          -> 0
 *   [1,2,3]          -> 2
 *
 * Approaches:
 *   1. Linear scan                 O(n) time, O(1) space
 *   2. Binary search on slope  ⭐   O(log n) time, O(1) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Linear Scan ----------
func findPeakElementLinear(nums []int) int {
	for i := 0; i+1 < len(nums); i++ {
		if nums[i] > nums[i+1] { // first downhill step: everything before rose
			return i
		}
	}
	return len(nums) - 1
}

// ---------- Approach 2: Binary Search on Slope ⭐ ----------
func findPeakElement(nums []int) int {
	lo, hi := 0, len(nums)-1
	for lo < hi { // lo < hi guarantees mid + 1 <= hi
		mid := lo + (hi-lo)/2
		if nums[mid] > nums[mid+1] {
			hi = mid // downhill: peak at mid or left
		} else {
			lo = mid + 1 // uphill: peak strictly right
		}
	}
	return lo
}

// ---------- Driver ----------
func isPeak(a []int, i int) bool {
	return (i == 0 || a[i] > a[i-1]) && (i == len(a)-1 || a[i] > a[i+1])
}

func main() {
	tests := [][]int{{1, 2, 3, 1}, {1, 2, 1, 3, 5, 6, 4}, {1}, {3, 2, 1}, {1, 2, 3}}
	for _, nums := range tests {
		a, b := findPeakElementLinear(nums), findPeakElement(nums)
		fmt.Printf("linear: %d peak=%t\n", a, isPeak(nums, a))
		fmt.Printf("binary: %d peak=%t\n", b, isPeak(nums, b))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - %t formats a bool in Printf; %d an int.
 * - `i+1 < len(nums)` is the safe loop bound for comparing neighbours.
 */
