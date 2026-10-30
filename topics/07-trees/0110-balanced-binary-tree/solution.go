/*
 * 0110. Balanced Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/balanced-binary-tree/
 *
 * Problem: Is every node's left/right subtree height difference <= 1?
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]                -> true
 *   [1,2,2,3,3,null,null,4,4]              -> false
 *   []                                     -> true
 *   [1,2,2,3,null,null,3,4,null,null,4]    -> false  (root looks balanced, subtrees aren't)
 *
 * Approaches:
 *   1. Top-down heights              O(n^2) time, O(h) space
 *   2. Bottom-up with -1 sentinel ⭐  O(n) time, O(h) space   <- go-to
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

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

// ---------- Approach 1: Top-Down Heights ----------
func height(n *TreeNode) int {
	if n == nil {
		return 0
	}
	return 1 + max(height(n.Left), height(n.Right))
}

func isBalancedTopDown(root *TreeNode) bool {
	if root == nil {
		return true
	}
	return abs(height(root.Left)-height(root.Right)) <= 1 &&
		isBalancedTopDown(root.Left) && isBalancedTopDown(root.Right)
}

// ---------- Approach 2: Bottom-Up With -1 Sentinel ⭐ ----------
func check(n *TreeNode) int { // height, or -1 if unbalanced
	if n == nil {
		return 0
	}
	L := check(n.Left)
	if L == -1 {
		return -1 // propagate failure immediately
	}
	R := check(n.Right)
	if R == -1 || abs(L-R) > 1 {
		return -1
	}
	return 1 + max(L, R)
}

func isBalanced(root *TreeNode) bool { return check(root) != -1 }

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
	tests := [][]int{
		{3, 9, 20, null, null, 15, 7}, {1, 2, 2, 3, 3, null, null, 4, 4}, {}, {1, 2, 2, 3, null, null, 3, 4, null, null, 4},
	}
	for _, v := range tests {
		root := build(v)
		fmt.Println("topDown :", isBalancedTopDown(root))
		fmt.Println("bottomUp:", isBalanced(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go has no integer abs in the standard library (math.Abs is float64);
 *   write a tiny helper.
 * - A trailing && lets a boolean expression continue on the next line.
 */
