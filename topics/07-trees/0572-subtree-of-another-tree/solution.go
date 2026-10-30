/*
 * 0572. Subtree of Another Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/subtree-of-another-tree/
 *
 * Problem: Does subRoot appear in root as a complete subtree?
 *
 * Examples (level order, null = missing):
 *   [3,4,5,1,2],                         [4,1,2]  -> true
 *   [3,4,5,1,2,null,null,null,null,0],   [4,1,2]  -> false
 *   [12],                                [2]      -> false  (delimiter check)
 *   [1,1],                               [1]      -> true
 *
 * Approaches:
 *   1. DFS + same tree  ⭐          O(m*n) time, O(h) space   <- go-to
 *   2. Serialize + substring        O(m+n) with KMP, O(m+n) space
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

// ---------- Approach 1: DFS + Same Tree ⭐ ----------
func same(a, b *TreeNode) bool {
	if a == nil || b == nil {
		return a == b
	}
	return a.Val == b.Val && same(a.Left, b.Left) && same(a.Right, b.Right)
}

func isSubtree(root, subRoot *TreeNode) bool {
	if root == nil {
		return false
	}
	return same(root, subRoot) || isSubtree(root.Left, subRoot) || isSubtree(root.Right, subRoot)
}

// ---------- Approach 2: Serialize + Substring ----------
func pre(n *TreeNode, sb *strings.Builder) {
	if n == nil {
		sb.WriteString(",#") // null marker keeps shapes distinct
		return
	}
	sb.WriteString("," + strconv.Itoa(n.Val)) // leading comma: "2" can't match inside "12"
	pre(n.Left, sb)
	pre(n.Right, sb)
}

func isSubtreeSerialize(root, subRoot *TreeNode) bool {
	var a, b strings.Builder
	pre(root, &a)
	pre(subRoot, &b)
	return strings.Contains(a.String(), b.String())
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
	tests := [][2][]int{
		{{3, 4, 5, 1, 2}, {4, 1, 2}}, {{3, 4, 5, 1, 2, null, null, null, null, 0}, {4, 1, 2}}, {{12}, {2}}, {{1, 1}, {1}},
	}
	for _, t := range tests {
		r, s := build(t[0]), build(t[1])
		fmt.Println("dfs      :", isSubtree(r, s))
		fmt.Println("serialize:", isSubtreeSerialize(r, s))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Pass *strings.Builder to recursive helpers; copying a Builder panics.
 * - strings.Contains(s, sub) is substring search.
 * - `if a == nil || b == nil { return a == b }` covers all null cases.
 */
