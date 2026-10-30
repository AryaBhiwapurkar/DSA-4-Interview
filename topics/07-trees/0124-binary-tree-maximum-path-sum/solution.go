/*
 * 0124. Binary Tree Maximum Path Sum  |  Hard  |  Trees
 * Link: https://leetcode.com/problems/binary-tree-maximum-path-sum/
 *
 * Problem: Maximum sum of any non-empty path (connected nodes, each used
 *          once, not necessarily through the root).
 *
 * Examples (level order, null = missing):
 *   [1,2,3]                    -> 6
 *   [-10,9,20,null,null,15,7]  -> 42
 *   [-3]                       -> -3   (all negative)
 *   [2,-1]                     -> 2
 *
 * Approaches:
 *   1. Every node as top, recomputing gains   O(n^2) time, O(h) space
 *   2. Single DFS, global max  ⭐              O(n) time, O(h) space   <- go-to
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

// ---------- Approach 1: Every Node as Top ----------
func down(n *TreeNode) int { // best path starting at n going down
	if n == nil {
		return 0
	}
	return n.Val + max(0, down(n.Left), down(n.Right))
}

func maxPathSumBrute(root *TreeNode) int {
	if root == nil {
		return math.MinInt
	}
	here := root.Val + max(0, down(root.Left)) + max(0, down(root.Right))
	return max(here, maxPathSumBrute(root.Left), maxPathSumBrute(root.Right))
}

// ---------- Approach 2: Single DFS, Global Max ⭐ ----------
func maxPathSum(root *TreeNode) int {
	best := math.MinInt // not 0: all-negative trees
	var gain func(n *TreeNode) int
	gain = func(n *TreeNode) int {
		if n == nil {
			return 0
		}
		L := max(0, gain(n.Left)) // a negative branch is never worth taking
		R := max(0, gain(n.Right))
		best = max(best, n.Val+L+R) // path bending at n
		return n.Val + max(L, R)    // parent can extend only one side
	}
	gain(root)
	return best
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
	for _, v := range [][]int{{1, 2, 3}, {-10, 9, 20, null, null, 15, 7}, {-3}, {2, -1}} {
		root := build(v)
		fmt.Println("brute :", maxPathSumBrute(root))
		fmt.Println("global:", maxPathSum(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - math.MinInt as the starting best.
 * - Built-in max is variadic: max(0, a, b).
 */
