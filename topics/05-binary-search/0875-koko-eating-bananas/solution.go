/*
 * 0875. Koko Eating Bananas  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/koko-eating-bananas/
 *
 * Problem: Each hour Koko eats up to k bananas from one pile. Return the
 *          minimum integer k to finish all piles within h hours.
 *
 * Examples:
 *   [3,6,7,11],       h 8   -> 4
 *   [30,11,23,4,20],  h 5   -> 30
 *   [30,11,23,4,20],  h 6   -> 23
 *   [5],              h 5   -> 1
 *   [1,1,1,1],        h 4   -> 1
 *
 * Approaches:
 *   1. Try every speed               O(n * max) time, O(1) space
 *   2. Binary search on speed  ⭐     O(n log max) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

func hoursAt(piles []int, k int) int {
	total := 0 // int is 64-bit: 1e13 at k = 1 fits
	for _, p := range piles {
		total += (p + k - 1) / k // ceil(p / k), exact
	}
	return total
}

// ---------- Approach 1: Try Every Speed ----------
func minEatingSpeedBrute(piles []int, h int) int {
	k := 1
	for hoursAt(piles, k) > h { // k = max(piles) always works
		k++
	}
	return k
}

// ---------- Approach 2: Binary Search on Speed ⭐ ----------
func minEatingSpeed(piles []int, h int) int {
	lo, hi := 1, slices.Max(piles) // lo = 1: never divide by 0
	for lo < hi {
		mid := lo + (hi-lo)/2
		if hoursAt(piles, mid) <= h {
			hi = mid // fast enough: try slower
		} else {
			lo = mid + 1
		}
	}
	return lo
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		piles []int
		h     int
	}{
		{[]int{3, 6, 7, 11}, 8}, {[]int{30, 11, 23, 4, 20}, 5}, {[]int{30, 11, 23, 4, 20}, 6},
		{[]int{5}, 5}, {[]int{1, 1, 1, 1}, 4},
	}
	for _, t := range tests {
		fmt.Println("brute :", minEatingSpeedBrute(t.piles, t.h))
		fmt.Println("binary:", minEatingSpeed(t.piles, t.h))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Max(s) (Go 1.21+) returns the largest element.
 * - sort.Search(n, pred) is the library form of "first k where pred is true":
 *   1 + sort.Search(max, func(i int) bool { return hoursAt(piles, i+1) <= h }).
 */
