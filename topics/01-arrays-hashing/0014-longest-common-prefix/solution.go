/*
 * 0014. Longest Common Prefix  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/longest-common-prefix/
 *
 * Problem: Return the longest prefix shared by all strings, or "" if none.
 *
 * Examples:
 *   ["flower","flow","flight"]  -> "fl"
 *   ["dog","racecar","car"]     -> ""
 *   ["ab","a"]                  -> "a"
 *   ["alone"]                   -> "alone"
 *
 * Approaches:
 *   1. Horizontal scan         O(S) time, O(1) extra space
 *   2. Sort, first vs last     O(S log n) time, O(n) space (sorted copy)
 *   3. Vertical scan  ⭐        O(S) time, O(1) extra space   <- go-to
 *   (S = total number of characters)
 */

package main

import (
	"fmt"
	"slices"
	"strings"
)

// ---------- Approach 1: Horizontal Scan ----------
func longestCommonPrefixHorizontal(strs []string) string {
	prefix := strs[0]
	for _, s := range strs[1:] {
		for !strings.HasPrefix(s, prefix) {
			prefix = prefix[:len(prefix)-1]
		}
	}
	return prefix
}

// ---------- Approach 2: Sort, Compare First and Last ----------
func longestCommonPrefixSorted(strs []string) string {
	s := slices.Clone(strs)
	slices.Sort(s)
	a, b := s[0], s[len(s)-1] // most different pair after sorting
	i := 0
	for i < len(a) && i < len(b) && a[i] == b[i] {
		i++
	}
	return a[:i]
}

// ---------- Approach 3: Vertical Scan ⭐ ----------
func longestCommonPrefix(strs []string) string {
	first := strs[0]
	for i := 0; i < len(first); i++ {
		for _, s := range strs[1:] {
			if i >= len(s) || s[i] != first[i] {
				return first[:i]
			}
		}
	}
	return first
}

// ---------- Driver ----------
func main() {
	tests := [][]string{{"flower", "flow", "flight"}, {"dog", "racecar", "car"}, {"ab", "a"}, {"alone"}}
	for _, strs := range tests {
		fmt.Printf("horizontal: %q\n", longestCommonPrefixHorizontal(strs))
		fmt.Printf("sorted    : %q\n", longestCommonPrefixSorted(strs))
		fmt.Printf("vertical  : %q\n", longestCommonPrefix(strs))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strings.HasPrefix(s, p) checks a prefix.
 * - %q prints a string with quotes (empty shows as "").
 * - s[:i] slices a string by byte index without copying.
 * - strs[1:] iterates all but the first element.
 */
