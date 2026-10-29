/*
 * 0238. Product of Array Except Self  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/product-of-array-except-self/
 *
 * Problem: Return ans where ans[i] is the product of all elements except
 *          nums[i]. No division, O(n) time.
 *
 * Examples:
 *   [1,2,3,4]        -> [24,12,8,6]
 *   [-1,1,0,-3,3]    -> [0,0,9,0,0]
 *   [0,0,5]          -> [0,0,0]
 *
 * Approaches:
 *   1. Brute force                    O(n^2) time, O(1) extra space
 *   2. Prefix + suffix arrays         O(n) time, O(n) extra space
 *   3. Output + running suffix  ⭐     O(n) time, O(1) extra space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force ----------
func productExceptSelfBrute(nums []int) []int {
	n := len(nums)
	ans := make([]int, n)
	for i := range ans {
		ans[i] = 1
		for j := 0; j < n; j++ {
			if j != i {
				ans[i] *= nums[j]
			}
		}
	}
	return ans
}

// ---------- Approach 2: Prefix + Suffix Arrays ----------
func productExceptSelfArrays(nums []int) []int {
	n := len(nums)
	prefix, suffix, ans := make([]int, n), make([]int, n), make([]int, n)
	prefix[0], suffix[n-1] = 1, 1
	for i := 1; i < n; i++ {
		prefix[i] = prefix[i-1] * nums[i-1] // product left of i
	}
	for i := n - 2; i >= 0; i-- {
		suffix[i] = suffix[i+1] * nums[i+1] // product right of i
	}
	for i := range ans {
		ans[i] = prefix[i] * suffix[i]
	}
	return ans
}

// ---------- Approach 3: Output Array + Running Suffix ⭐ ----------
func productExceptSelf(nums []int) []int {
	n := len(nums)
	ans := make([]int, n)
	ans[0] = 1
	for i := 1; i < n; i++ {
		ans[i] = ans[i-1] * nums[i-1] // ans holds left products
	}
	suffix := 1
	for i := n - 1; i >= 0; i-- {
		ans[i] *= suffix // left * right
		suffix *= nums[i]
	}
	return ans
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{1, 2, 3, 4}, {-1, 1, 0, -3, 3}, {0, 0, 5}}
	for _, nums := range tests {
		fmt.Println("brute :", productExceptSelfBrute(nums))
		fmt.Println("arrays:", productExceptSelfArrays(nums))
		fmt.Println("suffix:", productExceptSelf(nums))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - make([]int, n) zero-fills; set the 1s you need explicitly.
 * - `for i := range ans` iterates indices only.
 * - Multiple assignment: prefix[0], suffix[n-1] = 1, 1.
 */
