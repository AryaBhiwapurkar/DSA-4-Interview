/*
 * 0030. Substring with Concatenation of All Words  |  Hard  |  Sliding Window
 * Link: https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 *
 * Problem: Words all have length w. Return every start index in s where
 *          the next m*w chars are a concatenation of all words, each once.
 *
 * Examples (printed sorted):
 *   "barfoothefoobarman", ["foo","bar"]                         -> [0,9]
 *   "wordgoodgoodgoodbestword", ["word","good","best","word"]   -> []
 *   "barfoofoobarthefoobarman", ["bar","foo","the"]             -> [6,9,12]
 *   "aaaa", ["aa","aa"]                                         -> [0]
 *
 * Approaches:
 *   1. Check every start             O(n * m * w) time, O(m * w) space
 *   2. Per-offset token window  ⭐    O(n * w) time, O(m * w) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: Check Every Start ----------
func findSubstringBrute(s string, words []string) []int {
	n, m, w := len(s), len(words), len(words[0])
	need := map[string]int{}
	for _, word := range words {
		need[word]++
	}
	res := []int{}
	for i := 0; i+m*w <= n; i++ {
		seen := map[string]int{}
		j := 0
		for ; j < m; j++ {
			tok := s[i+j*w : i+(j+1)*w]
			seen[tok]++
			if seen[tok] > need[tok] { // unknown words have need 0, so this also rejects them
				break
			}
		}
		if j == m {
			res = append(res, i)
		}
	}
	return res
}

// ---------- Approach 2: Per-Offset Token Window ⭐ ----------
func findSubstring(s string, words []string) []int {
	n, m, w := len(s), len(words), len(words[0])
	need := map[string]int{}
	for _, word := range words {
		need[word]++
	}
	res := []int{}
	for off := 0; off < w; off++ { // valid starts live on one of w tracks
		win := map[string]int{}
		left, count := off, 0 // count = tokens in window
		for r := off; r+w <= n; r += w {
			tok := s[r : r+w]
			if _, ok := need[tok]; !ok { // non-word breaks every window: reset
				clear(win)
				count = 0
				left = r + w
				continue
			}
			win[tok]++
			count++
			for win[tok] > need[tok] { // too many copies: drop from the left
				win[s[left:left+w]]--
				left += w
				count--
			}
			if count == m {
				res = append(res, left)
			}
		}
	}
	return res
}

// ---------- Driver ----------
func main() {
	tests := []struct {
		s     string
		words []string
	}{
		{"barfoothefoobarman", []string{"foo", "bar"}},
		{"wordgoodgoodgoodbestword", []string{"word", "good", "best", "word"}},
		{"barfoofoobarthefoobarman", []string{"bar", "foo", "the"}},
		{"aaaa", []string{"aa", "aa"}},
	}
	for _, t := range tests {
		a, b := findSubstringBrute(t.s, t.words), findSubstring(t.s, t.words)
		slices.Sort(a) // normalize: order is unspecified
		slices.Sort(b)
		fmt.Println("brute :", a)
		fmt.Println("window:", b)
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - clear(m) (Go 1.21+) deletes all entries of a map in place.
 * - Substrings s[a:b] share memory with s, so map keys are cheap to build.
 * - A missing key reads as 0, so need[tok] works for unknown tokens too.
 */
