/*
 * 0004. Median of Two Sorted Arrays  |  Hard  |  Binary Search
 * Link: https://leetcode.com/problems/median-of-two-sorted-arrays/
 *
 * Problem: Return the median of two sorted arrays combined, in
 *          O(log(m + n)). One array may be empty.
 *
 * Examples:
 *   [1,3],   [2]       -> 2.00000
 *   [1,2],   [3,4]     -> 2.50000
 *   [],      [1]       -> 1.00000
 *   [2],     []        -> 2.00000
 *   [0,0],   [0,0]     -> 0.00000
 *   [1,3,5], [2,4,6]   -> 3.50000
 *   [1,2],   [-1,3]    -> 1.50000
 *
 * Approaches:
 *   1. Merge, pick middle            O(m+n) time, O(m+n) space
 *   2. Partition binary search  ⭐    O(log min(m,n)) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"math"
)

// ---------- Approach 1: Merge, Then Pick the Middle ----------
func findMedianSortedArraysMerge(a, b []int) float64 {
	m := make([]int, 0, len(a)+len(b))
	i, j := 0, 0
	for i < len(a) || j < len(b) {
		if j == len(b) || (i < len(a) && a[i] <= b[j]) {
			m = append(m, a[i])
			i++
		} else {
			m = append(m, b[j])
			j++
		}
	}
	n := len(m)
	if n%2 == 1 {
		return float64(m[n/2])
	}
	return float64(m[n/2-1]+m[n/2]) / 2
}

// ---------- Approach 2: Partition Binary Search ⭐ ----------
func findMedianSortedArrays(nums1, nums2 []int) float64 {
	A, B := nums1, nums2
	if len(A) > len(B) { // search the SHORTER one
		A, B = B, A
	}
	m, n := len(A), len(B)
	half := (m + n + 1) / 2 // left side gets the extra element when odd
	lo, hi := 0, m
	for lo <= hi {
		i := lo + (hi-lo)/2 // taken from A
		j := half - i       // taken from B
		aL, aR, bL, bR := math.MinInt, math.MaxInt, math.MinInt, math.MaxInt
		if i > 0 {
			aL = A[i-1]
		}
		if i < m {
			aR = A[i]
		}
		if j > 0 {
			bL = B[j-1]
		}
		if j < n {
			bR = B[j]
		}
		switch {
		case aL > bR:
			hi = i - 1 // too many from A
		case bL > aR:
			lo = i + 1 // too few from A
		case (m+n)%2 == 1:
			return float64(max(aL, bL))
		default:
			return float64(max(aL, bL)+min(aR, bR)) / 2
		}
	}
	return 0 // unreachable for sorted input
}

// ---------- Driver ----------
func main() {
	tests := [][2][]int{
		{{1, 3}, {2}}, {{1, 2}, {3, 4}}, {{}, {1}}, {{2}, {}}, {{0, 0}, {0, 0}}, {{1, 3, 5}, {2, 4, 6}}, {{1, 2}, {-1, 3}},
	}
	for _, t := range tests {
		fmt.Printf("merge    : %.5f\n", findMedianSortedArraysMerge(t[0], t[1]))
		fmt.Printf("partition: %.5f\n", findMedianSortedArrays(t[0], t[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - math.MinInt / math.MaxInt as -inf / +inf; the even-case sum only ever
 *   adds two real values, so no overflow.
 * - Swap two slices with A, B = B, A.
 * - [2][]int is a fixed-size array of two slices: handy for test pairs.
 * - %.5f formats a float64 with 5 decimals.
 */
