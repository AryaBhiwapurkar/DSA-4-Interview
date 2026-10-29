/*
 * 0169. Majority Element  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/majority-element/
 *
 * Problem: Return the element that appears more than n/2 times.
 *          It is guaranteed to exist.
 *
 * Examples:
 *   [3,2,3]           -> 3
 *   [2,2,1,1,1,2,2]   -> 2
 *   [1,2,2]           -> 2
 *
 * Approaches:
 *   1. Hashmap count      O(n) time, O(n) space
 *   2. Sort, take middle  O(n log n) time, O(n) space (sorted copy)
 *   3. Boyer-Moore  ⭐     O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Hashmap Count ----------
func majorityElementHash(nums []int) int {
	cnt := make(map[int]int)
	for _, x := range nums {
		cnt[x]++ // missing key starts at zero value 0
		if cnt[x] > len(nums)/2 {
			return x
		}
	}
	return -1 // unreachable when a majority exists
}

// ---------- Approach 2: Sort, Take Middle ----------
func majorityElementSorted(nums []int) int {
	s := slices.Clone(nums)
	slices.Sort(s)
	return s[len(s)/2] // majority spans the middle index
}

// ---------- Approach 3: Boyer-Moore Voting ⭐ ----------
func majorityElement(nums []int) int {
	candidate, count := 0, 0
	for _, x := range nums {
		if count == 0 { // previous votes fully cancelled
			candidate = x
		}
		if x == candidate {
			count++
		} else {
			count--
		}
	}
	return candidate
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{3, 2, 3}, {2, 2, 1, 1, 1, 2, 2}, {1, 2, 2}}
	for _, nums := range tests {
		fmt.Println("hash  :", majorityElementHash(nums))
		fmt.Println("sorted:", majorityElementSorted(nums))
		fmt.Println("voting:", majorityElement(nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - m[k]++ works on a missing key: it starts from the zero value 0.
 * - No ternary operator in Go; use if/else.
 * - Integer division truncates toward zero: len/2 is the floor for len >= 0.
 */
