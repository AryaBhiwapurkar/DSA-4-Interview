/*
 * 0017. Letter Combinations of a Phone Number  |  Medium  |  Backtracking
 * Link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 *
 * Problem: Return every letter string that a string of digits 2-9 could
 *          spell on a phone keypad. Any order.
 *
 * Examples:
 *   "23"  -> [ad ae af bd be bf cd ce cf]
 *   ""    -> []
 *   "2"   -> [a b c]
 *   "79"  -> 16 strings, "pw" .. "sz"
 *
 * Approaches:
 *   1. Iterative expansion       O(4^n * n) time, O(4^n * n) space
 *   2. Backtracking  ⭐           O(4^n * n) time, O(n) extra space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

var keys = [10]string{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}

// ---------- Approach 1: Iterative Expansion ----------
func letterCombinationsIter(digits string) []string {
	if digits == "" {
		return []string{}
	}
	res := []string{""}
	for i := 0; i < len(digits); i++ {
		next := []string{}
		for _, s := range res {
			for _, c := range keys[digits[i]-'0'] {
				next = append(next, s+string(c))
			}
		}
		res = next
	}
	return res
}

// ---------- Approach 2: Backtracking ⭐ ----------
func letterCombinations(digits string) []string {
	res := []string{}
	if digits == "" {
		return res // otherwise dfs would save ""
	}
	path := []byte{}
	var dfs func(i int)
	dfs = func(i int) {
		if i == len(digits) {
			res = append(res, string(path)) // string() copies the bytes
			return
		}
		for _, c := range []byte(keys[digits[i]-'0']) {
			path = append(path, c)
			dfs(i + 1)
			path = path[:len(path)-1] // unchoose
		}
	}
	dfs(0)
	return res
}

// ---------- Driver ----------
func main() {
	for _, d := range []string{"23", "", "2", "79"} {
		a, b := letterCombinationsIter(d), letterCombinations(d)
		slices.Sort(a) // normalize: any order is accepted
		slices.Sort(b)
		fmt.Println("iter     :", a)
		fmt.Println("backtrack:", b)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - var dfs func(int) declared before assignment lets the closure recurse.
 * - digits[i] is a byte; subtracting '0' gives the keypad index.
 * - string(path) copies a []byte, so later appends don't alter saved results.
 * - Ranging over a string yields runes; []byte(s) ranges bytes.
 */
