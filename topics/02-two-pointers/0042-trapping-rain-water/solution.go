/*
 * 0042. Trapping Rain Water  |  Hard  |  Two Pointers
 * Link: https://leetcode.com/problems/trapping-rain-water/
 *
 * Problem: Given bar heights (width 1), return the total water trapped.
 *
 * Examples:
 *   [0,1,0,2,1,0,1,3,2,1,2,1]  -> 6
 *   [4,2,0,3,2,5]              -> 9
 *   [3,0,3]                    -> 3
 *   [1,2,3]                    -> 0
 *
 * Approaches:
 *   1. Brute force                O(n^2) time, O(1) space
 *   2. Prefix/suffix max arrays   O(n) time, O(n) space
 *   3. Monotonic stack            O(n) time, O(n) space
 *   4. Two pointers  ⭐            O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Brute Force ----------
func trapBrute(h []int) int {
	total := 0
	for i := range h {
		total += min(slices.Max(h[:i+1]), slices.Max(h[i:])) - h[i]
	}
	return total
}

// ---------- Approach 2: Prefix/Suffix Max Arrays ----------
func trapArrays(h []int) int {
	n := len(h)
	L, R := make([]int, n), make([]int, n)
	for i := 0; i < n; i++ {
		L[i] = h[i] // includes h[i]
		if i > 0 {
			L[i] = max(L[i], L[i-1])
		}
	}
	for i := n - 1; i >= 0; i-- {
		R[i] = h[i]
		if i < n-1 {
			R[i] = max(R[i], R[i+1])
		}
	}
	total := 0
	for i := range h {
		total += min(L[i], R[i]) - h[i]
	}
	return total
}

// ---------- Approach 3: Monotonic Stack ----------
func trapStack(h []int) int {
	var st []int // indices with decreasing heights
	total := 0
	for i, x := range h {
		for len(st) > 0 && x > h[st[len(st)-1]] {
			bottom := st[len(st)-1]
			st = st[:len(st)-1]
			if len(st) == 0 { // no left wall
				break
			}
			left := st[len(st)-1]
			total += (i - left - 1) * (min(h[left], x) - h[bottom]) // fill one horizontal layer
		}
		st = append(st, i)
	}
	return total
}

// ---------- Approach 4: Two Pointers ⭐ ----------
func trap(h []int) int {
	l, r := 0, len(h)-1
	leftMax, rightMax, total := 0, 0, 0
	for l < r {
		if h[l] < h[r] { // right side has a wall >= h[l]: left is the bottleneck
			leftMax = max(leftMax, h[l])
			total += leftMax - h[l]
			l++
		} else {
			rightMax = max(rightMax, h[r])
			total += rightMax - h[r]
			r--
		}
	}
	return total
}

// ---------- Driver ----------
func main() {
	tests := [][]int{{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, {4, 2, 0, 3, 2, 5}, {3, 0, 3}, {1, 2, 3}}
	for _, h := range tests {
		fmt.Println("brute   :", trapBrute(h))
		fmt.Println("arrays  :", trapArrays(h))
		fmt.Println("stack   :", trapStack(h))
		fmt.Println("pointers:", trap(h))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Max(s) returns the largest element (panics on empty).
 * - Slice as stack: push with append, peek st[len(st)-1], pop st = st[:len(st)-1].
 * - Multiple accumulators declared together: leftMax, rightMax, total := 0, 0, 0.
 */
