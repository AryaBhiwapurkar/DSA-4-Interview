/*
 * 0222. Count Complete Tree Nodes  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/count-complete-tree-nodes/
 *
 * Problem: Count the nodes of a complete binary tree in less than O(n).
 *
 * Examples (level order, null = missing):
 *   [1,2,3,4,5,6]    -> 6
 *   []               -> 0
 *   [1]              -> 1
 *   [1,2,3,4,5,6,7]  -> 7   (perfect: answered at the root)
 *   [1,2,3,4]        -> 4
 *
 * Approaches:
 *   1. Plain DFS count               O(n) time, O(h) space
 *   2. Spine heights + recursion  ⭐  O(log^2 n) time, O(log n) space   <- go-to
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

// ---------- Approach 1: Plain DFS Count ----------
func countNodesDFS(root *TreeNode) int {
	if root == nil {
		return 0
	}
	return 1 + countNodesDFS(root.Left) + countNodesDFS(root.Right)
}

// ---------- Approach 2: Spine Heights + Recursion ⭐ ----------
func countNodes(root *TreeNode) int {
	if root == nil {
		return 0
	}
	lh, rh := 0, 0
	for n := root; n != nil; n = n.Left { // walk spines only: O(log n)
		lh++
	}
	for n := root; n != nil; n = n.Right {
		rh++
	}
	if lh == rh {
		return 1<<lh - 1 // perfect tree
	}
	return 1 + countNodes(root.Left) + countNodes(root.Right) // one side is perfect
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
	for _, v := range [][]int{{1, 2, 3, 4, 5, 6}, {}, {1}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4}} {
		root := build(v)
		fmt.Println("dfs   :", countNodesDFS(root))
		fmt.Println("spines:", countNodes(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - In Go, << binds tighter than -, so 1<<lh - 1 is (1<<lh) - 1
 *   (gofmt spacing shows the grouping).
 */
