/*
 * 0036. Valid Sudoku  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/valid-sudoku/
 *
 * Problem: Return true if the filled cells of a 9x9 board have no repeated
 *          digit in any row, column, or 3x3 box ('.' = empty).
 *
 * Examples (rows written as strings):
 *   LeetCode example 1                               -> true
 *   example 1 with top-left 5 changed to 8           -> false
 *   empty board                                      -> true
 *
 * Approaches:
 *   1. Three separate passes        O(81) time, O(9) space
 *   2. Single pass, 27 bitmasks  ⭐  O(81) time, O(27) space   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

// ---------- Approach 1: Three Separate Passes ----------
func isValidSudokuThreePass(b []string) bool {
	for i := 0; i < 9; i++ {
		var row, col, box [9]bool
		for j := 0; j < 9; j++ {
			cells := [3]byte{b[i][j], b[j][i], b[(i/3)*3+j/3][(i%3)*3+j%3]} // row i, column i, j-th cell of box i
			seen := [3]*[9]bool{&row, &col, &box}
			for t, ch := range cells {
				if ch == '.' {
					continue
				}
				if seen[t][ch-'1'] {
					return false
				}
				seen[t][ch-'1'] = true
			}
		}
	}
	return true
}

// ---------- Approach 2: Single Pass, 27 Bitmasks ⭐ ----------
func isValidSudoku(b []string) bool {
	var rows, cols, boxes [9]int // bit d set = digit d+1 seen
	for r := 0; r < 9; r++ {
		for c := 0; c < 9; c++ {
			if b[r][c] == '.' {
				continue
			}
			bit := 1 << (b[r][c] - '1')
			k := (r/3)*3 + c/3 // box index 0..8
			if rows[r]&bit != 0 || cols[c]&bit != 0 || boxes[k]&bit != 0 {
				return false
			}
			rows[r] |= bit
			cols[c] |= bit
			boxes[k] |= bit
		}
	}
	return true
}

// ---------- Driver ----------
func main() {
	valid := []string{
		"53..7....", "6..195...", ".98....6.",
		"8...6...3", "4..8.3..1", "7...2...6",
		".6....28.", "...419..5", "....8..79",
	}
	invalid := append([]string{"8" + valid[0][1:]}, valid[1:]...)
	empty := make([]string, 9)
	for i := range empty {
		empty[i] = strings.Repeat(".", 9)
	}
	for _, b := range [][]string{valid, invalid, empty} {
		fmt.Println("three pass :", isValidSudokuThreePass(b))
		fmt.Println("single pass:", isValidSudoku(b))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Bitmask set: mask&bit != 0 tests, mask |= bit adds. (& binds tighter than != in Go.)
 * - 1 << (ch - '1') shifts by a byte value; Go allows unsigned shift counts.
 * - append([]T{x}, rest...) prepends by building a new slice.
 * - strings.Repeat(".", 9) builds a repeated string.
 */
