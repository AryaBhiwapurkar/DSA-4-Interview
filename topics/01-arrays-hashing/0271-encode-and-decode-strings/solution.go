/*
 * 0271. Encode and Decode Strings  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/encode-and-decode-strings/
 *
 * Problem: Design encode([]string) -> string and decode(string) -> []string
 *          with decode(encode(x)) == x. Strings can hold any ASCII character.
 *
 * Examples:
 *   ["Hello","World"]  -> encoded "5#Hello5#World"  -> ["Hello","World"]
 *   [""]               -> encoded "0#"              -> [""]
 *   ["1#2","#","//;"]  -> round-trips unchanged
 *   []                 -> encoded ""                -> []
 *
 * Approaches:
 *   1. Escaped delimiter     O(N) time, O(N) space
 *   2. Length prefix  ⭐      O(N) time, O(N) space   <- go-to
 */

package main

import (
	"fmt"
	"strconv"
	"strings"
)

// ---------- Approach 1: Escaped Delimiter ----------
// '/' is written as "//", and every string ends with "/;".
func encodeEscaped(strs []string) string {
	var sb strings.Builder
	for _, s := range strs {
		sb.WriteString(strings.ReplaceAll(s, "/", "//"))
		sb.WriteString("/;")
	}
	return sb.String()
}

func decodeEscaped(s string) []string {
	res := []string{}
	var cur strings.Builder
	for i := 0; i < len(s); i++ {
		if s[i] == '/' {
			if s[i+1] == ';' { // terminator
				res = append(res, cur.String())
				cur.Reset()
			} else {
				cur.WriteByte('/') // "//" -> literal '/'
			}
			i++
		} else {
			cur.WriteByte(s[i])
		}
	}
	return res
}

// ---------- Approach 2: Length Prefix ⭐ ----------
func encode(strs []string) string {
	var sb strings.Builder
	for _, s := range strs {
		sb.WriteString(strconv.Itoa(len(s)))
		sb.WriteByte('#')
		sb.WriteString(s)
	}
	return sb.String()
}

func decode(s string) []string {
	res := []string{}
	for i := 0; i < len(s); {
		j := i + strings.IndexByte(s[i:], '#') // search from i: earlier content may contain '#'
		length, _ := strconv.Atoi(s[i:j])
		res = append(res, s[j+1:j+1+length])
		i = j + 1 + length
	}
	return res
}

// ---------- Driver ----------
func main() {
	tests := [][]string{{"Hello", "World"}, {""}, {"1#2", "#", "//;"}, {}}
	for _, strs := range tests {
		fmt.Printf("encoded: %q\n", encode(strs))
		fmt.Printf("escaped: %q\n", decodeEscaped(encodeEscaped(strs)))
		fmt.Printf("length : %q\n", decode(encode(strs)))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strings.Builder is the efficient way to build a string piece by piece.
 * - strings.IndexByte(s[i:], c) is relative to i; add i back.
 * - strconv.Itoa / strconv.Atoi convert int <-> string (Atoi also returns an error).
 * - %q on a []string prints each element quoted.
 */
