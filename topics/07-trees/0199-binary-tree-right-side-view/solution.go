/*
 * 0199. Binary Tree Right Side View  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/binary-tree-right-side-view/
 *
 * Problem: Values visible from the right side, top to bottom.
 *
 * Examples (level order, null = missing):
 *   [1,2,3,null,5,null,4]        -> [1 3 4]
 *   [1,2,3,4,null,null,null,5]   -> [1 3 4 5]
 *   [1,null,3]                   -> [1 3]
 *   []                           -> []
 *
 * Approaches:
 *   1. BFS, last per level  ⭐   O(n) time, O(w) space   <- go-to
 *   2. DFS right-first          O(n) time, O(h) space
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

// ---------- Approach 1: BFS, Last per Level ⭐ ----------
func rightSideView(root *TreeNode) []int {
	res := []int{}
	q := []*TreeNode{}
	if root != nil {
		q = append(q, root)
	}
	for len(q) > 0 {
		res = append(res, q[len(q)-1].Val) // queue holds exactly one level: last = rightmost
		for sz := len(q); sz > 0; sz-- {
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
	return res
}

// ---------- Approach 2: DFS Right-First ----------
func rightSideViewDFS(root *TreeNode) []int {
	res := []int{}
	var dfs func(n *TreeNode, depth int)
	dfs = func(n *TreeNode, depth int) {
		if n == nil {
			return
		}
		if depth == len(res) { // first node seen at this depth
			res = append(res, n.Val)
		}
		dfs(n.Right, depth+1) // right first
		dfs(n.Left, depth+1)
	}
	dfs(root, 0)
	return res
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
	for _, v := range [][]int{{1, 2, 3, null, 5, null, 4}, {1, 2, 3, 4, null, null, null, 5}, {1, null, 3}, {}} {
		root := build(v)
		fmt.Println("bfs:", rightSideView(root))
		fmt.Println("dfs:", rightSideViewDFS(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - q[len(q)-1] reads the back of the slice-queue before the level is popped.
 * - Closures can append to a captured slice variable.
 */
