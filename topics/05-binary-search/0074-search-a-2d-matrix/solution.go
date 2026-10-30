/*
 * 0074. Search a 2D Matrix  |  Medium  |  Binary Search
 * Link: https://leetcode.com/problems/search-a-2d-matrix/
 *
 * Problem: Rows are sorted and each row starts after the previous row ends.
 *          Return whether target is in the matrix. O(log(m*n)).
 *
 * Examples:
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 3   -> true
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 13  -> false
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 60  -> true
 *   [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target 0   -> false
 *   [[1]], target 1                                     -> true
 *   [[1],[3]], target 3                                 -> true
 *
 * Approaches:
 *   1. Scan everything         O(m*n) time, O(1) space
 *   2. Staircase (top-right)   O(m+n) time, O(1) space
 *   3. Flat binary search  ⭐   O(log(m*n)) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Scan Everything ----------
func searchMatrixBrute(m [][]int, target int) bool {
	for _, row := range m {
		if slices.Contains(row, target) {
			return true
		}
	}
	return false
}

// ---------- Approach 2: Staircase From the Top-Right ----------
func searchMatrixStaircase(m [][]int, target int) bool {
	r, c := 0, len(m[0])-1
	for r < len(m) && c >= 0 {
		switch {
		case m[r][c] == target:
			return true
		case m[r][c] > target:
			c-- // everything below in this column is bigger too
		default:
			r++ // everything left in this row is smaller too
		}
	}
	return false
}

// ---------- Approach 3: Flat Binary Search ⭐ ----------
func searchMatrix(m [][]int, target int) bool {
	cols := len(m[0])
	lo, hi := 0, len(m)*cols-1
	for lo <= hi {
		mid := lo + (hi-lo)/2
		v := m[mid/cols][mid%cols] // divide by COLUMNS
		switch {
		case v == target:
			return true
		case v < target:
			lo = mid + 1
		default:
			hi = mid - 1
		}
	}
	return false
}

// ---------- Driver ----------
func main() {
	big := [][]int{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}
	tests := []struct {
		m      [][]int
		target int
	}{
		{big, 3}, {big, 13}, {big, 60}, {big, 0}, {[][]int{{1}}, 1}, {[][]int{{1}, {3}}, 3},
	}
	for _, t := range tests {
		fmt.Println("brute    :", searchMatrixBrute(t.m, t.target))
		fmt.Println("staircase:", searchMatrixStaircase(t.m, t.target))
		fmt.Println("flat     :", searchMatrix(t.m, t.target))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - slices.Contains(s, x) is a linear membership test (Go 1.21+).
 * - Flat index k -> m[k/cols][k%cols].
 * - [][]int{{1}, {3}} is a 2x1 matrix literal.
 */
