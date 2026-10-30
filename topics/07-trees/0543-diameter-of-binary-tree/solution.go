/*
 * 0543. Diameter of Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/diameter-of-binary-tree/
 *
 * Problem: Number of edges on the longest path between any two nodes.
 *
 * Examples (level order, null = missing):
 *   [1,2,3,4,5]                     -> 3
 *   [1,2]                           -> 1
 *   [1]                             -> 0
 *   [1,2,null,3,4,5,null,null,6]    -> 4   (longest path avoids the root)
 *
 * Approaches:
 *   1. Height per node                O(n^2) time, O(h) space
 *   2. Single DFS, global max  ⭐      O(n) time, O(h) space   <- go-to
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

// ---------- Approach 1: Height Per Node ----------
func height(n *TreeNode) int {
	if n == nil {
		return 0
	}
	return 1 + max(height(n.Left), height(n.Right))
}

func diameterOfBinaryTreeBrute(root *TreeNode) int {
	if root == nil {
		return 0
	}
	through := height(root.Left) + height(root.Right)
	return max(through, diameterOfBinaryTreeBrute(root.Left), diameterOfBinaryTreeBrute(root.Right))
}

// ---------- Approach 2: Single DFS, Global Max ⭐ ----------
func diameterOfBinaryTree(root *TreeNode) int {
	best := 0
	var dfs func(n *TreeNode) int // returns height in nodes
	dfs = func(n *TreeNode) int {
		if n == nil {
			return 0
		}
		L, R := dfs(n.Left), dfs(n.Right)
		best = max(best, L+R) // path bending here, in edges
		return 1 + max(L, R)  // parent can only use one branch
	}
	dfs(root)
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
	for _, v := range [][]int{{1, 2, 3, 4, 5}, {1, 2}, {1}, {1, 2, null, 3, 4, 5, null, null, 6}} {
		root := build(v)
		fmt.Println("brute :", diameterOfBinaryTreeBrute(root))
		fmt.Println("global:", diameterOfBinaryTree(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - A closure captures `best` by reference: no pointer needed.
 * - Recursive closures need `var dfs func(...)` declared first.
 * - Built-in max accepts any number of arguments (Go 1.21+).
 */
