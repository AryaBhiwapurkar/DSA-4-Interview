/*
 * 0130. Surrounded Regions  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/surrounded-regions/
 *
 * Problem: Flip every 'O' region that doesn't touch the grid border to 'X',
 *          in place.
 *
 * Examples:
 *   XXXX/XOOX/XXOX/XOXX  -> XXXX/XXXX/XXXX/XOXX
 *   X                    -> X
 *   OO/OO                -> OO/OO (all on the border)
 *   XXX/XOX/XXX          -> XXX/XXX/XXX
 *
 * Approaches:
 *   1. BFS per region            O(m*n) time, O(m*n) space
 *   2. DFS from border  ⭐        O(m*n) time, O(m*n) stack   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

var dirs = [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

// ---------- Approach 1: BFS per Region ----------
func solveBFS(b [][]byte) {
	m, n := len(b), len(b[0])
	seen := make([][]bool, m)
	for i := range seen {
		seen[i] = make([]bool, n)
	}
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if b[i][j] != 'O' || seen[i][j] {
				continue
			}
			region := [][2]int{}
			border := false
			q := [][2]int{{i, j}}
			seen[i][j] = true
			for len(q) > 0 {
				r, c := q[0][0], q[0][1]
				q = q[1:]
				region = append(region, [2]int{r, c})
				if r == 0 || c == 0 || r == m-1 || c == n-1 {
					border = true
				}
				for _, d := range dirs {
					nr, nc := r+d[0], c+d[1]
					if nr < 0 || nc < 0 || nr >= m || nc >= n || seen[nr][nc] || b[nr][nc] != 'O' {
						continue
					}
					seen[nr][nc] = true
					q = append(q, [2]int{nr, nc})
				}
			}
			if !border {
				for _, p := range region {
					b[p[0]][p[1]] = 'X'
				}
			}
		}
	}
}

// ---------- Approach 2: DFS from the Border ⭐ ----------
func solve(b [][]byte) {
	m, n := len(b), len(b[0])
	var markSafe func(r, c int)
	markSafe = func(r, c int) {
		if r < 0 || c < 0 || r >= m || c >= n || b[r][c] != 'O' {
			return
		}
		b[r][c] = 'T' // connected to the border: safe
		for _, d := range dirs {
			markSafe(r+d[0], c+d[1])
		}
	}
	for i := 0; i < m; i++ {
		markSafe(i, 0)
		markSafe(i, n-1)
	}
	for j := 0; j < n; j++ {
		markSafe(0, j)
		markSafe(m-1, j)
	}
	for _, row := range b {
		for j, ch := range row {
			if ch == 'O' {
				row[j] = 'X' // enclosed
			} else if ch == 'T' {
				row[j] = 'O' // restore safe cells
			}
		}
	}
}

// ---------- Driver ----------
func grid(rows []string) [][]byte {
	g := make([][]byte, len(rows))
	for i, s := range rows {
		g[i] = []byte(s)
	}
	return g
}

func show(g [][]byte) string {
	rows := make([]string, len(g))
	for i, row := range g {
		rows[i] = strings.Join(strings.Split(string(row), ""), " ")
	}
	return "[[" + strings.Join(rows, "] [") + "]]"
}

func main() {
	tests := [][]string{{"XXXX", "XOOX", "XXOX", "XOXX"}, {"X"}, {"OO", "OO"}, {"XXX", "XOX", "XXX"}}
	for _, rows := range tests {
		a, b := grid(rows), grid(rows)
		solveBFS(a)
		solve(b)
		fmt.Println("bfs   :", show(a))
		fmt.Println("border:", show(b))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Ranging over row ([]byte) gives copies; write back through row[j].
 * - A slice used as a queue: read q[0], then q = q[1:].
 * - [2]int is a handy comparable coordinate type.
 */
