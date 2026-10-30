/*
 * 0104. Maximum Depth of Binary Tree  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/
 *
 * Problem: Number of nodes on the longest root-to-leaf path.
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]  -> 3
 *   [1,null,2]               -> 2
 *   []                       -> 0
 *   [1]                      -> 1
 *
 * Approaches:
 *   1. Recursive DFS  ⭐   O(n) time, O(h) space   <- go-to
 *   2. BFS level count    O(n) time, O(w) space
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
func maxDepth(root *TreeNode) int {
	if root == nil {
		return 0
	}
	return 1 + max(maxDepth(root.Left), maxDepth(root.Right))
}

// ---------- Approach 2: BFS Level Count ----------
func maxDepthBFS(root *TreeNode) int {
	if root == nil {
		return 0
	}
	q, depth := []*TreeNode{root}, 0
	for len(q) > 0 {
		depth++
		for sz := len(q); sz > 0; sz-- { // exactly one level per iteration
			n := q[0]
			q = q[1:]
			if n.Left != nil {
				q = append(q, n.Left)
			}
			if n.Right != nil {
				q = append(q, n.Right)
			}
		}
	}
	return depth
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
	for _, v := range [][]int{{3, 9, 20, null, null, 15, 7}, {1, null, 2}, {}, {1}} {
		root := build(v)
		fmt.Println("dfs:", maxDepth(root))
		fmt.Println("bfs:", maxDepthBFS(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - `for sz := len(q); sz > 0; sz--` freezes the level size up front.
 * - Built-in max (Go 1.21+) replaces a hand-written helper.
 * - serialize is unused here; unused functions compile fine in Go
 *   (only unused imports and variables are errors).
 */
