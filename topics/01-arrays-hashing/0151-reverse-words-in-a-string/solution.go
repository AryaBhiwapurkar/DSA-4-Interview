/*
 * 0151. Reverse Words in a String  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/reverse-words-in-a-string/
 *
 * Problem: Return the words of s in reverse order, joined by single
 *          spaces, with no leading/trailing/repeated spaces.
 *
 * Examples:
 *   "the sky is blue"    -> "blue is sky the"
 *   "  hello world  "    -> "world hello"
 *   "a good   example"   -> "example good a"
 *   "single"             -> "single"
 *
 * Approaches:
 *   1. Split + reverse + join  ⭐   O(n) time, O(n) space   <- go-to
 *   2. In-place reversal           O(n) time, O(n) space in Go (string is immutable)
 */

package main

import (
	"fmt"
	"slices"
	"strings"
)

// ---------- Approach 1: Split + Reverse + Join ⭐ ----------
func reverseWords(s string) string {
	words := strings.Fields(s) // drops all extra whitespace
	slices.Reverse(words)
	return strings.Join(words, " ")
}

// ---------- Approach 2: In-Place Reversal + Compaction ----------
func reverseWordsInPlace(s string) string {
	a := []byte(s)    // strings are immutable: work on a byte copy
	slices.Reverse(a) // words in final order, each backwards
	n, write := len(a), 0
	for read := 0; read < n; read++ {
		if a[read] == ' ' {
			continue
		}
		if write > 0 { // one space before every word but the first
			a[write] = ' '
			write++
		}
		start := write
		for read < n && a[read] != ' ' {
			a[write] = a[read]
			write++
			read++
		}
		slices.Reverse(a[start:write]) // fix this word
	}
	return string(a[:write]) // drop leftover tail
}

// ---------- Driver ----------
func main() {
	for _, s := range []string{"the sky is blue", "  hello world  ", "a good   example", "single"} {
		fmt.Printf("split   : %q\n", reverseWords(s))
		fmt.Printf("in-place: %q\n", reverseWordsInPlace(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strings.Fields + strings.Join is the idiomatic split/join on whitespace.
 * - slices.Reverse works on any slice, including a sub-slice a[i:j].
 * - []byte(s) copies; string(a[:k]) copies back.
 */
