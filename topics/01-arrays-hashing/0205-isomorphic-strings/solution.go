/*
 * 0205. Isomorphic Strings  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/isomorphic-strings/
 *
 * Problem: Return true if each char of s can be replaced consistently to
 *          get t, with no two different chars of s mapping to the same
 *          char of t (one-to-one mapping).
 *
 * Examples:
 *   s="egg",   t="add"    -> true
 *   s="foo",   t="bar"    -> false
 *   s="paper", t="title"  -> true
 *   s="badc",  t="baba"   -> false
 *
 * Approaches:
 *   1. First-occurrence signature   O(n) time, O(n) space
 *   2. Two maps  ⭐                  O(n) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
)

// ---------- Approach 1: First-Occurrence Signature ----------
func signature(s string) []int {
	first := make(map[byte]int)
	sig := make([]int, len(s))
	for i := 0; i < len(s); i++ {
		if _, ok := first[s[i]]; !ok {
			first[s[i]] = i
		}
		sig[i] = first[s[i]]
	}
	return sig
}

func isIsomorphicSignature(s, t string) bool {
	return len(s) == len(t) && slices.Equal(signature(s), signature(t))
}

// ---------- Approach 2: Two Maps ⭐ ----------
func isIsomorphic(s, t string) bool {
	if len(s) != len(t) {
		return false
	}
	var st, ts [256]int // stores mapped byte + 1, so 0 means unmapped
	for i := 0; i < len(s); i++ {
		a, b := s[i], t[i]
		if st[a] == 0 && ts[b] == 0 {
			st[a] = int(b) + 1
			ts[b] = int(a) + 1
		} else if st[a] != int(b)+1 || ts[b] != int(a)+1 {
			return false // breaks one direction of the bijection
		}
	}
	return true
}

// ---------- Driver ----------
func main() {
	tests := [][2]string{{"egg", "add"}, {"foo", "bar"}, {"paper", "title"}, {"badc", "baba"}}
	for _, tc := range tests {
		fmt.Println("signature:", isIsomorphicSignature(tc[0], tc[1]))
		fmt.Println("two maps :", isIsomorphic(tc[0], tc[1]))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Zero value trap: byte 0 is valid data, so store value+1 and treat 0 as "unset".
 * - slices.Equal compares two slices element-wise.
 * - A byte indexes a [256]int array directly (no cast needed).
 */
