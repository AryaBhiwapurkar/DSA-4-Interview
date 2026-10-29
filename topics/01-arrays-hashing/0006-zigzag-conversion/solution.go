/*
 * 0006. Zigzag Conversion  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/zigzag-conversion/
 *
 * Problem: Write s in a zigzag over numRows rows (down, then diagonally
 *          up, repeat) and return the rows read left to right.
 *
 * Examples:
 *   "PAYPALISHIRING", 3  -> "PAHNAPLSIIGYIR"
 *   "PAYPALISHIRING", 4  -> "PINALSIGYAHRPI"
 *   "A", 1               -> "A"
 *   "AB", 5              -> "AB"
 *
 * Approaches:
 *   1. Direct index math     O(n) time, O(n) output
 *   2. Row buckets  ⭐        O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

// ---------- Approach 1: Direct Index Math ----------
func convertMath(s string, numRows int) string {
	n := len(s)
	if numRows == 1 || numRows >= n {
		return s
	}
	cycle := 2 * (numRows - 1)
	var sb strings.Builder
	for r := 0; r < numRows; r++ {
		for k := r; k < n; k += cycle {
			sb.WriteByte(s[k])      // vertical column char
			diag := k + cycle - 2*r // diagonal char between columns
			if r != 0 && r != numRows-1 && diag < n {
				sb.WriteByte(s[diag])
			}
		}
	}
	return sb.String()
}

// ---------- Approach 2: Row Buckets ⭐ ----------
func convert(s string, numRows int) string {
	if numRows == 1 {
		return s // otherwise the bounce never moves
	}
	rows := make([]strings.Builder, min(numRows, len(s)))
	r, dir := 0, 1
	for i := 0; i < len(s); i++ {
		rows[r].WriteByte(s[i])
		if r == 0 {
			dir = 1
		} else if r == len(rows)-1 {
			dir = -1 // bounce at top and bottom
		}
		r += dir
	}
	var sb strings.Builder
	for i := range rows {
		sb.WriteString(rows[i].String())
	}
	return sb.String()
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		s string
		k int
	}{{"PAYPALISHIRING", 3}, {"PAYPALISHIRING", 4}, {"A", 1}, {"AB", 5}}
	for _, t := range tests {
		fmt.Println("math   :", convertMath(t.s, t.k))
		fmt.Println("buckets:", convert(t.s, t.k))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - make([]strings.Builder, k) gives k ready-to-use zero-value builders.
 * - Index builders by i (rows[i]); copying a used Builder value panics.
 * - min is a built-in since Go 1.21.
 */
