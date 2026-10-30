/*
 * 0530. Minimum Absolute Difference in BST  |  Easy  |  Trees
 * Link: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
 *
 * Problem: Minimum absolute difference between values of any two nodes.
 *
 * Examples (level order, null = missing):
 *   [4,2,6,1,3]               -> 1
 *   [1,0,48,null,null,12,49]  -> 1
 *   [236,104,701,null,227,null,911]  -> 9   (closest pair 227, 236 isn't parent-child)
 *
 * Approaches:
 *   1. Inorder list + adjacent gaps   O(n) time, O(n) space
 *   2. Inorder with prev  ⭐           O(n) time, O(h) space   <- go-to
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

// ---------- Approach 1: Inorder List + Adjacent Gaps ----------
func getMinimumDifferenceList(root *TreeNode) int {
	vals := []int{}
	var collect func(n *TreeNode)
	collect = func(n *TreeNode) {
		if n == nil {
			return
		}
		collect(n.Left)
		vals = append(vals, n.Val)
		collect(n.Right)
	}
	collect(root)
	best := math.MaxInt
	for i := 1; i < len(vals); i++ {
		best = min(best, vals[i]-vals[i-1])
	}
	return best
}

// ---------- Approach 2: Inorder With prev ⭐ ----------
func getMinimumDifference(root *TreeNode) int {
	prev, best := -1, math.MaxInt // -1 = none yet (values are >= 0)
	var inorder func(n *TreeNode)
	inorder = func(n *TreeNode) {
		if n == nil {
			return
		}
		inorder(n.Left)
		if prev != -1 {
			best = min(best, n.Val-prev)
		}
		prev = n.Val
		inorder(n.Right)
	}
	inorder(root)
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
	for _, v := range [][]int{{4, 2, 6, 1, 3}, {1, 0, 48, null, null, 12, 49}, {236, 104, 701, null, 227, null, 911}} {
		root := build(v)
		fmt.Println("list:", getMinimumDifferenceList(root))
		fmt.Println("prev:", getMinimumDifference(root))
		fmt.Println("---")
	}
}

/*
 * Syntax notes (Go):
 * - Closures share prev/best with the enclosing function: no pointers needed.
 * - math.MaxInt as the starting minimum.
 */
