/*
 * 0200. Number of Islands  |  Medium  |  Graphs
 * Link: https://leetcode.com/problems/number-of-islands/
 *
 * Problem: Count groups of 4-connected '1' cells in a grid of '1'/'0'.
 *
 * Examples:
 *   11110/11010/11000/00000  -> 1
 *   11000/11000/00100/00011  -> 3
 *   0                        -> 0
 *   101/010/101              -> 5
 *
 * Approaches:
 *   1. DFS flood fill  ⭐   O(m*n) time, O(m*n) stack   <- go-to
 *   2. BFS flood fill       O(m*n) time, O(min(m,n)) queue typically
 *   3. Union-Find           O(m*n * alpha) time, O(m*n) space
 */

package main

import "fmt"

var dirs = [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

// ---------- Approach 1: DFS Flood Fill ⭐ ----------
func numIslands(g [][]byte) int {
	m, n := len(g), len(g[0])
	var sink func(r, c int)
	sink = func(r, c int) {
		if r < 0 || c < 0 || r >= m || c >= n || g[r][c] != '1' {
			return
		}
		g[r][c] = '0' // visited = sunk
		for _, d := range dirs {
			sink(r+d[0], c+d[1])
		}
	}
	count := 0
	for r := 0; r < m; r++ {
		for c := 0; c < n; c++ {
			if g[r][c] == '1' {
				count++
				sink(r, c)
			}
		}
	}
	return count
}

// ---------- Approach 2: BFS Flood Fill ----------
func numIslandsBFS(g [][]byte) int {
	m, n, count := len(g), len(g[0]), 0
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if g[i][j] != '1' {
				continue
			}
			count++
			g[i][j] = '0' // mark on push, not on pop
			q := [][2]int{{i, j}}
			for len(q) > 0 {
				r, c := q[0][0], q[0][1]
				q = q[1:]
				for _, d := range dirs {
					nr, nc := r+d[0], c+d[1]
					if nr >= 0 && nc >= 0 && nr < m && nc < n && g[nr][nc] == '1' {
						g[nr][nc] = '0'
						q = append(q, [2]int{nr, nc})
					}
				}
			}
		}
	}
	return count
}

// ---------- Approach 3: Union-Find ----------
type DSU struct{ parent, rank []int }

func newDSU(n int) *DSU {
	d := &DSU{make([]int, n), make([]int, n)}
	for i := range d.parent {
		d.parent[i] = i
	}
	return d
}

func (d *DSU) find(x int) int {
	if d.parent[x] != x {
		d.parent[x] = d.find(d.parent[x]) // path compression
	}
	return d.parent[x]
}

func (d *DSU) union(a, b int) bool {
	a, b = d.find(a), d.find(b)
	if a == b {
		return false
	}
	if d.rank[a] < d.rank[b] {
		a, b = b, a
	}
	d.parent[b] = a
	if d.rank[a] == d.rank[b] {
		d.rank[a]++
	}
	return true
}

func numIslandsUF(g [][]byte) int {
	m, n, count := len(g), len(g[0]), 0
	dsu := newDSU(m * n)
	for r := 0; r < m; r++ {
		for c := 0; c < n; c++ {
			if g[r][c] != '1' {
				continue
			}
			count++
			if r+1 < m && g[r+1][c] == '1' && dsu.union(r*n+c, (r+1)*n+c) {
				count--
			}
			if c+1 < n && g[r][c+1] == '1' && dsu.union(r*n+c, r*n+c+1) {
				count--
			}
		}
	}
	return count
}

// ---------- Driver ----------
func grid(rows []string) [][]byte {
	g := make([][]byte, len(rows))
	for i, s := range rows {
		g[i] = []byte(s)
	}
	return g
}

func main() {
	tests := [][]string{{"11110", "11010", "11000", "00000"}, {"11000", "11000", "00100", "00011"}, {"0"}, {"101", "010", "101"}}
	for _, rows := range tests {
		fmt.Println("dfs:", numIslands(grid(rows)))
		fmt.Println("bfs:", numIslandsBFS(grid(rows)))
		fmt.Println("uf :", numIslandsUF(grid(rows)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Methods on *DSU mutate the shared parent/rank slices.
 * - grid(rows) builds a fresh [][]byte per call, so sinking never leaks between approaches.
 * - Recursive closures need `var f func(...)` declared first.
 */
