/*
 * 0101. Symmetric Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/symmetric-tree/
 *
 * Problem: Is the tree a mirror image of itself?
 *
 * Examples (level order, null = missing):
 *   [1,2,2,3,4,4,3]          -> true
 *   [1,2,2,null,3,null,3]    -> false
 *   [1]                      -> true
 *   [1,2,3]                  -> false
 *
 * Approaches:
 *   1. Recursive mirror check  ⭐   O(n) time, O(h) space   <- go-to
 *   2. Queue of pairs              O(n) time, O(w) space
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

// ---------- Approach 1: Recursive Mirror Check ⭐ ----------
func mirror(a, b *TreeNode) bool {
	if a == nil && b == nil {
		return true
	}
	if a == nil || b == nil {
		return false
	}
	return a.Val == b.Val && mirror(a.Left, b.Right) && mirror(a.Right, b.Left) // crossed
}

func isSymmetric(root *TreeNode) bool {
	return root == nil || mirror(root.Left, root.Right)
}

// ---------- Approach 2: Queue of Pairs ----------
func isSymmetricBFS(root *TreeNode) bool {
	if root == nil {
		return true
	}
	q := [][2]*TreeNode{{root.Left, root.Right}}
	for len(q) > 0 {
		a, b := q[0][0], q[0][1]
		q = q[1:]
		if a == nil && b == nil {
			continue
		}
		if a == nil || b == nil || a.Val != b.Val {
			return false
		}
		q = append(q, [2]*TreeNode{a.Left, b.Right}, [2]*TreeNode{a.Right, b.Left}) // outer, inner
	}
	return true
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
	for _, v := range [][]int{{1, 2, 2, 3, 4, 4, 3}, {1, 2, 2, null, 3, null, 3}, {1}, {1, 2, 3}} {
		root := build(v)
		fmt.Println("dfs:", isSymmetric(root))
		fmt.Println("bfs:", isSymmetricBFS(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - append accepts several items: append(q, x, y).
 * - The only change from Same Tree is the crossed recursive arguments.
 */
