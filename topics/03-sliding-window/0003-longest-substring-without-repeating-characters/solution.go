/*
 * 0003. Longest Substring Without Repeating Characters  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * Problem: Return the length of the longest substring with all-distinct
 *          characters.
 *
 * Examples:
 *   "abcabcbb"  -> 3
 *   "bbbbb"     -> 1
 *   "pwwkew"    -> 3
 *   ""          -> 0
 *   "abba"      -> 2
 *
 * Approaches:
 *   1. Brute force                   O(n^2) time, O(alphabet) space
 *   2. Window + set  ⭐               O(n) time, O(min(n, alphabet)) space   <- go-to
 *   3. Window + last-seen index      O(n) time, O(alphabet) space
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force ----------
func lengthOfLongestSubstringBrute(s string) int {
	best := 0
	for i := 0; i < len(s); i++ {
		var seen [256]bool
		for j := i; j < len(s) && !seen[s[j]]; j++ {
			seen[s[j]] = true
			best = max(best, j-i+1)
		}
	}
	return best
}

// ---------- Approach 2: Window + Set ⭐ ----------
func lengthOfLongestSubstring(s string) int {
	var inWindow [256]bool // byte-indexed set
	l, best := 0, 0
	for r := 0; r < len(s); r++ {
		for inWindow[s[r]] { // shrink until s[r] is no longer inside
			inWindow[s[l]] = false
			l++
		}
		inWindow[s[r]] = true
		best = max(best, r-l+1) // window is valid here
	}
	return best
}

// ---------- Approach 3: Window + Last-Seen Index ----------
func lengthOfLongestSubstringJump(s string) int {
	var last [256]int // stores index+1, so 0 means "never seen"
	l, best := 0, 0
	for r := 0; r < len(s); r++ {
		l = max(l, last[s[r]]) // max: never move l backwards ("abba")
		last[s[r]] = r + 1
		best = max(best, r-l+1)
	}
	return best
}

// ---------- Driver ----------
func main() {
	for _, s := range []string{"abcabcbb", "bbbbb", "pwwkew", "", "abba"} {
		fmt.Println("brute:", lengthOfLongestSubstringBrute(s))
		fmt.Println("set  :", lengthOfLongestSubstring(s))
		fmt.Println("jump :", lengthOfLongestSubstringJump(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A [256]bool array indexed by byte is a fast fixed-alphabet set.
 * - Storing index+1 lets the zero value mean "not seen" (no -1 fill needed).
 * - s[i] is a byte; this treats the string as ASCII bytes.
 */
