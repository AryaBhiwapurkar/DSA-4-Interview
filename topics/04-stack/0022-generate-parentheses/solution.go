/*
 * 0022. Generate Parentheses  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/generate-parentheses/
 *
 * Problem: Return every well-formed string of n pairs of parentheses.
 *
 * Examples (printed sorted):
 *   n = 3  -> [((())) (()()) (())() ()(()) ()()()]
 *   n = 1  -> [()]
 *   n = 2  -> [(()) ()()]
 *
 * Approaches:
 *   1. Generate all, filter      O(2^(2n) * n) time, O(n) depth
 *   2. Backtracking  ⭐           O(4^n / sqrt(n)) time, O(n) depth   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Generate All, Then Filter ----------
func balanced(s []byte) bool {
	bal := 0
	for _, c := range s {
		if c == '(' {
			bal++
		} else {
			bal--
		}
		if bal < 0 { // a ')' with nothing to close
			return false
		}
	}
	return bal == 0
}

func generateParenthesisBrute(n int) []string {
	res := []string{}
	cur := []byte{}
	var gen func()
	gen = func() {
		if len(cur) == 2*n {
			if balanced(cur) {
				res = append(res, string(cur))
			}
			return
		}
		for _, c := range []byte("()") {
			cur = append(cur, c)
			gen()
			cur = cur[:len(cur)-1]
		}
	}
	gen()
	return res
}

// ---------- Approach 2: Backtracking With Counts ⭐ ----------
func generateParenthesis(n int) []string {
	res := []string{}
	cur := make([]byte, 0, 2*n)
	var backtrack func(open, close int)
	backtrack = func(open, close int) {
		if len(cur) == 2*n {
			res = append(res, string(cur)) // string() copies: safe to keep mutating cur
			return
		}
		if open < n {
			cur = append(cur, '(')
			backtrack(open+1, close)
			cur = cur[:len(cur)-1]
		}
		if close < open { // NOT close < n
			cur = append(cur, ')')
			backtrack(open, close+1)
			cur = cur[:len(cur)-1]
		}
	}
	backtrack(0, 0)
	return res
}

// ---------- Driver ----------
func main() {
	for _, n := range []int{3, 1, 2} {
		a, b := generateParenthesisBrute(n), generateParenthesis(n)
		slices.Sort(a) // normalize: any order is accepted
		slices.Sort(b)
		fmt.Println("brute    :", a)
		fmt.Println("backtrack:", b)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Recursive closures need `var f func(...)` declared before assigning,
 *   so the body can refer to f.
 * - string(byteSlice) copies the bytes, so later appends don't alias it.
 * - make([]byte, 0, 2*n) preallocates capacity, avoiding regrowth.
 * - []byte("()") iterates the bytes of a string literal.
 */
