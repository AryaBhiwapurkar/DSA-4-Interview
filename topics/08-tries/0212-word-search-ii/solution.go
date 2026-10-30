/*
 * 0212. Word Search II  |  Hard  |  Tries
 * Link: https://leetcode.com/problems/word-search-ii/
 *
 * Problem: Return all words that can be traced on the board through
 *          horizontally/vertically adjacent cells, each cell used once per word.
 *
 * Examples (printed sorted):
 *   [[o,a,a,n],[e,t,a,e],[i,h,k,r],[i,f,l,v]], [oath,pea,eat,rain]  -> [eat oath]
 *   [[a,b],[c,d]], [abcb]                                          -> []
 *   [[a]], [a,b]                                                   -> [a]
 *   [[o,a,b,n],[o,t,a,e],[a,h,k,r],[a,f,l,v]], [oa,oaa]            -> [oa oaa]
 *
 * Approaches:
 *   1. Word search per word        O(W * m*n * 4*3^(L-1))
 *   2. Trie + backtracking  ⭐      O(m*n * 4*3^(L-1)) worst case   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

var dirs = [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

// ---------- Approach 1: Word Search Per Word ----------
func findWordsBrute(board [][]byte, words []string) []string {
	m, n := len(board), len(board[0])
	var exist func(w string, r, c, i int) bool
	exist = func(w string, r, c, i int) bool {
		if i == len(w) {
			return true
		}
		if r < 0 || c < 0 || r >= m || c >= n || board[r][c] != w[i] {
			return false
		}
		saved := board[r][c]
		board[r][c] = '#' // mark visited
		found := false
		for _, d := range dirs {
			if exist(w, r+d[0], c+d[1], i+1) {
				found = true
				break
			}
		}
		board[r][c] = saved // unmark on backtrack
		return found
	}
	res := []string{}
	for _, w := range words {
		found := false
		for r := 0; r < m && !found; r++ {
			for c := 0; c < n && !found; c++ {
				found = exist(w, r, c, 0)
			}
		}
		if found {
			res = append(res, w)
		}
	}
	return res
}

// ---------- Approach 2: Trie + Backtracking ⭐ ----------
type trieNode struct {
	next     [26]*trieNode
	word     string // non-empty at the end of a word
	children int    // for pruning empty branches
}

func findWords(board [][]byte, words []string) []string {
	root := &trieNode{}
	for _, w := range words {
		n := root
		for i := 0; i < len(w); i++ {
			c := w[i] - 'a'
			if n.next[c] == nil {
				n.next[c] = &trieNode{}
				n.children++
			}
			n = n.next[c]
		}
		n.word = w
	}
	m, cols := len(board), len(board[0])
	res := []string{}
	var dfs func(r, c int, parent *trieNode)
	dfs = func(r, c int, parent *trieNode) {
		ch := board[r][c]
		node := parent.next[ch-'a']
		if node.word != "" {
			res = append(res, node.word)
			node.word = "" // avoid duplicates
		}
		board[r][c] = '#'
		for _, d := range dirs {
			nr, nc := r+d[0], c+d[1]
			if nr < 0 || nc < 0 || nr >= m || nc >= cols {
				continue
			}
			nx := board[nr][nc]
			if nx != '#' && node.next[nx-'a'] != nil { // stay inside the trie
				dfs(nr, nc, node)
			}
		}
		board[r][c] = ch
		if node.children == 0 && node.word == "" { // prune a fully used branch
			parent.next[ch-'a'] = nil
			parent.children--
		}
	}
	for r := 0; r < m; r++ {
		for c := 0; c < cols; c++ {
			if root.next[board[r][c]-'a'] != nil {
				dfs(r, c, root)
			}
		}
	}
	return res
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
	tests := []struct{ rows, words []string }{
		{[]string{"oaan", "etae", "ihkr", "iflv"}, []string{"oath", "pea", "eat", "rain"}},
		{[]string{"ab", "cd"}, []string{"abcb"}},
		{[]string{"a"}, []string{"a", "b"}},
		{[]string{"oabn", "otae", "ahkr", "aflv"}, []string{"oa", "oaa"}},
	}
	for _, t := range tests {
		a, b := findWordsBrute(grid(t.rows), t.words), findWords(grid(t.rows), t.words)
		slices.Sort(a) // normalize: any order is accepted
		slices.Sort(b)
		fmt.Println("brute:", a)
		fmt.Println("trie :", b)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A [4][2]int array of directions drives the neighbour loop.
 * - []byte(s) copies a string into a mutable byte slice (one per board row).
 * - Package-level var for constant tables (Go has no const arrays).
 */
