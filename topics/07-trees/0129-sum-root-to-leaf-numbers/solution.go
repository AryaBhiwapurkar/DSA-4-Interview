/*
 * 0129. Sum Root to Leaf Numbers  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/sum-root-to-leaf-numbers/
 *
 * Problem: Each root-to-leaf path of digits spells a number; sum them all.
 *
 * Examples (level order, null = missing):
 *   [1,2,3]        -> 25
 *   [4,9,0,5,1]    -> 1026
 *   [0]            -> 0
 *   [1,0]          -> 10   (one-child node: null side adds nothing)
 *
 * Approaches:
 *   1. Recursive DFS  ⭐        O(n) time, O(h) space   <- go-to
 *   2. BFS (node, number)      O(n) time, O(w) space
 */

package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

type TreeNode struct {
	Val         int
	Left, Right *TreeNode
}

// ---------- Approach 1: Recursive DFS ⭐ ----------
func dfs(n *TreeNode, cur int) int {
	if n == nil {
		return 0 // nil contributes nothing
	}
	cur = cur*10 + n.Val // append this digit
	if n.Left == nil && n.Right == nil {
		return cur
	}
	return dfs(n.Left, cur) + dfs(n.Right, cur)
}

func sumNumbers(root *TreeNode) int { return dfs(root, 0) }

// ---------- Approach 2: BFS (node, number) ----------
func sumNumbersBFS(root *TreeNode) int {
	type item struct {
		n   *TreeNode
		cur int
	}
	total := 0
	q := []item{}
	if root != nil {
		q = append(q, item{root, root.Val})
	}
	for len(q) > 0 {
		it := q[0]
		q = q[1:]
		if it.n.Left == nil && it.n.Right == nil {
			total += it.cur
		}
		for _, c := range []*TreeNode{it.n.Left, it.n.Right} {
			if c != nil {
				q = append(q, item{c, it.cur*10 + c.Val})
			}
		}
	}
	return total
}

// ---------- Driver ----------
const null = math.MinInt // marks a missing node in level-order input

func build(vals []int) *TreeNode { // LeetCode level order
	if len(vals) == 0 || vals[0] == null {
		return nil
	}
	root := &TreeNode{Val: vals[0]}
	q := []*TreeNode{root}
	for i := 1; i < len(vals); i += 2 {
		n := q[0]
		q = q[1:]
		if vals[i] != null {
			n.Left = &TreeNode{Val: vals[i]}
			q = append(q, n.Left)
		}
		if i+1 < len(vals) && vals[i+1] != null {
			n.Right = &TreeNode{Val: vals[i+1]}
			q = append(q, n.Right)
		}
	}
	return root
}

func serialize(root *TreeNode) string { // level order, trailing nulls trimmed
	out := []string{}
	q := []*TreeNode{root}
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		if n == nil {
			out = append(out, "null")
			continue
		}
		out = append(out, strconv.Itoa(n.Val))
		q = append(q, n.Left, n.Right)
	}
	for len(out) > 0 && out[len(out)-1] == "null" {
		out = out[:len(out)-1]
	}
	return "[" + strings.Join(out, ",") + "]"
}

func main() {
	for _, v := range [][]int{{1, 2, 3}, {4, 9, 0, 5, 1}, {0}, {1, 0}} {
		root := build(v)
		fmt.Println("dfs:", sumNumbers(root))
		fmt.Println("bfs:", sumNumbersBFS(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Ranging over []*TreeNode{a, b} handles both children uniformly.
 * - cur*10 + digit builds a number left to right.
 */
