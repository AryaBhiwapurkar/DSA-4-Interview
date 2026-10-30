/*
 * 0287. Find the Duplicate Number  |  Medium  |  Linked List
 * Link: https://leetcode.com/problems/find-the-duplicate-number/
 *
 * Problem: n + 1 ints in [1, n]; exactly one value repeats. Find it
 *          without modifying the array, in O(1) extra space.
 *
 * Examples:
 *   [1,3,4,2,2]  -> 2
 *   [3,1,3,4,2]  -> 3
 *   [3,3,3,3,3]  -> 3
 *   [1,1]        -> 1
 *   [2,2,2]      -> 2
 *
 * Approaches:
 *   1. Hash set                     O(n) time, O(n) space
 *   2. Binary search on value       O(n log n) time, O(1) space
 *   3. Floyd cycle detection  ⭐     O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Hash Set ----------
func findDuplicateSet(nums []int) int {
	seen := map[int]bool{}
	for _, x := range nums {
		if seen[x] {
			return x
		}
		seen[x] = true
	}
	return -1
}

// ---------- Approach 2: Binary Search on Value ----------
func findDuplicateBinary(nums []int) int {
	lo, hi := 1, len(nums)-1 // values live in [1, n]
	for lo < hi {
		mid := lo + (hi-lo)/2
		cnt := 0
		for _, x := range nums {
			if x <= mid {
				cnt++
			}
		}
		if cnt > mid { // pigeonhole: too many values <= mid
			hi = mid
		} else {
			lo = mid + 1
		}
	}
	return lo
}

// ---------- Approach 3: Floyd Cycle Detection ⭐ ----------
func findDuplicate(nums []int) int {
	slow, fast := 0, 0 // index 0 is the head: no value points to it
	for {              // phase 1: meet inside the cycle
		slow = nums[slow]
		fast = nums[nums[fast]]
		if slow == fast {
			break
		}
	}
	slow = 0
	for slow != fast { // phase 2: meet at the cycle entry
		slow, fast = nums[slow], nums[fast]
	}
	return slow // entry has two incoming edges = duplicate
}

// ---------- Driver ----------
func main() {
	for _, nums := range [][]int{{1, 3, 4, 2, 2}, {3, 1, 3, 4, 2}, {3, 3, 3, 3, 3}, {1, 1}, {2, 2, 2}} {
		fmt.Println("hashSet:", findDuplicateSet(nums))
		fmt.Println("binary :", findDuplicateBinary(nums))
		fmt.Println("floyd  :", findDuplicate(nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go has no do-while: `for { ...; if cond { break } }`.
 * - map[int]bool reads false for missing keys, so `if seen[x]` is enough.
 */
