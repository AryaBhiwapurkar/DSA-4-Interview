/*
 * 0131. Palindrome Partitioning  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/palindrome-partitioning/
 *
 * Problem: Return every way to split s into pieces that are all palindromes.
 *
 * Examples:
 *   "aab"  -> [[a a b] [aa b]]
 *   "a"    -> [[a]]
 *   "efe"  -> [[e f e] [efe]]
 *   "aaa"  -> [[a a a] [a aa] [aa a] [aaa]]
 *
 * Approaches:
 *   1. Backtracking + inline check  ⭐   O(n * 2^n) time, O(n) extra   <- go-to
 *   2. Backtracking + pal table         O(n * 2^n) time, O(n^2) space
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Backtracking + Inline Check ⭐ ----------
func isPal(s string, l, r int) bool {
	for l < r {
		if s[l] != s[r] {
			return false
		}
		l, r = l+1, r-1
	}
	return true
}

func partition(s string) [][]string {
	res := [][]string{}
	path := []string{}
	var dfs func(start int)
	dfs = func(start int) {
		if start == len(s) {
			res = append(res, slices.Clone(path))
			return
		}
		for end := start; end < len(s); end++ {
			if isPal(s, start, end) {
				path = append(path, s[start:end+1])
				dfs(end + 1)
				path = path[:len(path)-1]
			}
		}
	}
	dfs(0)
	return res
}

// ---------- Approach 2: Backtracking + Palindrome Table ----------
func partitionDP(s string) [][]string {
	n := len(s)
	pal := make([][]bool, n)
	for i := range pal {
		pal[i] = make([]bool, n)
	}
	for i := n - 1; i >= 0; i-- { // pal[i][j] needs pal[i+1][j-1]
		for j := i; j < n; j++ {
			pal[i][j] = s[i] == s[j] && (j-i < 2 || pal[i+1][j-1])
		}
	}
	res := [][]string{}
	path := []string{}
	var gofn func(start int)
	gofn = func(start int) {
		if start == n {
			res = append(res, slices.Clone(path))
			return
		}
		for end := start; end < n; end++ {
			if pal[start][end] {
				path = append(path, s[start:end+1])
				gofn(end + 1)
				path = path[:len(path)-1]
			}
		}
	}
	gofn(0)
	return res
}

// ---------- Driver ----------
func sorted(v [][]string) [][]string {
	slices.SortFunc(v, slices.Compare[[]string]) // any order is accepted
	return v
}

func main() {
	for _, s := range []string{"aab", "a", "efe", "aaa"} {
		fmt.Println("inline:", sorted(partition(s)))
		fmt.Println("table :", sorted(partitionDP(s)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - s[start:end+1] slices a string without copying (substrings share memory).
 * - slices.Compare works on []string too (lexicographic).
 */
