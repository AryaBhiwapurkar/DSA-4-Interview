/*
 * 0001. Two Sum  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/two-sum/
 *
 * Problem: Given an array and a target, return indices of the two
 *          numbers that add up to target. Exactly one answer exists;
 *          the same element can't be used twice.
 *
 * Examples:
 *   [2,7,11,15], target 9  -> [0 1]
 *   [3,2,4],     target 6  -> [1 2]
 *   [3,3],       target 6  -> [0 1]
 *   [-3,4,3,90], target 0  -> [0 2]
 *
 * Approaches:
 *   1. Brute force        O(n^2) time, O(1) space
 *   2. Sort + two ptrs    O(n log n) time, O(n) space
 *   3. Hashmap  ⭐         O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"sort"
)

// ---------- Approach 1: Brute Force ----------
func twoSumBrute(nums []int, target int) []int {
	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ { // j > i: never pair an element with itself
			if nums[i]+nums[j] == target {
				return []int{i, j}
			}
		}
	}
	return nil
}

// ---------- Approach 2: Sort + Two Pointers ----------
type pair struct{ val, idx int }

func twoSumSorted(nums []int, target int) []int {
	arr := make([]pair, len(nums)) // keep original indices
	for i, v := range nums {
		arr[i] = pair{v, i}
	}
	sort.Slice(arr, func(a, b int) bool { return arr[a].val < arr[b].val })

	l, r := 0, len(arr)-1
	for l < r {
		sum := arr[l].val + arr[r].val
		switch {
		case sum == target:
			a, b := arr[l].idx, arr[r].idx
			if a > b {
				a, b = b, a
			}
			return []int{a, b}
		case sum < target:
			l++
		default:
			r--
		}
	}
	return nil
}

// ---------- Approach 3: One-Pass Hashmap ⭐ ----------
func twoSum(nums []int, target int) []int {
	seen := make(map[int]int) // value -> index
	for i, num := range nums {
		if j, ok := seen[target-num]; ok {
			return []int{j, i}
		}
		seen[num] = i // insert AFTER checking: avoids self-match
	}
	return nil
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums   []int
		target int
	}{
		{[]int{2, 7, 11, 15}, 9},
		{[]int{3, 2, 4}, 6},
		{[]int{3, 3}, 6},
		{[]int{-3, 4, 3, 90}, 0},
	}
	for _, t := range tests {
		fmt.Println("brute :", twoSumBrute(t.nums, t.target))
		fmt.Println("sorted:", twoSumSorted(t.nums, t.target))
		fmt.Println("hash  :", twoSum(t.nums, t.target))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Comma-ok idiom: `v, ok := m[key]`. A missing key gives the zero value
 *   and ok=false, so always check ok (index 0 is a valid value!).
 * - `if x := ...; cond {}` scopes x to the if block.
 * - sort.Slice takes a less(i, j) closure over the slice.
 * - Anonymous struct slices are handy for test tables.
 * - int is 64-bit on most platforms, so overflow is rarely an issue here.
 */
