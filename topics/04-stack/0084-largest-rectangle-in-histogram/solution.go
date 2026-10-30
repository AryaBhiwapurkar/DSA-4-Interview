/*
 * 0084. Largest Rectangle in Histogram  |  Hard  |  Stack
 * Link: https://leetcode.com/problems/largest-rectangle-in-histogram/
 *
 * Problem: Bars of width 1 with given heights. Return the area of the
 *          largest rectangle that fits inside the histogram.
 *
 * Examples:
 *   [2,1,5,6,2,3]  -> 10
 *   [2,4]          -> 4
 *   [5]            -> 5
 *   [1,2,3,4,5]    -> 9
 *   [2,2,2]        -> 6
 *   [2,0,2]        -> 2
 *
 * Approaches:
 *   1. Brute force, running min     O(n^2) time, O(1) space
 *   2. Monotonic increasing stack ⭐ O(n) time, O(n) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force, Running Min ----------
func largestRectangleAreaBrute(h []int) int {
	best := 0
	for i := range h {
		mn := h[i]
		for j := i; j < len(h); j++ {
			mn = min(mn, h[j]) // shortest bar in [i, j] limits the height
			best = max(best, mn*(j-i+1))
		}
	}
	return best
}

// ---------- Approach 2: Monotonic Increasing Stack ⭐ ----------
func largestRectangleArea(h []int) int {
	best := 0
	st := []int{} // indices, heights increasing
	for i := 0; i <= len(h); i++ {
		cur := 0 // sentinel 0 flushes the stack at the end
		if i < len(h) {
			cur = h[i]
		}
		for len(st) > 0 && h[st[len(st)-1]] >= cur {
			height := h[st[len(st)-1]]
			st = st[:len(st)-1]
			left := -1 // previous smaller (NEW top)
			if len(st) > 0 {
				left = st[len(st)-1]
			}
			best = max(best, height*(i-left-1)) // i is the next smaller
		}
		st = append(st, i)
	}
	return best
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{2, 1, 5, 6, 2, 3}, {2, 4}, {5}, {1, 2, 3, 4, 5}, {2, 2, 2}, {2, 0, 2}}
	for _, h := range tests {
		fmt.Println("brute:", largestRectangleAreaBrute(h))
		fmt.Println("stack:", largestRectangleArea(h))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go has no ternary: set a default, then override in an if.
 * - Built-in min/max (Go 1.21+) work on any ordered type.
 * - Loop to i <= len(h) for the sentinel instead of appending to the input
 *   (append could write into the caller's backing array).
 */
