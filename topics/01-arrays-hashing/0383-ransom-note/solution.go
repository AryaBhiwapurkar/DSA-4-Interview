/*
 * 0383. Ransom Note  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/ransom-note/
 *
 * Problem: Return true if ransomNote can be built from the letters of
 *          magazine, using each magazine letter at most once.
 *
 * Examples:
 *   note="a",  mag="b"    -> false
 *   note="aa", mag="ab"   -> false
 *   note="aa", mag="aab"  -> true
 *
 * Approaches:
 *   1. Brute force (mark used)   O(m*n) time, O(n) space
 *   2. Count array  ⭐            O(m+n) time, O(1) space   <- go-to
 */

package main

import (
	"bytes"
	"fmt"
)

// ---------- Approach 1: Brute Force ----------
func canConstructBrute(note, mag string) bool {
	letters := []byte(mag) // mutable copy
	for i := 0; i < len(note); i++ {
		pos := bytes.IndexByte(letters, note[i])
		if pos == -1 {
			return false
		}
		letters[pos] = '#' // mark as used
	}
	return true
}

// ---------- Approach 2: Count Array ⭐ ----------
func canConstruct(note, mag string) bool {
	var cnt [26]int
	for i := 0; i < len(mag); i++ {
		cnt[mag[i]-'a']++
	}
	for i := 0; i < len(note); i++ {
		cnt[note[i]-'a']--
		if cnt[note[i]-'a'] < 0 { // needed more than available
			return false
		}
	}
	return true
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{{"a", "b"}, {"aa", "ab"}, {"aa", "aab"}}
	for _, tc := range tests {
		fmt.Println("brute:", canConstructBrute(tc[0], tc[1]))
		fmt.Println("count:", canConstruct(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - bytes.IndexByte / strings.IndexByte return -1 when not found.
 * - Go has no `--x` expression; decrement is a statement, then compare.
 * - []byte(s) makes a mutable copy of a string.
 */
