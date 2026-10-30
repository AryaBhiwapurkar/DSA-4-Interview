/*
 * 0226. Invert Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/invert-binary-tree/
 *
 * Problem: Mirror a binary tree (swap left/right at every node).
 *
 * Examples (level order, null = missing):
 *   [4,2,7,1,3,6,9]  -> [4,7,2,9,6,3,1]
 *   [2,1,3]          -> [2,3,1]
 *   []               -> []
 *   [1,2]            -> [1,null,2]
 *
 * Approaches:
 *   1. Recursive DFS  ⭐   O(n) time, O(h) space   <- go-to
 *   2. Iterative BFS      O(n) time, O(w) space
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
func invertTree(root *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}
	root.Left, root.Right = invertTree(root.Right), invertTree(root.Left) // RHS first: safe
	return root
}

// ---------- Approach 2: Iterative BFS ----------
func invertTreeBFS(root *TreeNode) *TreeNode {
	q := []*TreeNode{}
	if root != nil {
		q = append(q, root)
	}
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		n.Left, n.Right = n.Right, n.Left
		if n.Left != nil {
			q = append(q, n.Left)
		}
		if n.Right != nil {
			q = append(q, n.Right)
		}
	}
	return root
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
	for _, v := range [][]int{{4, 2, 7, 1, 3, 6, 9}, {2, 1, 3}, {}, {1, 2}} { // fresh tree per approach
		fmt.Println("dfs:", serialize(invertTree(build(v))))
		fmt.Println("bfs:", serialize(invertTreeBFS(build(v))))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Parallel assignment evaluates both calls before assigning, so the
 *   one-line recursive swap is safe.
 * - A slice works as a queue: q[0] to read, q = q[1:] to pop.
 * - math.MinInt as a "null" marker keeps test input a plain []int.
 */
