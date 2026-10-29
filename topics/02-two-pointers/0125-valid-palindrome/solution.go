/*
 * 0125. Valid Palindrome  |  Easy  |  Two Pointers
 * Link: https://leetcode.com/problems/valid-palindrome/
 *
 * Problem: After lowercasing and removing non-alphanumeric characters,
 *          does the string read the same forwards and backwards?
 *
 * Examples:
 *   "A man, a plan, a canal: Panama"  -> true
 *   "race a car"                      -> false
 *   " "                               -> true
 *   "0P"                              -> false
 *
 * Approaches:
 *   1. Clean + reverse      O(n) time, O(n) space
 *   2. Two pointers  ⭐      O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
	"unicode"
)

func isAlnum(b byte) bool {
	return unicode.IsLetter(rune(b)) || unicode.IsDigit(rune(b))
}

func lower(b byte) byte {
	return byte(unicode.ToLower(rune(b)))
}

// ---------- Approach 1: Clean + Reverse ----------
func isPalindromeClean(s string) bool {
	var t []byte
	for i := 0; i < len(s); i++ {
		if isAlnum(s[i]) {
			t = append(t, lower(s[i]))
		}
	}
	r := slices.Clone(t)
	slices.Reverse(r)
	return slices.Equal(t, r)
}

// ---------- Approach 2: Two Pointers ⭐ ----------
func isPalindrome(s string) bool {
	l, r := 0, len(s)-1
	for l < r {
		for l < r && !isAlnum(s[l]) { // skip junk on the left
			l++
		}
		for l < r && !isAlnum(s[r]) { // skip junk on the right
			r--
		}
		if lower(s[l]) != lower(s[r]) {
			return false
		}
		l, r = l+1, r-1
	}
	return true
}

// ---------- Driver ----------
func main() {
	for _, s := range []string{"A man, a plan, a canal: Panama", "race a car", " ", "0P"} {
		fmt.Println("clean   :", isPalindromeClean(s))
		fmt.Println("pointers:", isPalindrome(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - unicode.IsLetter / IsDigit / ToLower take a rune; convert ASCII bytes with rune(b).
 * - slices.Equal compares two slices element-wise.
 * - Parallel assignment l, r = l+1, r-1 moves both pointers.
 */
