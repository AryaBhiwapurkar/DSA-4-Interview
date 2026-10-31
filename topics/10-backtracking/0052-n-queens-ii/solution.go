/*
 * 0052. N-Queens II  |  Hard  |  Backtracking
 * Link: https://leetcode.com/problems/n-queens-ii/
 *
 * Problem: Count the placements of n non-attacking queens on an n x n board.
 *
 * Examples:
 *   n 4  -> 2
 *   n 1  -> 1
 *   n 2  -> 0
 *   n 3  -> 0
 *   n 8  -> 92
 *   n 9  -> 352
 *
 * Approaches:
 *   1. Backtracking + col/diag sets  ⭐   O(n!) time, O(n) space   <- go-to
 *   2. Bitmask backtracking              O(n!) time, O(n) space
 */

package main

import "fmt"

// ---------- Approach 1: Backtracking + Column/Diagonal Sets ⭐ ----------
func totalNQueens(n int) int {
	cols := make([]bool, n)
	diag := make([]bool, 2*n-1)
	anti := make([]bool, 2*n-1)
	var count func(r int) int
	count = func(r int) int {
		if r == n {
			return 1
		}
		total := 0
		for c := 0; c < n; c++ {
			d, a := r-c+n-1, r+c
			if cols[c] || diag[d] || anti[a] {
				continue
			}
			cols[c], diag[d], anti[a] = true, true, true
			total += count(r + 1)
			cols[c], diag[d], anti[a] = false, false, false
		}
		return total
	}
	return count(0)
}

// ---------- Approach 2: Bitmask Backtracking ----------
func totalNQueensBitmask(n int) int {
	full := 1<<n - 1
	var gofn func(cols, d1, d2 int) int
	gofn = func(cols, d1, d2 int) int {
		if cols == full {
			return 1
		}
		total := 0
		for avail := full &^ (cols | d1 | d2); avail != 0; {
			bit := avail & -avail // lowest free column
			avail -= bit
			total += gofn(cols|bit, (d1|bit)<<1&full, (d2|bit)>>1)
		}
		return total
	}
	return gofn(0, 0, 0)
}

// ---------- Driver ----------
func main() {
	for _, n := range []int{4, 1, 2, 3, 8, 9} {
		fmt.Println("sets   :", totalNQueens(n))
		fmt.Println("bitmask:", totalNQueensBitmask(n))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - &^ is AND NOT (bit clear): full &^ x keeps the bits of full not in x.
 * - Shift binds tighter than -: 1<<n - 1 is (1<<n) - 1.
 * - Go has no implicit int->bool; loop on `avail != 0`.
 */
