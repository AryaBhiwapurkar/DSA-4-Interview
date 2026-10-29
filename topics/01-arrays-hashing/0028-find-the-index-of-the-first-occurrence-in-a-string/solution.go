/*
 * 0028. Find the Index of the First Occurrence in a String  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
 *
 * Problem: Return the index of the first occurrence of needle in
 *          haystack, or -1 if it does not occur.
 *
 * Examples:
 *   "sadbutsad", "sad"       -> 0
 *   "leetcode",  "leeto"     -> -1
 *   "abc",       "c"         -> 2
 *   "aabaaabaaac", "aabaaac" -> 4
 *
 * Approaches:
 *   1. Brute-force window  ⭐  O(n*m) time, O(1) space   <- go-to
 *   2. KMP                    O(n+m) time, O(m) space
 */

package main

import "fmt"

// ---------- Approach 1: Brute-Force Window ⭐ ----------
func strStr(haystack, needle string) int {
	n, m := len(haystack), len(needle)
	for i := 0; i <= n-m; i++ {
		j := 0
		for j < m && haystack[i+j] == needle[j] {
			j++
		}
		if j == m {
			return i
		}
	}
	return -1
}

// ---------- Approach 2: KMP ----------
func strStrKMP(haystack, needle string) int {
	m := len(needle)
	lps := make([]int, m) // lps[i]: longest proper prefix == suffix of needle[:i+1]
	for i, length := 1, 0; i < m; {
		switch {
		case needle[i] == needle[length]:
			length++
			lps[i] = length
			i++
		case length > 0:
			length = lps[length-1] // fall back, don't advance i
		default:
			i++
		}
	}
	j := 0
	for i := 0; i < len(haystack); i++ {
		for j > 0 && haystack[i] != needle[j] {
			j = lps[j-1] // reuse the matched prefix
		}
		if haystack[i] == needle[j] {
			j++
			if j == m {
				return i - m + 1
			}
		}
	}
	return -1
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{{"sadbutsad", "sad"}, {"leetcode", "leeto"}, {"abc", "c"}, {"aabaaabaaac", "aabaaac"}}
	for _, tc := range tests {
		fmt.Println("brute:", strStr(tc[0], tc[1]))
		fmt.Println("kmp  :", strStrKMP(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - len() returns int (signed), so n-m can go negative safely.
 * - Built-in: strings.Index(haystack, needle) returns -1 if absent.
 * - `for i, length := 1, 0; i < m; {` declares two loop vars, no post step.
 */
