/*
 * 0150. Evaluate Reverse Polish Notation  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/
 *
 * Problem: Evaluate a postfix expression of integers and + - * /.
 *          Division truncates toward zero. Input is always valid.
 *
 * Examples:
 *   ["2","1","+","3","*"]                                        -> 9
 *   ["4","13","5","/","+"]                                       -> 6
 *   ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]    -> 22
 *   ["18"]                                                       -> 18
 *   ["4","-3","/"]                                               -> -1
 *
 * Approaches:
 *   1. Repeated collapse   O(n^2) time, O(n) space
 *   2. Stack  ⭐            O(n) time, O(n) space   <- go-to
 */

package main

import (
	"fmt"
	"slices"
	"strconv"
)

func isOp(t string) bool { return t == "+" || t == "-" || t == "*" || t == "/" }

func apply(a, b int, op string) int {
	switch op {
	case "+":
		return a + b
	case "-":
		return a - b
	case "*":
		return a * b
	default:
		return a / b // Go truncates toward zero already
	}
}

// ---------- Approach 1: Repeated Collapse ----------
func evalRPNBrute(tokens []string) int {
	t := slices.Clone(tokens)
	for len(t) > 1 {
		i := slices.IndexFunc(t, isOp) // first operator
		a, _ := strconv.Atoi(t[i-2])
		b, _ := strconv.Atoi(t[i-1])
		t[i-2] = strconv.Itoa(apply(a, b, t[i]))
		t = slices.Delete(t, i-1, i+1)
	}
	v, _ := strconv.Atoi(t[0])
	return v
}

// ---------- Approach 2: Stack ⭐ ----------
func evalRPN(tokens []string) int {
	st := []int{}
	for _, t := range tokens {
		if !isOp(t) { // "-11" is a number: isOp compares the whole token
			v, _ := strconv.Atoi(t)
			st = append(st, v)
			continue
		}
		a, b := st[len(st)-2], st[len(st)-1] // top = RIGHT operand
		st = st[:len(st)-2]
		st = append(st, apply(a, b, t))
	}
	return st[0]
}

// ---------- Driver ----------
func main() {
	tests := [][]string{
		{"2", "1", "+", "3", "*"},
		{"4", "13", "5", "/", "+"},
		{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"},
		{"18"},
		{"4", "-3", "/"},
	}
	for _, t := range tests {
		fmt.Println("brute:", evalRPNBrute(t))
		fmt.Println("stack:", evalRPN(t))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - strconv.Atoi returns (int, error); `v, _ :=` discards the error when
 *   input is guaranteed valid.
 * - slices.IndexFunc(s, pred) finds the first match; slices.Delete(s, i, j)
 *   removes s[i:j] and returns the shortened slice.
 * - Read two values then shrink once: st[len(st)-2], st[len(st)-1].
 * - Integer division truncates toward zero, like C++.
 */
