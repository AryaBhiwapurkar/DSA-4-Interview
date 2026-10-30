/*
 * 0020. Valid Parentheses  |  Easy  |  Stack
 * Link: https://leetcode.com/problems/valid-parentheses/
 *
 * Problem: A string of ()[]{} is valid if every closer matches the most
 *          recent unclosed opener of the same type and nothing is left open.
 *
 * Examples:
 *   "()"      -> true
 *   "()[]{}"  -> true
 *   "(]"      -> false
 *   "([])"    -> true
 *   "([)]"    -> false
 *   "]"       -> false
 *   "(("      -> false
 *
 * Approaches:
 *   1. Repeated removal   O(n^2) time, O(n) space
 *   2. Stack  ⭐           O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

// ---------- Approach 1: Repeated Removal ----------
func isValidBrute(s string) bool {
	for {
		t := strings.ReplaceAll(s, "()", "")
		t = strings.ReplaceAll(t, "[]", "")
		t = strings.ReplaceAll(t, "{}", "")
		if t == s {
			return s == ""
		}
		s = t
	}
}

// ---------- Approach 2: Stack ⭐ ----------
func isValid(s string) bool {
	match := map[byte]byte{')': '(', ']': '[', '}': '{'}
	st := []byte{}
	for i := 0; i < len(s); i++ {
		c := s[i]
		open, isCloser := match[c]
		if !isCloser {
			st = append(st, c)
			continue
		}
		if len(st) == 0 || st[len(st)-1] != open { // check length before indexing
			return false
		}
		st = st[:len(st)-1]
	}
	return len(st) == 0 // leftovers = unclosed openers
}

// ---------- Driver ----------
func main() {
	tests := []string{"()", "()[]{}", "(]", "([])", "([)]", "]", "(("}
	for _, s := range tests {
		fmt.Println("brute:", isValidBrute(s))
		fmt.Println("stack:", isValid(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A slice is the stack: append to push, st[len(st)-1] to peek,
 *   st = st[:len(st)-1] to pop.
 * - Comma-ok on a map tells "closer" apart from "opener" in one lookup.
 * - Indexing a string gives a byte; character literals like ')' are runes
 *   but convert to byte in a map[byte]byte literal.
 * - strings.ReplaceAll(s, old, new) replaces every occurrence.
 */
