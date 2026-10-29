/*
 * 0013. Roman to Integer  |  Easy  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/roman-to-integer/
 *
 * Problem: Convert a valid Roman numeral (1..3999) to an integer.
 *          IV, IX, XL, XC, CD, CM are subtractive pairs.
 *
 * Examples:
 *   "III"       -> 3
 *   "LVIII"     -> 58
 *   "MCMXCIV"   -> 1994
 *   "MMMCMXCIX" -> 3999
 *
 * Approaches:
 *   1. Match two-char pairs first   O(n) time, O(1) space
 *   2. Compare with next  ⭐         O(n) time, O(1) space   <- go-to
 */

package main

import "fmt"

var val = map[byte]int{'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
var pairs = map[string]int{"IV": 4, "IX": 9, "XL": 40, "XC": 90, "CD": 400, "CM": 900}

// ---------- Approach 1: Match Two-Char Pairs First ----------
func romanToIntPairs(s string) int {
	total := 0
	for i := 0; i < len(s); {
		if i+1 < len(s) {
			if v, ok := pairs[s[i:i+2]]; ok {
				total += v
				i += 2
				continue
			}
		}
		total += val[s[i]]
		i++
	}
	return total
}

// ---------- Approach 2: Compare With Next ⭐ ----------
func romanToInt(s string) int {
	total := 0
	for i := 0; i < len(s); i++ {
		v := val[s[i]]
		if i+1 < len(s) && v < val[s[i+1]] { // smaller before larger: subtract
			total -= v
		} else {
			total += v
		}
	}
	return total
}

// ---------- Driver ----------
func main() {
	for _, s := range []string{"III", "LVIII", "MCMXCIV", "MMMCMXCIX"} {
		fmt.Println("pairs  :", romanToIntPairs(s))
		fmt.Println("compare:", romanToInt(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Package-level map literals act as constant lookup tables.
 * - Slicing a string past its length panics: guard i+1 < len(s) first.
 * - A for loop with no post statement lets the body control the step.
 */
