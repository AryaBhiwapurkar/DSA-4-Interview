/*
 * 0011. Container With Most Water  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/container-with-most-water/
 *
 * Problem: Choose two lines that, with the x-axis, hold the most water;
 *          area = min(h[l], h[r]) * (r - l). Return the max area.
 *
 * Examples:
 *   [1,8,6,2,5,4,8,3,7]  -> 49
 *   [1,1]                -> 1
 *   [4,3,2,1,4]          -> 16
 *   [0,0]                -> 0
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Two pointers  ⭐    O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force ----------
func maxAreaBrute(h []int) int {
	best := 0
	for i := 0; i < len(h); i++ {
		for j := i + 1; j < len(h); j++ {
			best = max(best, min(h[i], h[j])*(j-i))
		}
	}
	return best
}

// ---------- Approach 2: Two Pointers ⭐ ----------
func maxArea(h []int) int {
	l, r, best := 0, len(h)-1, 0
	for l < r {
		best = max(best, min(h[l], h[r])*(r-l))
		if h[l] < h[r] { // shorter wall is the bottleneck: only moving it can help
			l++
		} else {
			r--
		}
	}
	return best
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{1, 8, 6, 2, 5, 4, 8, 3, 7}, {1, 1}, {4, 3, 2, 1, 4}, {0, 0}}
	for _, h := range tests {
		fmt.Println("brute   :", maxAreaBrute(h))
		fmt.Println("pointers:", maxArea(h))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - min and max are built-ins (Go 1.21+) and take any number of ordered args.
 * - Triple assignment l, r, best := 0, len(h)-1, 0 declares all at once.
 */
