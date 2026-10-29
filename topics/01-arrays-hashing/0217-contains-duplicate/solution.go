/*
 * 0217. Contains Duplicate  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/contains-duplicate/
 *
 * Problem: Return true if any value appears at least twice in the
 *          array, false if all elements are distinct.
 *
 * Examples:
 *   [1,2,3,1]               -> true
 *   [1,2,3,4]               -> false
 *   [1,1,1,3,3,4,3,2,4,2]   -> true
 *   [7]                     -> false
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Sort + adjacent    O(n log n) time, O(n) space (sorted copy)
 *   3. Hash set  ⭐        O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Brute Force ----------
func containsDuplicateBrute(nums []int) bool {
	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ {
			if nums[i] == nums[j] {
				return true
			}
		}
	}
	return false
}

// ---------- Approach 2: Sort + Adjacent Check ----------
func containsDuplicateSorted(nums []int) bool {
	s := slices.Clone(nums) // slices share memory: sorting nums would mutate the caller's data
	slices.Sort(s)
	for i := 1; i < len(s); i++ {
		if s[i] == s[i-1] {
			return true
		}
	}
	return false
}

// ---------- Approach 3: Hash Set ⭐ ----------
func containsDuplicate(nums []int) bool {
	seen := make(map[int]struct{})
	for _, x := range nums {
		if _, ok := seen[x]; ok {
			return true
		}
		seen[x] = struct{}{}
	}
	return false
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{1, 2, 3, 1}, {1, 2, 3, 4}, {1, 1, 1, 3, 3, 4, 3, 2, 4, 2}, {7}}
	for _, nums := range tests {
		fmt.Println("brute :", containsDuplicateBrute(nums))
		fmt.Println("sorted:", containsDuplicateSorted(nums))
		fmt.Println("hash  :", containsDuplicate(nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Set idiom: map[T]struct{}; struct{}{} takes zero bytes.
 * - slices.Clone copies a slice; plain assignment shares the backing array.
 * - slices.Sort (Go 1.21+) sorts any ordered slice in place.
 * - `_, ok := m[k]` checks presence without using the value.
 */
