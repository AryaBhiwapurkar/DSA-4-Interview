/*
 * 1448. Count Good Nodes in Binary Tree  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/count-good-nodes-in-binary-tree/
 *
 * Problem: A node is good if no node on its root path is greater. Count them.
 *
 * Examples (level order, null = missing):
 *   [3,1,4,3,null,1,5]  -> 4
 *   [3,3,null,4,2]      -> 3
 *   [1]                 -> 1
 *   [-1,-2,-3]          -> 1   (negatives: don't start max at 0)
 *
 * Approaches:
 *   1. DFS with path max  ⭐     O(n) time, O(h) space   <- go-to
 *   2. BFS with (node, max)     O(n) time, O(w) space
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

// ---------- Approach 1: DFS With Path Max ⭐ ----------
func dfs(n *TreeNode, mx int) int {
	if n == nil {
		return 0
	}
	good := 0
	if n.Val >= mx { // >= : equal values are good
		good = 1
	}
	mx = max(mx, n.Val)
	return good + dfs(n.Left, mx) + dfs(n.Right, mx)
}

func goodNodes(root *TreeNode) int { return dfs(root, math.MinInt) }

// ---------- Approach 2: BFS With (node, max) ----------
func goodNodesBFS(root *TreeNode) int {
	type item struct {
		n  *TreeNode
		mx int
	}
	count := 0
	q := []item{}
	if root != nil {
		q = append(q, item{root, math.MinInt})
	}
	for len(q) > 0 {
		it := q[0]
		q = q[1:]
		if it.n.Val >= it.mx {
			count++
		}
		nm := max(it.mx, it.n.Val)
		if it.n.Left != nil {
			q = append(q, item{it.n.Left, nm})
		}
		if it.n.Right != nil {
			q = append(q, item{it.n.Right, nm})
		}
	}
	return count
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
	for _, v := range [][]int{{3, 1, 4, 3, null, 1, 5}, {3, 3, null, 4, 2}, {1}, {-1, -2, -3}} {
		root := build(v)
		fmt.Println("dfs:", goodNodes(root))
		fmt.Println("bfs:", goodNodesBFS(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Go bools don't convert to ints; branch to set 0/1.
 * - A local struct type (item) bundles node + path max for the queue.
 */
