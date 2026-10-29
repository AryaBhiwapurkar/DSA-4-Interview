/*
 * 0567. Permutation in String  |  Medium  |  Sliding Window
 * Link: https://leetcode.com/problems/permutation-in-string/
 *
 * Problem: Return true if some permutation of s1 is a substring of s2.
 *
 * Examples:
 *   s1="ab",  s2="eidbaooo"  -> true
 *   s1="ab",  s2="eidboaoo"  -> false
 *   s1="abc", s2="ab"        -> false
 *   s1="adc", s2="dcda"      -> true
 *
 * Approaches:
 *   1. Sort every window            O(n * m log m) time, O(m) space
 *   2. Fixed window + counts  ⭐     O(26 * n) time, O(1) space   <- go-to
 *   3. Window + matches counter     O(n) time, O(1) space
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Sort Every Window ----------
func checkInclusionSort(s1, s2 string) bool {
	m := len(s1)
	target := []byte(s1)
	slices.Sort(target)
	for i := 0; i+m <= len(s2); i++ {
		w := []byte(s2[i : i+m])
		slices.Sort(w)
		if slices.Equal(w, target) {
			return true
		}
	}
	return false
}

// ---------- Approach 2: Fixed Window + Count Arrays ⭐ ----------
func checkInclusion(s1, s2 string) bool {
	m, n := len(s1), len(s2)
	if m > n {
		return false
	}
	var need, win [26]int
	for i := 0; i < m; i++ {
		need[s1[i]-'a']++
		win[s2[i]-'a']++
	}
	if need == win { // first window
		return true
	}
	for r := m; r < n; r++ {
		win[s2[r]-'a']++   // char entering
		win[s2[r-m]-'a']-- // char leaving
		if need == win {
			return true
		}
	}
	return false
}

// ---------- Approach 3: Window + Matches Counter ----------
func checkInclusionMatches(s1, s2 string) bool {
	m, n := len(s1), len(s2)
	if m > n {
		return false
	}
	var need, win [26]int
	for i := 0; i < m; i++ {
		need[s1[i]-'a']++
		win[s2[i]-'a']++
	}
	matches := 0 // letters whose counts agree
	for c := 0; c < 26; c++ {
		if need[c] == win[c] {
			matches++
		}
	}
	update := func(c byte, delta int) {
		if win[c] == need[c] { // was equal, about to change
			matches--
		}
		win[c] += delta
		if win[c] == need[c] { // equal after the change
			matches++
		}
	}
	for r := m; r < n; r++ {
		if matches == 26 {
			return true
		}
		update(s2[r]-'a', 1)
		update(s2[r-m]-'a', -1)
	}
	return matches == 26
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{{"ab", "eidbaooo"}, {"ab", "eidboaoo"}, {"abc", "ab"}, {"adc", "dcda"}}
	for _, tc := range tests {
		fmt.Println("sort   :", checkInclusionSort(tc[0], tc[1]))
		fmt.Println("counts :", checkInclusion(tc[0], tc[1]))
		fmt.Println("matches:", checkInclusionMatches(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Fixed-size arrays compare with == (slices don't).
 * - Closures capture variables by reference: update() modifies matches and win.
 * - []byte(s2[i:i+m]) copies a window so it can be sorted.
 */
