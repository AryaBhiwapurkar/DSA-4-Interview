/*
 * 0112. Path Sum  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/path-sum/
 *
 * Problem: Is there a root-to-leaf path whose values sum to targetSum?
 *
 * Examples (level order, null = missing):
 *   [5,4,8,11,null,13,4,7,2,null,null,null,1], 22  -> true
 *   [1,2,3], 5                                     -> false
 *   [], 0                                          -> false
 *   [1,2], 1                                       -> false  (root isn't a leaf)
 *   [-2,null,-3], -5                               -> true
 *
 * Approaches:
 *   1. Recursive DFS  ⭐                 O(n) time, O(h) space   <- go-to
 *   2. Iterative stack (node, remaining) O(n) time, O(h) space
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
func hasPathSum(root *TreeNode, target int) bool {
	if root == nil {
		return false
	}
	if root.Left == nil && root.Right == nil { // only leaves end paths
		return target == root.Val
	}
	rem := target - root.Val
	return hasPathSum(root.Left, rem) || hasPathSum(root.Right, rem)
}

// ---------- Approach 2: Iterative Stack ----------
func hasPathSumIter(root *TreeNode, target int) bool {
	type item struct {
		n   *TreeNode
		rem int
	}
	st := []item{}
	if root != nil {
		st = append(st, item{root, target})
	}
	for len(st) > 0 {
		it := st[len(st)-1]
		st = st[:len(st)-1]
		n := it.n
		if n.Left == nil && n.Right == nil && it.rem == n.Val {
			return true
		}
		if n.Left != nil {
			st = append(st, item{n.Left, it.rem - n.Val})
		}
		if n.Right != nil {
			st = append(st, item{n.Right, it.rem - n.Val})
		}
	}
	return false
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
	tests := []struct {
		v []int
		t int
	}{
		{[]int{5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1}, 22}, {[]int{1, 2, 3}, 5}, {[]int{}, 0},
		{[]int{1, 2}, 1}, {[]int{-2, null, -3}, -5},
	}
	for _, t := range tests {
		root := build(t.v)
		fmt.Println("dfs  :", hasPathSum(root, t.t))
		fmt.Println("stack:", hasPathSumIter(root, t.t))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A local struct type (item) pairs a node with its remaining sum.
 * - Leaf test: n.Left == nil && n.Right == nil.
 */
