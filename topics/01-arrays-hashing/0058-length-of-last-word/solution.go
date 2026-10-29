/*
 * 0058. Length of Last Word  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/length-of-last-word/
 *
 * Problem: Return the length of the last word in a string of words and
 *          spaces (a word is a maximal run of non-space characters).
 *
 * Examples:
 *   "Hello World"                   -> 5
 *   "   fly me   to   the moon  "   -> 4
 *   "luffy is still joyboy"         -> 6
 *   "a"                             -> 1
 *
 * Approaches:
 *   1. Split, take last   O(n) time, O(n) space
 *   2. Reverse scan  ⭐    O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

// ---------- Approach 1: Split, Take Last ----------
func lengthOfLastWordSplit(s string) int {
	words := strings.Fields(s)
	return len(words[len(words)-1])
}

// ---------- Approach 2: Reverse Scan ⭐ ----------
func lengthOfLastWord(s string) int {
	i := len(s) - 1
	for i >= 0 && s[i] == ' ' { // skip trailing spaces
		i--
	}
	length := 0
	for i >= 0 && s[i] != ' ' {
		length++
		i--
	}
	return length
}

// ---------- Driver ----------
func main() {
	for _, s := range []string{"Hello World", "   fly me   to   the moon  ", "luffy is still joyboy", "a"} {
		fmt.Println("split:", lengthOfLastWordSplit(s))
		fmt.Println("scan :", lengthOfLastWord(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strings.Fields drops empty tokens; strings.Split(s, " ") keeps them.
 * - `for cond {}` is Go's while loop.
 * - No negative indexing: s[-1] is a compile/runtime error.
 */
