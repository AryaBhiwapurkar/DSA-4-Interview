/*
 * 0051. N-Queens  |  Hard  |  Backtracking
 * Link: https://leetcode.com/problems/n-queens/
 *
 * Problem: Return every placement of n non-attacking queens on an n x n
 *          board, as row strings of 'Q' and '.'.
 *
 * Examples:
 *   n 4  -> [[.Q.. ...Q Q... ..Q.] [..Q. Q... ...Q .Q..]]
 *   n 1  -> [[Q]]
 *   n 2  -> []
 *   n 3  -> []
 *   n 8  -> 92 solutions (count printed)
 *
 * Approaches:
 *   1. Backtracking + board scan      O(n! * n) time, O(n^2) space
 *   2. Backtracking + col/diag sets ⭐ O(n!) time, O(n) extra   <- go-to
 */

package main

import (
	"fmt"
	"slices"
	"strings"
)

func snapshot(b [][]byte) []string {
	rows := make([]string, len(b))
	for i, row := range b {
		rows[i] = string(row)
	}
	return rows
}

func emptyBoard(n int) [][]byte {
	b := make([][]byte, n)
	for i := range b {
		b[i] = []byte(strings.Repeat(".", n))
	}
	return b
}

// ---------- Approach 1: Backtracking + Board Scan ----------
func solveNQueensScan(n int) [][]string {
	b := emptyBoard(n)
	res := [][]string{}
	safe := func(r, c int) bool {
		for i := 0; i < r; i++ {
			dc := r - i // same row distance -> diagonal offsets
			if b[i][c] == 'Q' || (c-dc >= 0 && b[i][c-dc] == 'Q') || (c+dc < n && b[i][c+dc] == 'Q') {
				return false
			}
		}
		return true
	}
	var gofn func(r int)
	gofn = func(r int) {
		if r == n {
			res = append(res, snapshot(b))
			return
		}
		for c := 0; c < n; c++ {
			if safe(r, c) {
				b[r][c] = 'Q'
				gofn(r + 1)
				b[r][c] = '.'
			}
		}
	}
	gofn(0)
	return res
}

// ---------- Approach 2: Backtracking + Column/Diagonal Sets ⭐ ----------
func solveNQueens(n int) [][]string {
	b := emptyBoard(n)
	cols := make([]bool, n)
	diag := make([]bool, 2*n-1) // r - c + n - 1, constant along "\"
	anti := make([]bool, 2*n-1) // r + c, constant along "/"
	res := [][]string{}
	var place func(r int)
	place = func(r int) {
		if r == n {
			res = append(res, snapshot(b))
			return
		}
		for c := 0; c < n; c++ {
			d, a := r-c+n-1, r+c
			if cols[c] || diag[d] || anti[a] {
				continue
			}
			cols[c], diag[d], anti[a] = true, true, true
			b[r][c] = 'Q'
			place(r + 1)
			b[r][c] = '.'
			cols[c], diag[d], anti[a] = false, false, false
		}
	}
	place(0)
	return res
}

// ---------- Driver ----------
func sorted(v [][]string) [][]string {
	slices.SortFunc(v, slices.Compare[[]string]) // any order is accepted
	return v
}

func main() {
	for _, n := range []int{4, 1, 2, 3} {
		fmt.Println("scan:", sorted(solveNQueensScan(n)))
		fmt.Println("sets:", sorted(solveNQueens(n)))
		fmt.Println("---")
	}
	fmt.Println("scan n=8 count:", len(solveNQueensScan(8)))
	fmt.Println("sets n=8 count:", len(solveNQueens(8)))
}

/*
 * Syntax notes (Go):
 * - Strings are immutable: keep rows as []byte, convert with string(row) when saving.
 * - strings.Repeat(".", n) builds a row of dots.
 * - Tuple assignment sets three flags at once: a, b, c = true, true, true.
 */
