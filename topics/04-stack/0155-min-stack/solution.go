/*
 * 0155. Min Stack  |  Medium  |  Stack
 * Link: https://leetcode.com/problems/min-stack/
 *
 * Problem: Design a stack with push, pop, top and getMin, all O(1).
 *          pop/top/getMin are only called on a non-empty stack.
 *
 * Examples:
 *   push -2, push 0, push -3, getMin, pop, top, getMin
 *     -> [null,null,null,null,-3,null,0,-2]
 *   push 0, push 1, push 0, getMin, pop, getMin          (duplicate min)
 *     -> [null,null,null,null,0,null,0]
 *
 * Approaches:
 *   1. Plain stack, scan on getMin   O(n) getMin, O(n) space
 *   2. Stack of (val, min)  ⭐        O(1) all ops, O(n) space   <- go-to
 *   3. Two stacks                    O(1) all ops, O(n) space worst case
 */

package main

import (
	"fmt"
	"slices"
	"strconv"
	"strings"
)

// ---------- Approach 1: Plain Stack, Scan for Min ----------
type MinStackBrute struct{ st []int }

func (s *MinStackBrute) Push(val int) { s.st = append(s.st, val) }
func (s *MinStackBrute) Pop()         { s.st = s.st[:len(s.st)-1] }
func (s *MinStackBrute) Top() int     { return s.st[len(s.st)-1] }
func (s *MinStackBrute) GetMin() int  { return slices.Min(s.st) }

// ---------- Approach 2: Stack of (val, min) ⭐ ----------
type entry struct{ val, min int } // min of this and everything below

type MinStack struct{ st []entry }

func Constructor() MinStack { return MinStack{} }

func (s *MinStack) Push(val int) {
	m := val
	if len(s.st) > 0 {
		m = min(val, s.st[len(s.st)-1].min)
	}
	s.st = append(s.st, entry{val, m})
}
func (s *MinStack) Pop()        { s.st = s.st[:len(s.st)-1] }
func (s *MinStack) Top() int    { return s.st[len(s.st)-1].val }
func (s *MinStack) GetMin() int { return s.st[len(s.st)-1].min }

// ---------- Approach 3: Two Stacks ----------
type MinStackTwoStacks struct{ st, mins []int }

func (s *MinStackTwoStacks) Push(val int) {
	s.st = append(s.st, val)
	if len(s.mins) == 0 || val <= s.mins[len(s.mins)-1] { // <= keeps duplicate mins
		s.mins = append(s.mins, val)
	}
}
func (s *MinStackTwoStacks) Pop() {
	if s.st[len(s.st)-1] == s.mins[len(s.mins)-1] {
		s.mins = s.mins[:len(s.mins)-1]
	}
	s.st = s.st[:len(s.st)-1]
}
func (s *MinStackTwoStacks) Top() int    { return s.st[len(s.st)-1] }
func (s *MinStackTwoStacks) GetMin() int { return s.mins[len(s.mins)-1] }

// ---------- Driver ----------
type minStacker interface {
	Push(int)
	Pop()
	Top() int
	GetMin() int
}

func run(st minStacker, ops []string, args []int) string {
	out := []string{"null"} // ops[0] is the constructor
	for i := 1; i < len(ops); i++ {
		switch ops[i] {
		case "push":
			st.Push(args[i])
			out = append(out, "null")
		case "pop":
			st.Pop()
			out = append(out, "null")
		case "top":
			out = append(out, strconv.Itoa(st.Top()))
		default:
			out = append(out, strconv.Itoa(st.GetMin()))
		}
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	tests := []struct {
		ops  []string
		args []int
	}{
		{[]string{"MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"},
			[]int{0, -2, 0, -3, 0, 0, 0, 0}},
		{[]string{"MinStack", "push", "push", "push", "getMin", "pop", "getMin"},
			[]int{0, 0, 1, 0, 0, 0, 0}},
	}
	for _, t := range tests {
		ms := Constructor()
		fmt.Println("brute    :", run(&MinStackBrute{}, t.ops, t.args))
		fmt.Println("pairs    :", run(&ms, t.ops, t.args))
		fmt.Println("twoStacks:", run(&MinStackTwoStacks{}, t.ops, t.args))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Methods with pointer receivers (s *T) can modify the struct; pass &v
 *   to satisfy an interface whose methods use pointer receivers.
 * - An interface (minStacker) lets one driver run several implementations.
 * - slices.Min (Go 1.21+) returns the smallest element; panics if empty.
 * - strconv.Itoa + strings.Join build the "[a,b,c]" output.
 */
