/*
 * 0209. Minimum Size Subarray Sum  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/minimum-size-subarray-sum/
 *
 * Problem: Positive integers; return the length of the shortest contiguous
 *          subarray with sum >= target, or 0 if none.
 *
 * Examples:
 *   target=7,  [2,3,1,2,4,3]       -> 2
 *   target=4,  [1,4,4]             -> 1
 *   target=11, [1,1,1,1,1,1,1,1]   -> 0
 *   target=15, [1,2,3,4,5]         -> 5
 *
 * Approaches:
 *   1. Brute force                    O(n^2) time, O(1) space
 *   2. Prefix sums + binary search    O(n log n) time, O(n) space
 *   3. Sliding window  ⭐              O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"math"
	"sort"
)

// ---------- Approach 1: Brute Force ----------
func minSubArrayLenBrute(target int, nums []int) int {
	best := math.MaxInt
	for i := range nums {
		sum := 0
		for j := i; j < len(nums); j++ {
			sum += nums[j]
			if sum >= target {
				best = min(best, j-i+1)
				break // longer windows from i can't be shorter
			}
		}
	}
	if best == math.MaxInt {
		return 0
	}
	return best
}

// ---------- Approach 2: Prefix Sums + Binary Search ----------
func minSubArrayLenBinary(target int, nums []int) int {
	n := len(nums)
	P := make([]int, n+1) // P[i] = sum of nums[:i], strictly increasing
	for i, x := range nums {
		P[i+1] = P[i] + x
	}
	best := math.MaxInt
	for i := 0; i < n; i++ {
		j := sort.SearchInts(P, P[i]+target) // first j with P[j] >= P[i] + target
		if j <= n {
			best = min(best, j-i)
		}
	}
	if best == math.MaxInt {
		return 0
	}
	return best
}

// ---------- Approach 3: Sliding Window ⭐ ----------
func minSubArrayLen(target int, nums []int) int {
	l, sum, best := 0, 0, math.MaxInt
	for r, x := range nums {
		sum += x
		for sum >= target { // valid: record, then try to shrink
			best = min(best, r-l+1)
			sum -= nums[l]
			l++
		}
	}
	if best == math.MaxInt {
		return 0
	}
	return best
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		target int
		nums   []int
	}{
		{7, []int{2, 3, 1, 2, 4, 3}},
		{4, []int{1, 4, 4}},
		{11, []int{1, 1, 1, 1, 1, 1, 1, 1}},
		{15, []int{1, 2, 3, 4, 5}},
	}
	for _, t := range tests {
		fmt.Println("brute :", minSubArrayLenBrute(t.target, t.nums))
		fmt.Println("binary:", minSubArrayLenBinary(t.target, t.nums))
		fmt.Println("window:", minSubArrayLen(t.target, t.nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - math.MaxInt is the platform int max; handy as an "infinity" sentinel.
 * - sort.SearchInts on the whole prefix array works because P is strictly
 *   increasing and P[i] + target > P[i], so the hit is always after i.
 * - Go has no while; `for cond {}` is the shrink loop.
 */
