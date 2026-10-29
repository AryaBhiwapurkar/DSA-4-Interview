/*
 * 0392. Is Subsequence  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/is-subsequence/
 *
 * Problem: Return true if s can be formed by deleting some characters of t
 *          without reordering the rest.
 *
 * Examples:
 *   s="abc", t="ahbgdc"  -> true
 *   s="axc", t="ahbgdc"  -> false
 *   s="",    t="abc"     -> true
 *   s="aa",  t="a"       -> false
 *
 * Approaches:
 *   1. Two pointers  ⭐                 O(|t|) time, O(1) space   <- go-to
 *   2. Index t + binary search         O(|s| log |t|) per query, O(|t|) space
 */

package main

import (
	"fmt"
	"sort"
)

// ---------- Approach 1: Two Pointers ⭐ ----------
func isSubsequence(s, t string) bool {
	i := 0
	for j := 0; j < len(t) && i < len(s); j++ {
		if t[j] == s[i] { // greedy: match as early as possible
			i++
		}
	}
	return i == len(s)
}

// ---------- Approach 2: Index t + Binary Search ----------
func isSubsequenceIndexed(s, t string) bool {
	var pos [26][]int // pos[c] = sorted indices of c in t
	for j := 0; j < len(t); j++ {
		pos[t[j]-'a'] = append(pos[t[j]-'a'], j)
	}
	prev := -1
	for i := 0; i < len(s); i++ {
		p := pos[s[i]-'a']
		k := sort.SearchInts(p, prev+1) // first index >= prev+1, i.e. strictly after prev
		if k == len(p) {
			return false
		}
		prev = p[k]
	}
	return true
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{{"abc", "ahbgdc"}, {"axc", "ahbgdc"}, {"", "abc"}, {"aa", "a"}}
	for _, tc := range tests {
		fmt.Println("pointers:", isSubsequence(tc[0], tc[1]))
		fmt.Println("indexed :", isSubsequenceIndexed(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - sort.SearchInts(a, x) returns the first index with a[i] >= x (lower bound).
 * - For "strictly greater than v" on ints, search for v+1.
 * - [26][]int is an array of 26 nil slices; append works on nil.
 */
