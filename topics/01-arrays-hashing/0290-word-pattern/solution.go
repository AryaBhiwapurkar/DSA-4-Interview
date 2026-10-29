/*
 * 0290. Word Pattern  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/word-pattern/
 *
 * Problem: Return true if the words in s follow the letter pattern with
 *          a one-to-one mapping between letters and words.
 *
 * Examples:
 *   "abba", "dog cat cat dog"   -> true
 *   "abba", "dog cat cat fish"  -> false
 *   "aaaa", "dog cat cat dog"   -> false
 *   "abba", "dog dog dog dog"   -> false
 *
 * Approaches:
 *   1. First-occurrence signature   O(n+m) time, O(n+m) space
 *   2. Two hashmaps  ⭐              O(n+m) time, O(k) space   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

// ---------- Approach 1: First-Occurrence Signature ----------
func wordPatternSignature(pattern, s string) bool {
	words := strings.Fields(s)
	if len(words) != len(pattern) {
		return false
	}
	pf := make(map[byte]int)
	wf := make(map[string]int)
	for i, w := range words {
		if _, ok := pf[pattern[i]]; !ok {
			pf[pattern[i]] = i
		}
		if _, ok := wf[w]; !ok {
			wf[w] = i
		}
		if pf[pattern[i]] != wf[w] {
			return false
		}
	}
	return true
}

// ---------- Approach 2: Two Hashmaps ⭐ ----------
func wordPattern(pattern, s string) bool {
	words := strings.Fields(s)
	if len(words) != len(pattern) {
		return false
	}
	pw := make(map[byte]string)
	wp := make(map[string]byte)
	for i, w := range words {
		c := pattern[i]
		mw, ok1 := pw[c]
		mc, ok2 := wp[w]
		switch {
		case !ok1 && !ok2:
			pw[c] = w
			wp[w] = c
		case !ok1 || !ok2 || mw != w || mc != c:
			return false
		}
	}
	return true
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{
		{"abba", "dog cat cat dog"},
		{"abba", "dog cat cat fish"},
		{"aaaa", "dog cat cat dog"},
		{"abba", "dog dog dog dog"},
	}
	for _, tc := range tests {
		fmt.Println("signature:", wordPatternSignature(tc[0], tc[1]))
		fmt.Println("two maps :", wordPattern(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strings.Fields splits on any whitespace and drops empty strings.
 * - strings.Split(s, " ") keeps empty strings for repeated spaces.
 * - A tagless switch is a clean if/else-if chain.
 * - Use comma-ok for both maps: "" and 0 are valid zero values.
 */
