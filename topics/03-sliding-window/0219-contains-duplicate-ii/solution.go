/*
 * 0219. Contains Duplicate II  |  Easy  |  Sliding Window
 * Link: https://leetcode.com/problems/contains-duplicate-ii/
 *
 * Problem: Return true if two equal values sit at most k indices apart.
 *
 * Examples:
 *   [1,2,3,1], k=3        -> true
 *   [1,0,1,1], k=1        -> true
 *   [1,2,3,1,2,3], k=2    -> false
 *   [1,1], k=0            -> false
 *
 * Approaches:
 *   1. Brute force          O(n*k) time, O(1) space
 *   2. Last-seen hashmap    O(n) time, O(n) space
 *   3. Window set  ⭐        O(n) time, O(min(n,k)) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force ----------
func containsNearbyDuplicateBrute(nums []int, k int) bool {
	for i := range nums {
		for j := i + 1; j < len(nums) && j-i <= k; j++ {
			if nums[i] == nums[j] {
				return true
			}
		}
	}
	return false
}

// ---------- Approach 2: Last-Seen Hashmap ----------
func containsNearbyDuplicateMap(nums []int, k int) bool {
	last := make(map[int]int) // value -> most recent index
	for i, x := range nums {
		if j, ok := last[x]; ok && i-j <= k { // comma-ok: index 0 is valid
			return true
		}
		last[x] = i
	}
	return false
}

// ---------- Approach 3: Window Set ⭐ ----------
func containsNearbyDuplicate(nums []int, k int) bool {
	window := make(map[int]struct{}) // values at indices [i-k, i-1]
	for i, x := range nums {
		if _, ok := window[x]; ok {
			return true
		}
		window[x] = struct{}{}
		if len(window) > k {
			delete(window, nums[i-k]) // drop the value that leaves the window
		}
	}
	return false
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		nums []int
		k    int
	}{
		{[]int{1, 2, 3, 1}, 3},
		{[]int{1, 0, 1, 1}, 1},
		{[]int{1, 2, 3, 1, 2, 3}, 2},
		{[]int{1, 1}, 0},
	}
	for _, t := range tests {
		fmt.Println("brute :", containsNearbyDuplicateBrute(t.nums, t.k))
		fmt.Println("map   :", containsNearbyDuplicateMap(t.nums, t.k))
		fmt.Println("window:", containsNearbyDuplicate(t.nums, t.k))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - `if j, ok := m[x]; ok && cond` combines lookup and condition.
 * - delete(m, key) is a no-op if the key is missing.
 * - len(map) is O(1).
 */
