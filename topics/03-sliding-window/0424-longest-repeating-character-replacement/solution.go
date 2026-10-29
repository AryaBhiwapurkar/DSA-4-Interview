/*
 * 0424. Longest Repeating Character Replacement  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/longest-repeating-character-replacement/
 *
 * Problem: Uppercase string, at most k character changes; return the
 *          longest substring that can become one repeated letter.
 *
 * Examples:
 *   "ABAB", k=2       -> 4
 *   "AABABBA", k=1    -> 4
 *   "AAAA", k=0       -> 4
 *   "ABCDE", k=1      -> 2
 *
 * Approaches:
 *   1. Brute force                   O(n^2) time, O(26) space
 *   2. Per-letter window             O(26*n) time, O(1) space
 *   3. Window + max frequency  ⭐     O(n) time, O(26) space   <- go-to
 */

package main

import "fmt"

// ---------- Approach 1: Brute Force ----------
func characterReplacementBrute(s string, k int) int {
	best := 0
	for i := 0; i < len(s); i++ {
		var cnt [26]int
		maxf := 0
		for j := i; j < len(s); j++ {
			cnt[s[j]-'A']++
			maxf = max(maxf, cnt[s[j]-'A'])
			if (j-i+1)-maxf > k { // needs more than k changes
				break
			}
			best = max(best, j-i+1)
		}
	}
	return best
}

// ---------- Approach 2: Per-Letter Window ----------
func characterReplacementPerLetter(s string, k int) int {
	best := 0
	for c := byte('A'); c <= 'Z'; c++ {
		l, others := 0, 0 // chars in window that aren't c
		for r := 0; r < len(s); r++ {
			if s[r] != c {
				others++
			}
			for others > k {
				if s[l] != c {
					others--
				}
				l++
			}
			best = max(best, r-l+1)
		}
	}
	return best
}

// ---------- Approach 3: Window + Max Frequency ⭐ ----------
func characterReplacement(s string, k int) int {
	var cnt [26]int
	l, maxf, best := 0, 0, 0
	for r := 0; r < len(s); r++ {
		cnt[s[r]-'A']++
		maxf = max(maxf, cnt[s[r]-'A'])
		if (r-l+1)-maxf > k { // slide, don't shrink: maxf may be stale, that's fine
			cnt[s[l]-'A']--
			l++
		}
		best = max(best, r-l+1)
	}
	return best
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		s string
		k int
	}{{"ABAB", 2}, {"AABABBA", 1}, {"AAAA", 0}, {"ABCDE", 1}}
	for _, t := range tests {
		fmt.Println("brute     :", characterReplacementBrute(t.s, t.k))
		fmt.Println("per-letter:", characterReplacementPerLetter(t.s, t.k))
		fmt.Println("maxfreq   :", characterReplacement(t.s, t.k))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - for c := byte('A'); c <= 'Z'; c++ loops over letters as bytes.
 * - s[i]-'A' is a byte, usable directly as an array index.
 * - No implicit bool->int: count with an explicit if.
 */
