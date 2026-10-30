/*
 * 0103. Binary Tree Zigzag Level Order Traversal  |  Medium  |  Trees
 * Link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
 *
 * Problem: Level order, alternating left-to-right and right-to-left.
 *
 * Examples (level order, null = missing):
 *   [3,9,20,null,null,15,7]  -> [[3] [20 9] [15 7]]
 *   [1]                      -> [[1]]
 *   []                       -> []
 *   [1,2,3,4,null,null,5]    -> [[1] [3 2] [4 5]]
 *
 * Approaches:
 *   1. BFS + index by direction  ⭐   O(n) time, O(w) space   <- go-to
 *   2. BFS + reverse odd levels       O(n) time, O(w) space
 */

package main

import (
	"fmt"
	"math"
	"slices"
	"strconv"
	"strings"
)

type TreeNode struct {
	Val         int
	Left, Right *TreeNode
}

// ---------- Approach 1: BFS + Index by Direction ⭐ ----------
func zigzagLevelOrder(root *TreeNode) [][]int {
	res := [][]int{}
	q := []*TreeNode{}
	if root != nil {
		q = append(q, root)
	}
	leftToRight := true
	for len(q) > 0 {
		sz := len(q)
		level := make([]int, sz)
		for i := 0; i < sz; i++ {
			n := q[0]
			q = q[1:]
			if leftToRight { // BFS order stays normal
				level[i] = n.Val
			} else {
				level[sz-1-i] = n.Val
			}
			if n.Left != nil {
				q = append(q, n.Left)
			}
			if n.Right != nil {
				q = append(q, n.Right)
			}
		}
		res = append(res, level)
		leftToRight = !leftToRight
	}
	return res
}

// ---------- Approach 2: BFS + Reverse Odd Levels ----------
func zigzagLevelOrderReverse(root *TreeNode) [][]int {
	res := [][]int{}
	q := []*TreeNode{}
	if root != nil {
		q = append(q, root)
	}
	for len(q) > 0 {
		level := []int{}
		for sz := len(q); sz > 0; sz-- {
			n := q[0]
			q = q[1:]
			level = append(level, n.Val)
			if n.Left != nil {
				q = append(q, n.Left)
			}
			if n.Right != nil {
				q = append(q, n.Right)
			}
		}
		if len(res)%2 == 1 {
			slices.Reverse(level)
		}
		res = append(res, level)
	}
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
	for _, v := range [][]int{{3, 9, 20, null, null, 15, 7}, {1}, {}, {1, 2, 3, 4, null, null, 5}} {
		root := build(v)
		fmt.Println("index  :", zigzagLevelOrder(root))
		fmt.Println("reverse:", zigzagLevelOrderReverse(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - make([]int, sz) pre-sizes for index writes.
 * - slices.Reverse(s) reverses in place (Go 1.21+).
 */
