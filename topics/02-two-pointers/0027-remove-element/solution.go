/*
 * 0027. Remove Element  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/remove-element/
 *
 * Problem: Remove all occurrences of val in place; return k, the count
 *          of remaining elements, which must fill the first k slots
 *          (any order).
 *
 * Examples (k, then first k elements sorted):
 *   [3,2,2,3], val=3            -> 2, [2,2]
 *   [0,1,2,2,3,0,4,2], val=2    -> 5, [0,0,1,3,4]
 *   [], val=1                   -> 0, []
 *   [4,4], val=4                -> 0, []
 *
 * Approaches:
 *   1. Read/write pointers  ⭐   O(n) time, O(1) space   <- go-to
 *   2. Swap with end            O(n) time, O(1) space
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Read/Write Pointers ⭐ ----------
func removeElement(nums []int, val int) int {
	k := 0
	for _, x := range nums {
		if x != val {
			nums[k] = x
			k++
		}
	}
	return k
}

// ---------- Approach 2: Swap With End ----------
func removeElementSwap(nums []int, val int) int {
	i, n := 0, len(nums)
	for i < n {
		if nums[i] == val {
			n--
			nums[i] = nums[n] // don't advance i: the moved-in value is unchecked
		} else {
			i++
		}
	}
	return n
}

// ---------- Driver ----------
func show(label string, nums []int, val int, fn func([]int, int) int) {
	nums = slices.Clone(nums)
	k := fn(nums, val)
	slices.Sort(nums[:k]) // normalize: any order is accepted
	fmt.Printf("%s: %d, %v\n", label, k, nums[:k])
}

func main() {
	tests := []struct {
		nums []int
		val  int
	}{
		{[]int{3, 2, 2, 3}, 3},
		{[]int{0, 1, 2, 2, 3, 0, 4, 2}, 2},
		{[]int{}, 1},
		{[]int{4, 4}, 4},
	}
	for _, t := range tests {
		show("read/write", t.nums, t.val, removeElement)
		show("swap end  ", t.nums, t.val, removeElementSwap)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - range copies each element into x; writing nums[k] (k <= index) is safe.
 * - slices.Sort(nums[:k]) sorts only the prefix, in place.
 * - Go has no --n expression; decrement as its own statement.
 */
