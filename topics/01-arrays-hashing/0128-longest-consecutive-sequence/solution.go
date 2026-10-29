/*
 * 0128. Longest Consecutive Sequence  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/longest-consecutive-sequence/
 *
 * Problem: Return the length of the longest run of consecutive integers
 *          that can be formed from the array's values. O(n) required.
 *
 * Examples:
 *   [100,4,200,1,3,2]        -> 4
 *   [0,3,7,2,5,8,4,6,0,1]    -> 9
 *   [1,0,1,2]                -> 3
 *   []                       -> 0
 *
 * Approaches:
 *   1. Sort + scan                 O(n log n) time, O(n) space (sorted copy)
 *   2. Hash set, start-of-run  ⭐   O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Sort + Scan ----------
func longestConsecutiveSorted(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	s := slices.Clone(nums)
	slices.Sort(s)
	best, cur := 1, 1
	for i := 1; i < len(s); i++ {
		switch {
		case s[i] == s[i-1]: // duplicate: neither breaks nor extends
			continue
		case s[i] == s[i-1]+1:
			cur++
		default:
			cur = 1
		}
		best = max(best, cur)
	}
	return best
}

// ---------- Approach 2: Hash Set, Start-of-Run ⭐ ----------
func longestConsecutive(nums []int) int {
	set := make(map[int]bool, len(nums))
	for _, x := range nums {
		set[x] = true
	}
	best := 0
	for x := range set { // iterate the set: each value once
		if set[x-1] { // not a run start (missing key reads as false)
			continue
		}
		length := 1
		for set[x+length] {
			length++
		}
		best = max(best, length)
	}
	return best
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{100, 4, 200, 1, 3, 2}, {0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, {1, 0, 1, 2}, {}}
	for _, nums := range tests {
		fmt.Println("sorted:", longestConsecutiveSorted(nums))
		fmt.Println("set   :", longestConsecutive(nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - map[int]bool as a set: a missing key reads as false, so set[x] is the lookup.
 * - make(map[K]V, n) preallocates room for n entries.
 * - max(a, b) is a built-in since Go 1.21.
 * - `continue` inside a switch continues the enclosing for loop.
 */
