/*
 * 0189. Rotate Array  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/rotate-array/
 *
 * Problem: Rotate the array to the right by k steps, in place.
 *
 * Examples:
 *   [1,2,3,4,5,6,7], k=3   -> [5,6,7,1,2,3,4]
 *   [-1,-100,3,99], k=2    -> [3,99,-1,-100]
 *   [1,2], k=3             -> [2,1]
 *   [1,2,3], k=0           -> [1,2,3]
 *
 * Approaches:
 *   1. Rotate by one, k times   O(n*k) time, O(1) space
 *   2. Extra array              O(n) time, O(n) space
 *   3. Three reversals  ⭐       O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Rotate by One, k Times ----------
func rotateBrute(nums []int, k int) {
	n := len(nums)
	for step := 0; step < k%n; step++ {
		last := nums[n-1]
		copy(nums[1:], nums[:n-1]) // copy handles overlapping ranges like memmove
		nums[0] = last
	}
}

// ---------- Approach 2: Extra Array ----------
func rotateExtra(nums []int, k int) {
	n := len(nums)
	out := make([]int, n)
	for i, x := range nums {
		out[(i+k)%n] = x
	}
	copy(nums, out) // write back into the caller's backing array
}

// ---------- Approach 3: Three Reversals ⭐ ----------
func rotate(nums []int, k int) {
	k %= len(nums) // k may exceed n
	slices.Reverse(nums)
	slices.Reverse(nums[:k]) // first k: the old tail, fixed
	slices.Reverse(nums[k:]) // rest: the old head, fixed
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums []int
		k    int
	}{
		{[]int{1, 2, 3, 4, 5, 6, 7}, 3},
		{[]int{-1, -100, 3, 99}, 2},
		{[]int{1, 2}, 3},
		{[]int{1, 2, 3}, 0},
	}
	for _, t := range tests {
		a, b, c := slices.Clone(t.nums), slices.Clone(t.nums), slices.Clone(t.nums) // each approach mutates its own copy
		rotateBrute(a, t.k)
		rotateExtra(b, t.k)
		rotate(c, t.k)
		fmt.Println("brute  :", a)
		fmt.Println("extra  :", b)
		fmt.Println("reverse:", c)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A slice shares its backing array: modifying nums[i] in a function is visible to the caller.
 * - slices.Reverse(s[:k]) reverses just that sub-slice, in place.
 * - copy(dst, src) copies min(len) elements and is safe for overlapping slices.
 */
