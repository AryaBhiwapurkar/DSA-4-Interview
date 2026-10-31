/*
 * 0079. Word Search  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/word-search/
 *
 * Problem: Can `word` be traced on a letter grid through 4-adjacent
 *          cells, each cell used at most once?
 *
 * Examples (board B = ABCE / SFCS / ADEE):
 *   B, "ABCCED"  -> true
 *   B, "SEE"     -> true
 *   B, "ABCB"    -> false
 *   ["a"], "a"   -> true
 *   ["ab"], "ba" -> true
 *   ["aa"], "aaa" -> false (too long)
 *
 * Approaches:
 *   1. DFS + visited grid               O(m*n*3^L) time, O(m*n + L) space
 *   2. In-place mark + count prune  ⭐   O(m*n*3^L) time, O(L) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

var dirs = [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

// ---------- Approach 1: DFS + Visited Grid ----------
func existVisited(board [][]byte, word string) bool {
	m, n := len(board), len(board[0])
	vis := make([][]bool, m)
	for i := range vis {
		vis[i] = make([]bool, n)
	}
	var dfs func(r, c, i int) bool
	dfs = func(r, c, i int) bool {
		if r < 0 || c < 0 || r >= m || c >= n || vis[r][c] || board[r][c] != word[i] {
			return false
		}
		if i == len(word)-1 {
			return true
		}
		vis[r][c] = true
		defer func() { vis[r][c] = false }()
		for _, d := range dirs {
			if dfs(r+d[0], c+d[1], i+1) {
				return true
			}
		}
		return false
	}
	for r := 0; r < m; r++ {
		for c := 0; c < n; c++ {
			if dfs(r, c, 0) {
				return true
			}
		}
	}
	return false
}

// ---------- Approach 2: In-Place Mark + Count Prune ⭐ ----------
func exist(board [][]byte, word string) bool {
	m, n := len(board), len(board[0])
	if len(word) > m*n {
		return false
	}
	var have, need [128]int
	for _, row := range board {
		for _, ch := range row {
			have[ch]++
		}
	}
	for i := 0; i < len(word); i++ {
		need[word[i]]++
	}
	for ch := range need {
		if have[ch] < need[ch] {
			return false
		}
	}
	w := []byte(word)
	if have[w[len(w)-1]] < have[w[0]] {
		slices.Reverse(w) // start from the rarer end
	}
	var dfs func(r, c, i int) bool
	dfs = func(r, c, i int) bool {
		if r < 0 || c < 0 || r >= m || c >= n || board[r][c] != w[i] {
			return false
		}
		if i == len(w)-1 {
			return true
		}
		board[r][c] = '#' // on the path: can't be reused
		found := false
		for _, d := range dirs {
			if found = dfs(r+d[0], c+d[1], i+1); found {
				break
			}
		}
		board[r][c] = w[i] // unchoose
		return found
	}
	for r := 0; r < m; r++ {
		for c := 0; c < n; c++ {
			if dfs(r, c, 0) {
				return true
			}
		}
	}
	return false
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
	B := []string{"ABCE", "SFCS", "ADEE"}
	tests := []struct {
		rows []string
		word string
	}{{B, "ABCCED"}, {B, "SEE"}, {B, "ABCB"}, {[]string{"a"}, "a"}, {[]string{"ab"}, "ba"}, {[]string{"aa"}, "aaa"}}
	for _, t := range tests {
		fmt.Println("visited:", existVisited(grid(t.rows), t.word))
		fmt.Println("inplace:", exist(grid(t.rows), t.word))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A [128]int array indexed by byte is a cheap letter counter.
 * - defer runs the unmark when the closure returns, on every path.
 * - `if found = f(); found { break }` assigns and tests in one line.
 * - slices.Reverse works on the []byte copy of the word.
 */
