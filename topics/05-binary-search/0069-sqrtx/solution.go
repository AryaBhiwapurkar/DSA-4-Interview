/*
 * 0069. Sqrt(x)  |  Easy  |  Binary Search
 * Link: https://leetcode.com/problems/sqrtx/
 *
 * Problem: Return floor(sqrt(x)) for 0 <= x <= 2^31 - 1 without sqrt/pow.
 *
 * Examples:
 *   4           -> 2
 *   8           -> 2
 *   0           -> 0
 *   1           -> 1
 *   2147395599  -> 46339
 *   2147483647  -> 46340
 *
 * Approaches:
 *   1. Linear scan                O(sqrt x) time, O(1) space
 *   2. Binary search on answer ⭐  O(log x) time, O(1) space   <- go-to
 *   3. Newton's method            O(log x) iterations, O(1) space
 */

package main

import "fmt"

// ---------- Approach 1: Linear Scan ----------
func mySqrtLinear(x int) int {
	k := 0
	for (k+1)*(k+1) <= x {
		k++
	}
	return k
}

// ---------- Approach 2: Binary Search on Answer ⭐ ----------
func mySqrt(x int) int {
	lo, hi, ans := 0, x, 0
	for lo <= hi {
		mid := lo + (hi-lo)/2
		if mid*mid <= x { // int is 64-bit: no overflow for x < 2^31
			ans = mid // mid works; try bigger
			lo = mid + 1
		} else {
			hi = mid - 1
		}
	}
	return ans
}

// ---------- Approach 3: Newton's Method ----------
func mySqrtNewton(x int) int {
	r := x
	for r*r > x {
		r = (r + x/r) / 2 // integer Newton step, decreases to the floor
	}
	return r
}

// ---------- Driver ----------
func main() {
	for _, x := range []int{4, 8, 0, 1, 2147395599, 2147483647} {
		fmt.Println("linear:", mySqrtLinear(x))
		fmt.Println("binary:", mySqrt(x))
		fmt.Println("newton:", mySqrtNewton(x))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - int is 64-bit on 64-bit platforms, so mid*mid fits for x < 2^31.
 *   With int32 inputs, convert first: int64(mid) * int64(mid).
 * - Integer division / truncates; no float involved.
 */
