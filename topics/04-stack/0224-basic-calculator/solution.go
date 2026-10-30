/*
 * 0224. Basic Calculator  |  Hard  |  Stack
 * Link: https://leetcode.com/problems/basic-calculator/
 *
 * Problem: Evaluate a valid expression with non-negative integers, + - ( )
 *          and spaces. '-' may be unary. No eval.
 *
 * Examples:
 *   "1 + 1"                -> 2
 *   " 2-1 + 2 "            -> 3
 *   "(1+(4+5+2)-3)+(6+8)"  -> 23
 *   "-(2+3)"               -> -5
 *   "1-(     -2)"          -> 3
 *   "2147483647"           -> 2147483647
 *
 * Approaches:
 *   1. Recursive descent       O(n) time, O(depth) space
 *   2. Stack of (result, sign) ⭐ O(n) time, O(depth) space   <- go-to
 */

package main

import "fmt"

func isDigit(c byte) bool { return c >= '0' && c <= '9' }

// ---------- Approach 1: Recursive Descent ----------
func calculateRecursive(s string) int {
	i := 0
	var parse func() int
	parse = func() int {
		res, sign := 0, 1
		for i < len(s) {
			c := s[i]
			i++
			switch {
			case isDigit(c):
				num := int(c - '0')
				for i < len(s) && isDigit(s[i]) {
					num = num*10 + int(s[i]-'0')
					i++
				}
				res += sign * num
			case c == '+':
				sign = 1
			case c == '-':
				sign = -1
			case c == '(':
				res += sign * parse() // a group is just a number
			case c == ')':
				return res
			}
		}
		return res
	}
	return parse()
}

// ---------- Approach 2: Stack of (result, sign) ⭐ ----------
func calculate(s string) int {
	res, num, sign := 0, 0, 1
	type frame struct{ res, sign int } // saved context per open paren
	st := []frame{}
	for i := 0; i < len(s); i++ {
		c := s[i]
		switch {
		case isDigit(c):
			num = num*10 + int(c-'0')
		case c == '+' || c == '-':
			res += sign * num // flush the pending number
			num = 0
			sign = 1
			if c == '-' {
				sign = -1
			}
		case c == '(':
			st = append(st, frame{res, sign})
			res, sign = 0, 1
		case c == ')':
			res += sign * num
			num = 0
			top := st[len(st)-1]
			st = st[:len(st)-1]
			res = top.res + top.sign*res
		} // spaces fall through
	}
	return res + sign*num // flush the final number
}

// ---------- Driver ----------
func main() {
	tests := []string{"1 + 1", " 2-1 + 2 ", "(1+(4+5+2)-3)+(6+8)", "-(2+3)", "1-(     -2)", "2147483647"}
	for _, s := range tests {
		fmt.Println("recursive:", calculateRecursive(s))
		fmt.Println("stack    :", calculate(s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A tagless `switch { case cond: }` replaces an if/else-if chain.
 * - Types can be declared inside a function (type frame struct{...}).
 * - int(c - '0') converts a digit byte to its value.
 * - Closures capture variables by reference, so parse() advances the outer i.
 */
