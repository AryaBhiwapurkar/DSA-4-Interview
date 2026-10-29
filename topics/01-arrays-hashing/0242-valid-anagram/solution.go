/*
 * 0242. Valid Anagram  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/valid-anagram/
 *
 * Problem: Return true if t uses exactly the same letters as s with
 *          the same counts (t is a rearrangement of s).
 *
 * Examples:
 *   s="anagram", t="nagaram"  -> true
 *   s="rat",     t="car"      -> false
 *   s="ab",      t="a"        -> false
 *
 * Approaches:
 *   1. Sort both          O(n log n) time, O(n) space
 *   2. Count array  ⭐     O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Sort Both ----------
func isAnagramSorted(s, t string) bool {
	a, b := []byte(s), []byte(t) // strings are immutable: sort byte copies
	slices.Sort(a)
	slices.Sort(b)
	return string(a) == string(b)
}

// ---------- Approach 2: Count Array ⭐ ----------
func isAnagram(s, t string) bool {
	if len(s) != len(t) {
		return false
	}
	var cnt [26]int // arrays are zero-valued
	for i := 0; i < len(s); i++ {
		cnt[s[i]-'a']++
		cnt[t[i]-'a']--
	}
	for _, c := range cnt {
		if c != 0 {
			return false
		}
	}
	return true
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{{"anagram", "nagaram"}, {"rat", "car"}, {"ab", "a"}}
	for _, tc := range tests {
		fmt.Println("sorted:", isAnagramSorted(tc[0], tc[1]))
		fmt.Println("count :", isAnagram(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - s[i] is a byte; s[i]-'a' indexes 0..25 for lowercase ASCII.
 * - []byte(s) copies the string so it can be sorted.
 * - `var cnt [26]int` is a zeroed fixed-size array (a value, not a slice).
 * - [2]string is a handy fixed-size pair for test tables.
 */
