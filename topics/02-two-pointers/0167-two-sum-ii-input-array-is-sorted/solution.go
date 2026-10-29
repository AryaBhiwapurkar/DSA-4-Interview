/*
 * 0167. Two Sum II - Input Array Is Sorted  |  Medium  |  Two Pointers
 * Link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * Problem: Sorted array, return 1-based indices [i, j] (i < j) of the two
 *          numbers summing to target. Exactly one answer; O(1) extra space.
 *
 * Examples:
 *   [2,7,11,15], target 9  -> [1 2]
 *   [2,3,4],     target 6  -> [1 3]
 *   [-1,0],      target -1 -> [1 2]
 *   [1,1,3],     target 2  -> [1 2]
 *
 * Approaches:
 *   1. Binary search per element   O(n log n) time, O(1) space
 *   2. Hashmap                     O(n) time, O(n) space
 *   3. Two pointers  ⭐             O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"sort"
)

// ---------- Approach 1: Binary Search per Element ----------
func twoSumBinary(a []int, target int) []int {
	for i, x := range a {
		rest := a[i+1:] // search only to the right of i
		j := sort.SearchInts(rest, target-x)
		if j < len(rest) && rest[j] == target-x {
			return []int{i + 1, i + 1 + j + 1}
		}
	}
	return nil
}

// ---------- Approach 2: Hashmap ----------
func twoSumHash(a []int, target int) []int {
	seen := make(map[int]int)
	for i, x := range a {
		if j, ok := seen[target-x]; ok {
			return []int{j + 1, i + 1}
		}
		seen[x] = i
	}
	return nil
}

// ---------- Approach 3: Two Pointers ⭐ ----------
func twoSum(a []int, target int) []int {
	l, r := 0, len(a)-1
	for l < r {
		sum := a[l] + a[r]
		switch {
		case sum == target:
			return []int{l + 1, r + 1} // 1-based
		case sum < target:
			l++ // a[l] is too small for every remaining partner
		default:
			r-- // a[r] is too big for every remaining partner
		}
	}
	return nil
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		a      []int
		target int
	}{
		{[]int{2, 7, 11, 15}, 9},
		{[]int{2, 3, 4}, 6},
		{[]int{-1, 0}, -1},
		{[]int{1, 1, 3}, 2},
	}
	for _, t := range tests {
		fmt.Println("binary  :", twoSumBinary(t.a, t.target))
		fmt.Println("hash    :", twoSumHash(t.a, t.target))
		fmt.Println("pointers:", twoSum(t.a, t.target))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - sort.SearchInts on a sub-slice returns an index relative to that sub-slice.
 * - A tagless switch reads cleanly for three-way comparisons.
 * - Returning nil for "no answer" prints as [].
 */
