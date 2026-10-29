/*
 * 0076. Minimum Window Substring  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/minimum-window-substring/
 *
 * Problem: Return the shortest substring of s containing every character
 *          of t (with multiplicity), or "" if none exists.
 *
 * Examples:
 *   s="ADOBECODEBANC", t="ABC"  -> "BANC"
 *   s="a", t="a"                -> "a"
 *   s="a", t="aa"               -> ""
 *   s="aAbB", t="AB"            -> "AbB"
 *
 * Approaches:
 *   1. Brute force                         O(|s|^2 * 128) time, O(128) space
 *   2. Window, compare full counts         O(128 * |s|) time, O(128) space
 *   3. Window with have/need  ⭐            O(|s| + |t|) time, O(128) space   <- go-to
 */

package main

import (
	"fmt"
	"math"
)

func covers(win, tc *[128]int) bool {
	for c := 0; c < 128; c++ {
		if win[c] < tc[c] {
			return false
		}
	}
	return true
}

// ---------- Approach 1: Brute Force ----------
func minWindowBrute(s, t string) string {
	var tc [128]int
	for i := 0; i < len(t); i++ {
		tc[t[i]]++
	}
	bestLen, bestL := math.MaxInt, 0
	for i := 0; i < len(s); i++ {
		var win [128]int
		for j := i; j < len(s); j++ {
			win[s[j]]++
			if covers(&win, &tc) {
				if j-i+1 < bestLen {
					bestLen, bestL = j-i+1, i
				}
				break // longer windows from i can't be shorter
			}
		}
	}
	if bestLen == math.MaxInt {
		return ""
	}
	return s[bestL : bestL+bestLen]
}

// ---------- Approach 2: Window, Compare Full Counts ----------
func minWindowCompare(s, t string) string {
	var tc, win [128]int
	for i := 0; i < len(t); i++ {
		tc[t[i]]++
	}
	l, bestLen, bestL := 0, math.MaxInt, 0
	for r := 0; r < len(s); r++ {
		win[s[r]]++
		for covers(&win, &tc) { // O(128) validity check
			if r-l+1 < bestLen {
				bestLen, bestL = r-l+1, l
			}
			win[s[l]]--
			l++
		}
	}
	if bestLen == math.MaxInt {
		return ""
	}
	return s[bestL : bestL+bestLen]
}

// ---------- Approach 3: Window With have/need ⭐ ----------
func minWindow(s, t string) string {
	var tc, win [128]int
	need := 0 // distinct chars to satisfy
	for i := 0; i < len(t); i++ {
		if tc[t[i]] == 0 {
			need++
		}
		tc[t[i]]++
	}
	have, l, bestLen, bestL := 0, 0, math.MaxInt, 0
	for r := 0; r < len(s); r++ {
		c := s[r]
		win[c]++
		if win[c] == tc[c] { // c just became satisfied (never true for chars not in t)
			have++
		}
		for have == need {
			if r-l+1 < bestLen {
				bestLen, bestL = r-l+1, l
			}
			d := s[l]
			if win[d] == tc[d] { // d is about to drop below its requirement
				have--
			}
			win[d]--
			l++
		}
	}
	if bestLen == math.MaxInt {
		return ""
	}
	return s[bestL : bestL+bestLen] // slice once at the end
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{{"ADOBECODEBANC", "ABC"}, {"a", "a"}, {"a", "aa"}, {"aAbB", "AB"}}
	for _, tc := range tests {
		fmt.Printf("brute   : %q\n", minWindowBrute(tc[0], tc[1]))
		fmt.Printf("compare : %q\n", minWindowCompare(tc[0], tc[1]))
		fmt.Printf("have/need: %q\n", minWindow(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Pass large arrays by pointer (*[128]int) to avoid copying them on every call.
 * - Indexing a pointer-to-array works directly: win[c] on *[128]int.
 * - Slicing a string s[a:b] is O(1) (shares memory); do it once at the end.
 */
