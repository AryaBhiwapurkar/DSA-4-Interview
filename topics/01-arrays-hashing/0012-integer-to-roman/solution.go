/*
 * 0012. Integer to Roman  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/integer-to-roman/
 *
 * Problem: Convert an integer in [1, 3999] to a Roman numeral using the
 *          standard subtractive forms (IV, IX, XL, XC, CD, CM).
 *
 * Examples:
 *   3749  -> "MMMDCCXLIX"
 *   58    -> "LVIII"
 *   1994  -> "MCMXCIV"
 *   3999  -> "MMMCMXCIX"
 *
 * Approaches:
 *   1. Digit lookup tables          O(1) time, O(1) space
 *   2. Greedy over value table  ⭐   O(1) time, O(1) space   <- go-to
 */

package main

import (
	"fmt"
	"strings"
)

var (
	th = []string{"", "M", "MM", "MMM"}
	hu = []string{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"}
	te = []string{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"}
	on = []string{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}
)

// descending; includes subtractive pairs
var table = []struct {
	value int
	sym   string
}{
	{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
	{50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"},
}

// ---------- Approach 1: Digit Lookup Tables ----------
func intToRomanTables(num int) string {
	return th[num/1000] + hu[num%1000/100] + te[num%100/10] + on[num%10]
}

// ---------- Approach 2: Greedy Over Value Table ⭐ ----------
func intToRoman(num int) string {
	var sb strings.Builder
	for _, e := range table {
		for num >= e.value { // loop, not if: symbols can repeat
			sb.WriteString(e.sym)
			num -= e.value
		}
	}
	return sb.String()
}

// ---------- Driver ----------
func main() {
	for _, num := range []int{3749, 58, 1994, 3999} {
		fmt.Println("tables:", intToRomanTables(num))
		fmt.Println("greedy:", intToRoman(num))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - var ( ... ) groups several package-level declarations.
 * - A slice of anonymous structs keeps (value, symbol) pairs together.
 * - strings.Builder avoids reallocating on every append.
 */
